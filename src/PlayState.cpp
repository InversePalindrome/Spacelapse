/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PlayState.cpp
InversePalindrome.com
*/


#include "PlayState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"


PlayState::PlayState(StateMachine& stateMachine, Data data) :
	State(stateMachine, data)
{
}

void PlayState::handleEvent(const sf::Event& event)
{

}

void PlayState::update(sf::Time deltaTime)
{
	
}

void PlayState::draw()
{

}