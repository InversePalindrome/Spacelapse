/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Projectile.cpp
InversePalindrome.com
*/


#include "Projectile.hpp"


Projectile::Projectile(Type type, TextureManager& textures) :
    type(type),
    sprite(textures.get(getTexture()))
{
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

bool Projectile::isMarkedForRemoval() const
{
    return this->getRemovalStatus();
}

std::size_t Projectile::getCategory() const
{
    return Command::Category::Projectile;
}

sf::FloatRect Projectile::getPerimeter() const
{
    return this->getAbsoluteTransform().transformRect(this->sprite.getGlobalBounds());
}

void Projectile::updateCurrentNode(sf::Time deltaTime, CommandQueue & commands)
{
    Entity::updateCurrentNode(deltaTime, commands);
}

void Projectile::drawCurrentNode(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(this->sprite, states);
}

Textures Projectile::getTexture() const
{
    switch (this->type)
    {
    case Type::FireProjectile:
        return Textures::FireProjectile;
    }
}