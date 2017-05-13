/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Asteroid.cpp
InversePalindrome.com
*/


#include "Asteroid.hpp"


Asteroid::Asteroid(Type type, TextureManager& textures) :
	type(type),
	sprite(textures.get(getTexture()))
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
	sprite.setScale(0.6f, 0.6f);
}

std::size_t Asteroid::getCategory() const
{
	return static_cast<std::size_t>(Command::Category::Asteroid);
}

void Asteroid::updateCurrentNode(sf::Time deltaTime, CommandQueue& commands)
{
	Entity::updateCurrentNode(deltaTime, commands);
}

void Asteroid::drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}

Textures Asteroid::getTexture() const
{
	switch (this->type)
	{
	case Type::Regular:
		return Textures::RegularAsteroid;
	case Type::Lava:
		return Textures::LavaAsteroid;
	}
}