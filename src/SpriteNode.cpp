/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SpriteNode.cpp
InversePalindrome.com
*/


#include "SpriteNode.hpp"


SpriteNode::SpriteNode(const sf::Texture& texture) :
    sprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle) :
    sprite(texture, rectangle)
{
}

void SpriteNode::setTextureRect(const sf::IntRect& rectangle)
{
    this->sprite.setTextureRect(rectangle);
}

void SpriteNode::drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->sprite, states);
}