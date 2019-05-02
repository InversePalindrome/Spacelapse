/*
Copyright (c) 2017 InversePalindrome
Spacelapse - GameOverState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"

#include <SFGUI/Label.hpp>
#include <SFGUI/Button.hpp>
#include <SFML/Graphics/Sprite.hpp>


class GameOverState : public State
{
public:
    GameOverState(StateMachine& stateMachine, Data data);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void draw() override;

private:
    sf::Sprite background;
    sfg::Label::Ptr scoreLabel;
    sfg::Button::Ptr playButton;
    sfg::Button::Ptr quitButton;

    void transitionToMenu();
    void transitionToPlay();
};