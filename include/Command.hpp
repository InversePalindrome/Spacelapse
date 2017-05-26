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
	enum Category 
	{
		UndefinedCategory = 0, Scene = 1 << 0, Sound = 1 << 1, Player = 1 << 2, Asteroid = 1 << 3, Projectile = 1 << 4, 
		BluePointTarget = 1 << 5, GreenPointTarget = 1 << 6, YellowPointTarget = 1 << 7,

		PointTarget = BluePointTarget | GreenPointTarget | YellowPointTarget
	};

	Command();

	std::function<void(SceneNode&, sf::Time)> action;

	std::size_t category;
};


template<typename Object, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function function)
{
	return [=] (SceneNode& node, sf::Time deltaTime)
	{
		function(static_cast<Object&>(node), deltaTime);
	};
}