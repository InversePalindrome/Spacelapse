/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Command.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/System/Time.hpp>

#include <functional>


class SceneNode;

struct Command
{
	enum class Category { UndefinedCategory = 0, Scene = 1 << 0, Player = 1 << 1, Asteroid = 1 << 2 };

	Command();

	std::function<void(SceneNode&, sf::Time)> action;

	Category category;
};


template<typename Object, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function function)
{
	return [=] (SceneNode& node, sf::Time deltaTime)
	{
		function(static_cast<Object&>(node), deltaTime);
	};
}