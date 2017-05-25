/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Asteroid.hpp
InversePalindrome.com
*/


#pragma once

#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Asteroid : public Entity
{
public:
	enum class Type { UndefinedType, Regular, Lava };

	Asteroid(Type type, TextureManager& textures);

	virtual bool isMarkedForRemoval() const override;

	virtual std::size_t getCategory() const override;

	virtual sf::FloatRect getPerimeter() const override;

private:
	Type type;
	sf::Sprite sprite;

	virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands) override;
	virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override;

	Textures getTexture() const;
};