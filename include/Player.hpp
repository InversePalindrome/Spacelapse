/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Player.hpp
InversePalindrome.com
*/


#pragma once

#include "CommandQueue.hpp"
#include "Spaceship.hpp"

#include <SFML/Window/Event.hpp>

#include <map>


class Player
{
public:
	enum class Action { MoveUp, MoveDown, MoveRight, MoveLeft, ActionCount };

	Player();

	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleInput(CommandQueue& commands);

	void setKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getKey(Action action) const;

private:
	struct SpaceshipMovement
	{
		SpaceshipMovement(float xVelocity, float yVelocity);

		void operator()(Spaceship& spaceship, sf::Time) const;

		sf::Vector2f velocity;
	};

	std::map<sf::Keyboard::Key, Action> keyActions;
	std::map <Action, Command> actionCommands;

	static bool isInput(Action action);
};