/*
Copyright (c) 2017 InversePalindrome
Spacelapse - State.cpp
InversePalindrome.com
*/


#include "State.hpp"
#include "StateMachine.hpp"


State::Data::Data(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureManager& textures, ImageManager& images,
    SoundPlayer& soundPlayer, Player& player, Spaceship::Type& spaceshipType, std::array<std::size_t, 9>& scores) :
    window(window),
    gui(gui),
    hud(hud),
    textures(textures),
    images(images),
    soundPlayer(soundPlayer),
    player(player),
    spaceshipType(spaceshipType),
    scores(scores)
{
}

State::State(StateMachine& stateMachine, Data data) :
    stateMachine(stateMachine),
    data(data)
{
}