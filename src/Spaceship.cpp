/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Spaceship.cpp
InversePalindrome.com
*/


#include "Spaceship.hpp"
#include "SoundNode.hpp"


Spaceship::Spaceship(Type type, TextureManager& textures) :
    type(type),
    sprite(textures.get(getTexture())),
    shootCommand(),
    shootingTime(sf::Time::Zero),
    isShooting(false)
{
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    sprite.setScale(0.6f, 0.6f);

    shootCommand.category = static_cast<std::size_t>(Command::Category::Scene);

    shootCommand.action = [this, &textures](SceneNode & node, sf::Time)
    {
        createProjectile(node, Projectile::Type::FireProjectile, textures);
    };
}

void Spaceship::shoot()
{
    this->isShooting = true;
}

void Spaceship::playLocalSound(CommandQueue & commands, Sounds sound)
{
    Command command;
    command.category = Command::Category::Sound;

    command.action = derivedAction<SoundNode>(
        [sound, this](SoundNode & node, sf::Time) { node.playSound(sound, this->getAbsolutePosition()); });

    commands.push(command);
}

std::size_t Spaceship::getCategory() const
{
    return Command::Category::Player;
}

sf::FloatRect Spaceship::getPerimeter() const
{
    return this->getAbsoluteTransform().transformRect(this->sprite.getGlobalBounds());
}

void Spaceship::updateCurrentNode(sf::Time deltaTime, CommandQueue & commands)
{
    if (this->isShooting && this->activeTime.asSeconds() > 4.5f && this->shootingTime.asSeconds() > 1.f)
    {
        commands.push(this->shootCommand);

        this->playLocalSound(commands, Sounds::LaserShot);

        this->shootingTime = sf::Time::Zero;
    }

    this->activeTime += deltaTime;
    this->shootingTime += deltaTime;
    this->isShooting = false;

    Entity::updateCurrentNode(deltaTime, commands);
}

void Spaceship::drawCurrentNode(sf::RenderTarget & target, sf::RenderStates state) const
{
    target.draw(this->sprite, state);
}

void Spaceship::createProjectile(SceneNode & node, Projectile::Type type, TextureManager & textures) const
{
    auto projectile = std::make_unique<Projectile>(type, textures);

    const float xOffset = 125.f;
    const sf::Vector2f velocity(2000.f, 0.f);

    projectile->setPosition(this->getPosition().x + xOffset, this->getPosition().y);
    projectile->setVelocity(velocity);

    node.addChild(std::move(projectile));
}

Textures Spaceship::getTexture() const
{
    switch (this->type)
    {
    case Type::BlueSpaceship:
        return Textures::BlueSpaceship;
    case Type::RedSpaceship:
        return Textures::RedSpaceship;
    case Type::GreenSpaceship:
        return Textures::GreenSpaceship;
    case Type::YellowSpaceship:
        return Textures::YellowSpaceship;
    default:
        return Textures::BlueSpaceship;
    }
}