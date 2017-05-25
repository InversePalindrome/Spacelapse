/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SpaceshipSelectionState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "Spaceship.hpp"

#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>


class SpaceshipSelectionState : public State
{
public:
	SpaceshipSelectionState(StateMachine& stateMachine, Data data);

	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw() override;

private:
	struct Selection
	{
		Selection(Data data, Textures spaceshipTexture, sf::Vector2f position);

		sf::Sprite spaceshipSprite;
		sfg::Button::Ptr spaceshipButton;
	};

	sf::Sprite background;
	sfg::Button::Ptr menuButton;
	std::map<Spaceship::Type, Selection> spaceshipSelections;

	void selectSpaceship(Spaceship::Type spaceshipType);
};