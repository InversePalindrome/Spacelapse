/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Spaceship.cpp
InversePalindrome.com
*/


#include "Spaceship.hpp"


Spaceship::Spaceship(Type type, TextureManager& textures) :
	type(type),
	sprite(textures.get(getTexture()))
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

std::size_t Spaceship::getCategory() const
{
	return static_cast<std::size_t>(Command::Category::Player);
}

void Spaceship::updateCurrentNode(sf::Time deltaTime, CommandQueue& commands)
{
	Entity::updateCurrentNode(deltaTime, commands);
}

void Spaceship::drawCurrentNode(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->sprite, state);
}

Textures Spaceship::getTexture() const
{
	switch (this->type)
	{
	case Type::Blue:
		return Textures::BlueSpaceship;
	}
}