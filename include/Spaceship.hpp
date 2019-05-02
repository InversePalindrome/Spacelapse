/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Spaceship.hpp
InversePalindrome.com
*/


#pragma once

#include "Entity.hpp"
#include "Command.hpp"
#include "Projectile.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Spaceship : public Entity
{
public:
    enum class Type { UndefinedSpaceship, BlueSpaceship, RedSpaceship, GreenSpaceship, YellowSpaceship };

    Spaceship(Type type, TextureManager& textures);

    void shoot();

    void playLocalSound(CommandQueue& commands, Sounds sound);

    virtual std::size_t getCategory() const override;

    virtual sf::FloatRect getPerimeter() const override;

private:
    Type type;
    sf::Sprite sprite;
    Command shootCommand;
    sf::Time shootingTime;
    sf::Time activeTime;
    bool isShooting;

    virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands) override;
    virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const override;

    void createProjectile(SceneNode& node, Projectile::Type type, TextureManager& textures) const;

    Textures getTexture() const;
};