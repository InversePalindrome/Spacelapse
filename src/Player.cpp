/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Player.cpp
InversePalindrome.com
*/


#include "Player.hpp"


Player::Player() :
    keyActions(),
    actionCommands()
{
    keyActions[sf::Keyboard::W] = Player::Action::MoveUp;
    keyActions[sf::Keyboard::S] = Player::Action::MoveDown;
    keyActions[sf::Keyboard::D] = Player::Action::MoveRight;
    keyActions[sf::Keyboard::A] = Player::Action::MoveLeft;
    keyActions[sf::Keyboard::Space] = Player::Action::Fire;

    const float playerSpeed = 600.f;

    actionCommands[Player::Action::MoveUp].action = derivedAction<Spaceship>(SpaceshipMovement(0.f, -playerSpeed));
    actionCommands[Player::Action::MoveDown].action = derivedAction<Spaceship>(SpaceshipMovement(0.f, playerSpeed));
    actionCommands[Player::Action::MoveRight].action = derivedAction<Spaceship>(SpaceshipMovement(playerSpeed, 0.f));
    actionCommands[Player::Action::MoveLeft].action = derivedAction<Spaceship>(SpaceshipMovement(2 * -playerSpeed, 0.f));
    actionCommands[Player::Action::Fire].action = derivedAction<Spaceship>([&](Spaceship & spaceship, sf::Time) { return spaceship.shoot(); });

    for (auto& actionCommand : actionCommands)
    {
        actionCommand.second.category = Command::Category::Player;
    }
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto key = this->keyActions.find(event.key.code);

        if (key != this->keyActions.end() && !isInput(key->second))
        {
            commands.push(this->actionCommands[key->second]);
        }
    }
}

void Player::handleInput(CommandQueue& commands)
{
    for (auto& key : this->keyActions)
    {
        if (sf::Keyboard::isKeyPressed(key.first) && isInput(key.second))
        {
            commands.push(this->actionCommands[key.second]);
        }
    }
}

void Player::setKey(Action action, sf::Keyboard::Key key)
{
    for (auto itr = this->keyActions.begin(); itr != this->keyActions.end(); )
    {
        itr->second == action ?
            this->keyActions.erase(itr++) : ++itr;
    }

    this->keyActions[key] = action;
}

sf::Keyboard::Key Player::getKey(Action action) const
{
    for (const auto& key : this->keyActions)
    {
        if (key.second == action)
        {
            return key.first;
        }
    }

    return sf::Keyboard::Unknown;
}

Player::SpaceshipMovement::SpaceshipMovement(float xVelocity, float yVelocity) :
    velocity(xVelocity, yVelocity)
{
}

void Player::SpaceshipMovement::operator()(Spaceship& spaceship, sf::Time) const
{
    spaceship.accelerate(velocity);
}

bool Player::isInput(Action action)
{
    switch (action)
    {
    case Player::Action::MoveUp:
    case Player::Action::MoveDown:
    case Player::Action::MoveRight:
    case Player::Action::MoveLeft:
    case Player::Action::Fire:
        return true;
    default:
        return false;
    }
}