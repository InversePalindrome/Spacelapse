/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PlayState.cpp
InversePalindrome.com
*/


#include "PlayState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"


PlayState::PlayState(StateMachine& stateMachine, Data data) :
	State(stateMachine, data),
	world(data.window),
	player(data.player)
{
}

void PlayState::handleEvent(const sf::Event& event)
{
	this->player.handleEvent(event, this->world.getCommands());

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
	{
		this->stateMachine.push(StateMachine::StateID::PauseState);
	}
}

void PlayState::update(sf::Time deltaTime)
{
	this->world.update(deltaTime);
	this->player.handleInput(this->world.getCommands());
}

void PlayState::draw()
{
	this->world.draw();
}