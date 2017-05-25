/*
Copyright (c) 2017 InversePalindrome
Spacelapse - World.cpp
InversePalindrome.com
*/


#include "World.hpp"
#include "Asteroid.hpp"
#include "SoundNode.hpp"
#include "Projectile.hpp"
#include "PointTarget.hpp"

#include <random>


const float World::increasedCameraStep = 10.f;
const float World::timePerSpawn = 2.f;

World::World(sf::RenderWindow& window, TextureManager& textures, SoundPlayer& soundPlayer, Spaceship::Type& spaceshipType, std::size_t& score) :
	window(window),
	view(window.getDefaultView()),
	textures(textures),
	soundPlayer(soundPlayer),
	sceneGraph(),
	sceneLayers(),
	commands(),
	backgroundPerimeter(0.f, 0.f, view.getSize().x, view.getSize().y),
	spawnTime(sf::Time::Zero),
	score(score),
	cameraSpeed(500.f),
	background(nullptr),
	player(nullptr),
	spaceshipType(spaceshipType),
	entityPositions(),
	gameEnded(false)
{
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

	auto soundNode = std::make_unique<SoundNode>(soundPlayer);
	sceneGraph.addChild(std::move(soundNode));
	
    auto spaceship = std::make_unique<Spaceship>(spaceshipType, textures);
    player = spaceship.get();
    player->setPosition(sf::Vector2f(250.f, view.getSize().y / 2.f));
    sceneLayers[static_cast<std::size_t>(Layer::Space)]->addChild(std::move(spaceship));

    this->spawnEntities();
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
	this->updateSounds();
	this->updatePlayerVelocity();
	this->updatePlayerPosition();

	this->handleCollisions();

    this->spawnTime += deltaTime;

    this->sceneGraph.removeMarkedNodes();

	if (this->spawnTime.asSeconds() >= this->timePerSpawn)
	{
		this->deleteMarkedEntities();
		this->spawnEntities();
		this->cameraSpeed += this->increasedCameraStep;
		this->spawnTime = sf::Time::Zero;
	}

    this->sceneGraph.update(deltaTime, this->commands);
}

void World::draw()
{
	this->window.setView(this->view);
	this->window.draw(this->sceneGraph);
}

CommandQueue& World::getCommands()
{
	return this->commands;
}

void World::endGame()
{
	this->gameEnded = true;
}

bool World::getGameEndedStatus() const
{
	return this->gameEnded;
}

void World::updateBackground()
{
	this->background->setTextureRect(sf::IntRect(this->view.getCenter().x - this->view.getSize().x / 2.f, 0.f, this->backgroundPerimeter.width, this->backgroundPerimeter.height));
	this->background->setPosition(this->view.getCenter().x - this->view.getSize().x / 2.f, 0.f);
}

void World::updateSounds()
{
	this->soundPlayer.setListenerPosition(this->player->getAbsolutePosition());

	this->soundPlayer.removeStoppedSounds();
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
	const float borderDistance = 80.f;

	position.x = std::max(position.x, viewRange.left + borderDistance);
	position.x = std::min(position.x, viewRange.left + viewRange.width - borderDistance);
	position.y = std::max(position.y, viewRange.top + borderDistance);
	position.y = std::min(position.y, viewRange.top + viewRange.height - borderDistance);

	this->player->setPosition(position);
}

void World::handleCollisions()
{
	std::set<std::pair<SceneNode*, SceneNode*>> collisions;

	this->sceneGraph.checkSceneCollision(this->sceneGraph, collisions);

	for (auto collision : collisions)
	{
		if (this->categoriesMatch(collision, Command::Category::Player, Command::Category::Asteroid)
			|| this->categoriesMatch(collision, Command::Category::Player, Command::Category::PointTarget))
		{
			this->endGame();
		}

		else if (this->categoriesMatch(collision, Command::Category::Asteroid, Command::Category::Projectile))
		{
			auto& asteroid = static_cast<Asteroid&>(*collision.first);
			auto& projectile = static_cast<Projectile&>(*collision.second);

			projectile.setRemovalStatus(true);
		}

		else if (this->categoriesMatch(collision, Command::Category::BluePointTarget, Command::Category::Projectile))
		{
			auto& pointTarget = static_cast<PointTarget&>(*collision.first);
			auto& projectile = static_cast<Projectile&>(*collision.second);

			this->score += 5;

			pointTarget.setRemovalStatus(true);
			projectile.setRemovalStatus(true);
		}

		else if (this->categoriesMatch(collision, Command::Category::GreenPointTarget, Command::Category::Projectile))
		{
			auto& pointTarget = static_cast<PointTarget&>(*collision.first);
			auto& projectile = static_cast<Projectile&>(*collision.second);

			this->score += 10;

			pointTarget.setRemovalStatus(true);
			projectile.setRemovalStatus(true);
        }
	}
}

void World::spawnEntities()
{
	const auto& externalWorldPerimeter = this->getExternalWorldPerimeter();

	std::random_device rd;
	std::mt19937 mt(rd());
    std::uniform_int_distribution<std::size_t> distNumAsteroids(1, 4);
	std::uniform_int_distribution<std::size_t> distNumTargets(0, 2);
	std::uniform_int_distribution<std::size_t> distAngle(0, 1);
	std::uniform_real_distribution<float> distEntityType(0.0f, 1.0f);

	const std::size_t numOfAsteroids = distNumAsteroids(mt);
	const std::size_t numOfTargets = distNumTargets(mt);

	const float regularAsteroidRate = 0.7f;
	const float blueTargetRate = 0.8f;

	this->calculateEntityPositions(numOfAsteroids + numOfTargets);

	auto positions = this->entityPositions;

	for (std::size_t i = 0; i < numOfAsteroids; i++)
	{
		Asteroid::Type type = Asteroid::Type::UndefinedType;

		distEntityType(mt) < regularAsteroidRate ? type = Asteroid::Type::Regular : type = Asteroid::Type::Lava;

		auto asteroid = std::make_unique<Asteroid>(type, this->textures);
	
		asteroid->setPosition(positions.back());
		asteroid->setRotation(distAngle(mt) * 180);

		positions.pop_back();

		this->sceneLayers[static_cast<std::size_t>(Layer::Space)]->addChild(std::move(asteroid));
	}

	for (std::size_t i = 0; i < numOfTargets; i++)
	{
		PointTarget::Type type = PointTarget::Type::UndefinedType;

		distEntityType(mt) < blueTargetRate ? type = PointTarget::Type::BlueTarget : type = PointTarget::Type::GreenTarget;

		auto pointTarget = std::make_unique<PointTarget>(type, this->textures);

		pointTarget->setPosition(positions.back());
		pointTarget->setRotation(distAngle(mt) * 180);

		positions.pop_back();

		this->sceneLayers[static_cast<std::size_t>(Layer::Space)]->addChild(std::move(pointTarget));
	}
}

void World::deleteMarkedEntities()
{
	for (auto itr = this->entityPositions.begin(); itr != this->entityPositions.end();)
	{
		itr->x < this->view.getCenter().x - this->view.getSize().x ?
			itr = this->entityPositions.erase(itr) : ++itr;
	}

	Command command;

	command.category = Command::Category::Asteroid | Command::Category::PointTarget;

	command.action = derivedAction<Entity>([this](Entity& entity, sf::Time)
	{
		if (entity.getAbsolutePosition().x < this->view.getCenter().x - this->view.getSize().x)
		{
			entity.setRemovalStatus(true);
		}
	});

	this->commands.push(command);
}

sf::FloatRect World::getExternalWorldPerimeter() const
{
	const float bufferDistance = 100.f;
	return sf::FloatRect(this->view.getCenter().x + this->view.getSize().x / 2.f + bufferDistance, this->view.getCenter().y - this->view.getSize().y / 2.f, this->view.getSize().x, this->view.getSize().y);
}

void World::calculateEntityPositions(std::size_t numOfAsteroids) 
{
	std::random_device rd;
	std::mt19937 mt(rd());

	const auto& externalWorldPerimeter = this->getExternalWorldPerimeter();
	const float borderDistance = 150.f;

	std::uniform_real_distribution<float> distX(externalWorldPerimeter.left + borderDistance, externalWorldPerimeter.left + externalWorldPerimeter.width);
	std::uniform_real_distribution<float> distY(externalWorldPerimeter.top + borderDistance, externalWorldPerimeter.top + externalWorldPerimeter.height - borderDistance);

	if (this->entityPositions.empty())
	{
		this->entityPositions.push_back(sf::Vector2f(distX(mt), distY(mt)));
	}

	for (std::size_t i = 0; i < numOfAsteroids; i++)
	{
		bool isCorrectlyPositioned = false;

		sf::Vector2f randomPosition;

		while (!isCorrectlyPositioned)
		{
			randomPosition.x = distX(mt);
			randomPosition.y = distY(mt);

			for (std::size_t j = 0; j < this->entityPositions.size(); j++)
			{
				if (std::sqrt(std::pow(randomPosition.y - this->entityPositions.at(j).y, 2) + std::pow(randomPosition.x - this->entityPositions.at(j).x, 2)) < 300.f)
				{
					break;
				}

				if (j == this->entityPositions.size() - 1)
				{
					isCorrectlyPositioned = true;
				}
			}
		}

		this->entityPositions.push_back(randomPosition);
	}
}

bool World::categoriesMatch(std::pair<SceneNode*, SceneNode*>& collision, Command::Category type1, Command::Category type2)
{
	auto category1 = collision.first->getCategory();
	auto category2 = collision.second->getCategory();

	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(collision.first, collision.second);
		return true;
	}
	else
	{
		return false;
	}
}