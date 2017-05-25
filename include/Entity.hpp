/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Entity.hpp
InversePalindrome.com
*/


#pragma once

#include "SceneNode.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>


class Entity : public SceneNode
{
public:
	Entity();

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float xVelocity, float yVelocity);

	void accelerate(sf::Vector2f velocity);
	void accelerate(float xVelocity, float yVelocity);

	sf::Vector2f getVelocity() const;

	void setRemovalStatus(bool status);

    bool getRemovalStatus() const;

protected:
	virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands) override;

private:
	sf::Vector2f velocity;
	bool removalStatus;
};