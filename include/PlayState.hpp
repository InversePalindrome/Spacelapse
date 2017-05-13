/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PlayState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"


class PlayState : public State
{
public:
	PlayState(StateMachine& stateMachine, Data data);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	World world;
	Player& player;
};