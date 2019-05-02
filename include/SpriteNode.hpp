/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SpriteNode.hpp
InversePalindrome.com
*/


#pragma once

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>


class SpriteNode : public SceneNode
{
public:
    SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle);

    void setTextureRect(const sf::IntRect& rectangle);

private:
    sf::Sprite sprite;

    virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override;
};