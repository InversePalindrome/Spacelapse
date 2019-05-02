/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PlayState.cpp
InversePalindrome.com
*/


#include "PlayState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"


PlayState::PlayState(StateMachine& stateMachine, Data data) :
    State(stateMachine, data),
    player(data.player),
    world(data.window, data.textures, data.soundPlayer, data.spaceshipType, data.scores.back()),
    scoreLabel()
{
    scoreLabel = sfg::Label::Create("SCORE:  ");
    scoreLabel->SetPosition(sf::Vector2f(1820.f, 80.f));
    scoreLabel->SetId("score");

    data.hud.SetProperty("Label#score", "FontSize", 60.f);
    data.hud.SetProperty("Label#score", "FontName", "Resources/Fonts/Bebas.ttf");
    data.hud.Add(scoreLabel);
}

void PlayState::handleEvent(const sf::Event& event)
{
    this->player.handleEvent(event, this->world.getCommands());
    this->data.hud.HandleEvent(event);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
    {
        this->scoreLabel->Show(false);

        this->stateMachine.push(StateMachine::StateID::PauseState);
    }
}

void PlayState::update(sf::Time deltaTime)
{
    this->scoreLabel->Show(true);
    this->scoreLabel->SetText("SCORE:  " + std::to_string(this->data.scores.back()));

    this->world.update(deltaTime);
    this->data.hud.Update(deltaTime.asMicroseconds());

    if (this->world.getGameEndedStatus())
    {
        this->scoreLabel->Show(false);

        this->stateMachine.pop();
        this->stateMachine.push(StateMachine::StateID::GameOverState);
    }

    this->player.handleInput(this->world.getCommands());
}

void PlayState::draw()
{
    this->world.draw();
    this->data.gui.Display(this->data.window);
}