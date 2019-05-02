/*
Copyright (c) 2017 InversePalindrome
Spacelapse - World.hpp
InversePalindrome.com
*/


#pragma once

#include "SceneNode.hpp"
#include "Spaceship.hpp"
#include "SoundPlayer.hpp"
#include "SpriteNode.hpp"
#include "CommandQueue.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <array>


class World
{
public:
    World(sf::RenderWindow& window, TextureManager& textures, SoundPlayer& soundPlayer, Spaceship::Type& spaceshipType, std::size_t& score);

    void update(sf::Time deltaTime);
    void draw();

    CommandQueue& getCommands();

    void endGame();

    bool getGameEndedStatus() const;

private:
    enum class Layer { Background, Space, Size };

    sf::RenderWindow& window;
    sf::View view;

    TextureManager& textures;
    SoundPlayer& soundPlayer;

    SceneNode sceneGraph;
    std::array<SceneNode*, static_cast<std::size_t>(Layer::Size)> sceneLayers;
    CommandQueue commands;

    sf::FloatRect backgroundPerimeter;
    sf::Time spawnTime;
    std::size_t& score;
    float cameraSpeed;
    static const float increasedCameraStep;
    static const float timePerSpawn;

    SpriteNode* background;
    Spaceship* player;

    Spaceship::Type& spaceshipType;

    std::vector<sf::Vector2f> entityPositions;

    bool gameEnded;

    void updateBackground();
    void updateSounds();
    void updatePlayerVelocity();
    void updatePlayerPosition();

    void handleCollisions();

    void spawnEntities();
    void deleteMarkedEntities();

    sf::FloatRect getExternalWorldPerimeter() const;
    void calculateEntityPositions(std::size_t numOfAsteroids);

    bool categoriesMatch(std::pair<SceneNode*, SceneNode*>& collisions, Command::Category type1, Command::Category type2);
};