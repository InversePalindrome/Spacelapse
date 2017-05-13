/*
Copyright (c) 2017 InversePalindrome
Spacelapse - World.cpp
InversePalindrome.com
*/


#include "World.hpp"

#include <random>


const float World::increasedCameraStep = 5.f;
const float World::timePerSpawn = 1.6f;

World::World(sf::RenderTarget& target) :
	target(target),
	view(target.getDefaultView()),
	textures(),
	sceneGraph(),
	sceneLayers(),
	commands(),
	backgroundPerimeter(0.f, 0.f, view.getSize().x, view.getSize().y),
	timer(),
	cameraSpeed(500.f),
	background(nullptr),
	player(nullptr),
	asteroids()
{
	textures.load(Textures::PlayBackground, "Resources/Images/SpaceBackground.jpg");
	textures.load(Textures::BlueSpaceship, "Resources/Images/BlueSpaceship.png");
	textures.load(Textures::RegularAsteroid, "Resources/Images/RegularAsteroid.png");
	textures.load(Textures::LavaAsteroid, "Resources/Images/LavaAsteroid.png");

	for (std::size_t i = 0; i < static_cast<std::size_t>(Layer::Size); ++i)
	{
		auto layer = std::make_unique<SceneNode>();
		sceneLayers[i] = layer.get();

		sceneGraph.addChild(std::move(layer));
	}

	auto& backgroundTexture = textures.get(Textures::PlayBackground);
	backgroundTexture.setRepeated(true);

	sf::IntRect backgroundRectangle1(this->backgroundPerimeter);

	auto backgroundNode = std::make_unique<SpriteNode>(backgroundTexture, backgroundRectangle1);
	background = backgroundNode.get();
	sceneLayers[static_cast<std::size_t>(Layer::Background)]->addChild(std::move(backgroundNode));

	auto spaceship = std::make_unique<Spaceship>(Spaceship::Type::Blue, textures);
	player = spaceship.get();
	player->setPosition(sf::Vector2f(250.f, view.getSize().y / 2.f));
	sceneLayers[static_cast<std::size_t>(Layer::Space)]->addChild(std::move(spaceship));

	this->spawnAsteroids();
}

void World::update(sf::Time deltaTime)
{
	this->view.move(this->cameraSpeed * deltaTime.asSeconds(), 0.f);
	this->player->setVelocity(0.f, 0.f);

	while (this->commands.hasCommands())
	{
		this->sceneGraph.executeCommand(this->commands.pop(), deltaTime);
    }

	this->updateBackground();
	this->updatePlayerVelocity();
	this->updatePlayerPosition();

	this->deleteUnusedAsteroids();

	if (this->timer.getElapsedTime().asSeconds() >= this->timePerSpawn)
	{
		this->spawnAsteroids();
		this->cameraSpeed += this->increasedCameraStep;
		this->timer.restart();
	}

	this->sceneGraph.update(deltaTime, this->commands);
}

void World::draw()
{
	this->target.setView(this->view);
	this->target.draw(this->sceneGraph);
}

CommandQueue& World::getCommands()
{
	return this->commands;
}

void World::updateBackground()
{
	this->background->setTextureRect(sf::IntRect(this->view.getCenter().x - this->view.getSize().x / 2.f, 0.f, this->backgroundPerimeter.width, this->backgroundPerimeter.height));
	this->background->setPosition(this->view.getCenter().x - this->view.getSize().x / 2.f, 0.f);
}

void World::updatePlayerVelocity()
{
	if (this->player->getVelocity().x != 0.f && this->player->getVelocity().y != 0.f)
	{
		this->player->setVelocity(this->player->getVelocity() / std::sqrt(2.f));
	}

	this->player->accelerate(this->cameraSpeed, 0.f);
}

void World::updatePlayerPosition()
{
	auto position = this->player->getPosition();
	const sf::FloatRect viewRange(this->view.getCenter() - this->view.getSize() / 2.f, this->view.getSize());
	const float borderDistance = 125.f;

	position.x = std::max(position.x, viewRange.left + borderDistance);
	position.x = std::min(position.x, viewRange.left + viewRange.width - borderDistance);
	position.y = std::max(position.y, viewRange.top + borderDistance);
	position.y = std::min(position.y, viewRange.top + viewRange.height - borderDistance);

	this->player->setPosition(position);
}

void World::spawnAsteroids()
{
	const auto& externalWorldPerimeter = this->getExternalWorldPerimeter();

	std::random_device rd;
	std::mt19937 mt(rd());
    std::uniform_int_distribution<std::size_t> distNum(2, 6);
	std::uniform_real_distribution<float> distAsteroids(0.0f, 1.0f);
	std::uniform_real_distribution<float> distX(externalWorldPerimeter.left, externalWorldPerimeter.left + externalWorldPerimeter.width);
	std::uniform_real_distribution<float> distY(externalWorldPerimeter.top, externalWorldPerimeter.top + externalWorldPerimeter.height);
	std::uniform_real_distribution<float> distAngle(0.f, 360.f);

	const std::size_t numOfAsteroids = distNum(mt);
	const float regularAsteroidRate = 0.7f;

	for (std::size_t i = 0; i < numOfAsteroids; i++)
	{
		Asteroid::Type type = Asteroid::Type::UndefinedType;

		distAsteroids(mt) < regularAsteroidRate ? type = Asteroid::Type::Regular : type = Asteroid::Type::Lava;

		auto asteroid = std::make_unique<Asteroid>(type, this->textures);
	
		asteroid->setPosition(sf::Vector2f(distX(mt), distY(mt)));
		asteroid->setRotation(distAngle(mt));

		this->asteroids.push_back(asteroid.get());

		this->sceneLayers[static_cast<std::size_t>(Layer::Space)]->addChild(std::move(asteroid));
	}
}

void World::deleteUnusedAsteroids()
{
	for (auto itr = this->asteroids.begin(); itr != this->asteroids.end();)
	{
		if ((*itr)->getAbsolutePosition().x < this->view.getCenter().x - this->view.getSize().x)
		{
			this->sceneLayers[static_cast<std::size_t>(Layer::Space)]->removeChild(*(*itr));
			itr = this->asteroids.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

sf::FloatRect World::getExternalWorldPerimeter() const
{
	const float bufferDistance = 200.f;
	return sf::FloatRect(this->view.getCenter().x + this->view.getSize().x / 2.f + bufferDistance, this->view.getCenter().y - this->view.getSize().y / 2.f, this->view.getSize().x, this->view.getSize().y);
}