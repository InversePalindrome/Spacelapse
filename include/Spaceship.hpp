/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Spaceship.hpp
InversePalindrome.com
*/


#pragma once

#include "Entity.hpp"

#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Spaceship : public Entity
{
public:
	enum class Type { Blue };

	Spaceship(Type type, TextureManager& textures);

	virtual std::size_t getCategory() const override;

private:
	Type type;
	sf::Sprite sprite;

	virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands) override;
	virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override;

	Textures getTexture() const;
};