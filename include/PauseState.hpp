/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PauseState.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "World.hpp"

#include <SFGUI/Label.hpp>
#include <SFGUI/Button.hpp>


class PauseState : public State
{
public:
    PauseState(StateMachine& stateMachine, Data data);

    virtual void handleEvent(const sf::Event& event) override;
    virtual void update(sf::Time deltaTime) override;
    virtual void draw() override;

private:
    sf::Sprite background;
    sfg::Label::Ptr scoreLabel;
    sfg::Button::Ptr quitButton;
    sfg::Button::Ptr playButton;

    void transitionToMenu();
    void transitionToPlay();
};