/*
Copyright (c) 2017 InversePalindrome
Spacelapse - World.hpp
InversePalindrome.com
*/


#pragma once

#include "Asteroid.hpp"
#include "SceneNode.hpp"
#include "Spaceship.hpp"
#include "SpriteNode.hpp"
#include "CommandQueue.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/Clock.hpp>

#include <array>


class World
{
public:
	World(sf::RenderTarget& target);

	void update(sf::Time deltaTime);
	void draw();

	CommandQueue& getCommands();

private:
	enum class Layer { Background, Space, Size };

	sf::RenderTarget& target;
	sf::View view;

	TextureManager textures;

	SceneNode sceneGraph;
	std::array<SceneNode*, static_cast<std::size_t>(Layer::Size)> sceneLayers;
	CommandQueue commands;

	sf::FloatRect backgroundPerimeter;
	sf::Clock timer;
	float cameraSpeed;
	static const float increasedCameraStep;
	static const float timePerSpawn;

	SpriteNode* background;
	Spaceship* player;
	std::vector<Asteroid*> asteroids;

	void updateBackground();
	void updatePlayerVelocity();
	void updatePlayerPosition();

	void spawnAsteroids();
	void deleteUnusedAsteroids();

	sf::FloatRect getExternalWorldPerimeter() const;
};