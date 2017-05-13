/*
Copyright (c) 2017 InversePalindrome
Spacelapse - State.cpp
InversePalindrome.com
*/


#include "State.hpp"
#include "StateMachine.hpp"


State::Data::Data(sf::RenderWindow& window, sfg::SFGUI& gui, sfg::Desktop& hud, TextureManager& textures, ImageManager& images, Player& player) :
	window(window),
	gui(gui),
	hud(hud),
	textures(textures),
	images(images),
	player(player)
{
}

State::State(StateMachine& stateMachine, Data data) :
	stateMachine(stateMachine),
	data(data)
{
}