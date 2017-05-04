/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SplashState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>


class SplashState : public State
{
public:
	SplashState(StateMachine& stateMachine, Data data);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	sf::Sprite background;
	sf::Clock timer;
};