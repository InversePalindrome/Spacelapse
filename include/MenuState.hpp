/*
Copyright (c) 2017 InversePalindrome
Spacelapse - MenuState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>


class MenuState : public State
{
public:
	MenuState(StateMachine& stateMachine, Data data);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	sf::Sprite background;
	sfg::Button::Ptr playButton;
	sfg::Button::Ptr spaceshipsButton;
	sfg::Button::Ptr highScoresButton;

	void transitionToPlay();
	void transitionToSpaceshipSelection();
	void transitionToHighScores();
};