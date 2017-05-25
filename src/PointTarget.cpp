/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PointTarget.cpp
InversePalindrome.com
*/


#include "PointTarget.hpp"


PointTarget::PointTarget(Type type, TextureManager& textures) :
	type(type),
	sprite(textures.get(getTexture())),
	points(getPoints())
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setScale(0.4f, 0.4f);
}

std::size_t PointTarget::getPoints() const
{
	return this->points;
}

bool PointTarget::isMarkedForRemoval() const
{
	return this->getRemovalStatus();
}

sf::FloatRect PointTarget::getPerimeter() const
{
	return this->getAbsoluteTransform().transformRect(this->sprite.getGlobalBounds());
}

std::size_t PointTarget::getCategory() const
{
	switch (this->type)
	{
	case Type::BlueTarget:
		return Command::Category::BluePointTarget;
	case Type::GreenTarget:
		return Command::Category::GreenPointTarget;
	}
}

void PointTarget::updateCurrentNode(sf::Time deltaTime, CommandQueue& commands)
{
	Entity::updateCurrentNode(deltaTime, commands);
}

void PointTarget::drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}

Textures PointTarget::getTexture() const
{
	switch (this->type)
	{
	case Type::BlueTarget:
		return Textures::BluePointTarget;
	case Type::GreenTarget:
		return Textures::GreenPointTarget;
	}
}

std::size_t PointTarget::getTypePoints() const
{
	switch (this->type)
	{
	case Type::BlueTarget:
		return 5;
	case Type::GreenTarget:
		return 10;
	}
}