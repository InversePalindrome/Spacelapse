/*
Copyright (c) 2017 InversePalindrome
Spacelapse - State.hpp
InversePalindrome.com
*/


#pragma once

#include "World.hpp"
#include "Player.hpp"
#include "Spaceship.hpp"
#include "SoundPlayer.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>


class StateMachine;

class State
{
public:
    struct Data
    {
        Data(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureManager& textures, ImageManager& images,
            SoundPlayer& soundPlayer, Player& player, Spaceship::Type& spaceshipType, std::array<std::size_t, 9>& scores);

        sf::RenderWindow& window;
        sfg::SFGUI& gui;
        sfg::Desktop& hud;
        TextureManager& textures;
        ImageManager& images;
        SoundPlayer& soundPlayer;
        Player& player;
        Spaceship::Type& spaceshipType;
        std::array<std::size_t, 9>& scores;
    };

    State(StateMachine& stateMachine, Data data);

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw() = 0;

protected:
    StateMachine& stateMachine;
    Data data;
};