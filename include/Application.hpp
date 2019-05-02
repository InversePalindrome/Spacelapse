/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Application.hpp
InversePalindrome.com
*/


#pragma once

#include "World.hpp"
#include "Player.hpp"
#include "SoundPlayer.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <array>


class Application
{
public:
    Application();

    void run();

private:
    void processInput();
    void update(sf::Time deltaTime);
    void render();

    void saveData();

    void loadData();
    void loadTextures();

    sf::RenderWindow window;
    sfg::SFGUI gui;
    sfg::Desktop hud;

    StateMachine stateMachine;
    TextureManager textures;
    ImageManager images;
    SoundPlayer soundPlayer;
    Player player;
    Spaceship::Type spaceshipType;

    std::array<std::size_t, 9> scores;
};