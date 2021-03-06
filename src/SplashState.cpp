/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SplashState.cpp
InversePalindrome.com
*/


#include "SplashState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"


SplashState::SplashState(StateMachine& stateMachine, Data data) :
    State(stateMachine, data),
    background(),
    introTime(sf::seconds(2.5f))
{
    background.setTexture(data.textures.get(Textures::SplashScreen));

    background.setOrigin(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f);
    background.setPosition(data.window.getSize().x / 2.f, data.window.getSize().y / 2.f);
}

void SplashState::handleEvent(const sf::Event & event)
{

}

void SplashState::update(sf::Time deltaTime)
{
    this->introTime -= deltaTime;

    if (introTime.asSeconds() <= 0.f)
    {
        this->stateMachine.pop();
        this->stateMachine.push(StateMachine::StateID::MenuState);
    }
}

void SplashState::draw()
{
    this->data.window.draw(background);
}