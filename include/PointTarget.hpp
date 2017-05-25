/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PointTarget.hpp
InversePalindrome.com
*/


#pragma once

#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class PointTarget : public Entity
{
public:
	enum class Type { UndefinedType, BlueTarget, GreenTarget };

	PointTarget(Type type, TextureManager& textures);

	std::size_t getPoints() const;

	virtual bool isMarkedForRemoval() const override;

	virtual std::size_t getCategory() const override;

	virtual sf::FloatRect getPerimeter() const override;

private:
	Type type;
	sf::Sprite sprite;
	std::size_t points;

	virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands) override;
	virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override;

	Textures getTexture() const;
	std::size_t getTypePoints() const;
};
