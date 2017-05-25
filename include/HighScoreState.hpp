/*
Copyright (c) 2017 InversePalindrome
Spacelapse - OptionsState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Label.hpp>
#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>


class HighScoreState : public State
{
public:
    HighScoreState(StateMachine& stateMachine, Data data);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	sf::Sprite background;
	std::array<sfg::Label::Ptr, 9> scoreLabels;
	sfg::Button::Ptr menuButton;
};
