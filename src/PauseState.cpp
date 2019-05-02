/*
Copyright (c) 2017 InversePalindrome
Spacelapse - PauseState.cpp
InversePalindrome.com
*/


#pragma once

#include "PauseState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


PauseState::PauseState(StateMachine& stateMachine, Data data) :
    State(stateMachine, data),
    background(),
    scoreLabel(),
    quitButton(),
    playButton()
{
    data.window.setView(data.window.getDefaultView());

    auto& backgroundTexture = data.textures.get(Textures::PauseBackground);
    backgroundTexture.setRepeated(true);

    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, 2 * data.window.getSize().x, data.window.getSize().y));

    scoreLabel = sfg::Label::Create("SCORE:   " + std::to_string(this->data.scores.back()));
    scoreLabel->SetPosition(sf::Vector2f(1020.f, 500.f));
    scoreLabel->SetId("bigScore2");

    quitButton = sfg::Button::Create();
    quitButton->SetImage(sfg::Image::Create(data.images.get(Images::QuitButton)));
    quitButton->SetPosition(sf::Vector2f(1020.f, 700.f));
    quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { return transitionToMenu(); });

    playButton = sfg::Button::Create();
    playButton->SetImage(sfg::Image::Create(data.images.get(Images::PlayButton)));
    playButton->SetPosition(sf::Vector2f(1020.f, 900.f));
    playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { return transitionToPlay(); });

    data.hud.SetProperty("Label#bigScore2", "FontSize", 85.f);
    data.hud.SetProperty("Label#bigScore2", "FontName", "Resources/Fonts/Bebas.ttf");
    data.hud.Add(scoreLabel);
    data.hud.Add(quitButton);
    data.hud.Add(playButton);
}

void PauseState::handleEvent(const sf::Event & event)
{
    this->data.hud.HandleEvent(event);
}

void PauseState::update(sf::Time deltaTime)
{
    this->data.hud.Update(deltaTime.asMicroseconds());
}

void PauseState::draw()
{
    this->data.window.draw(this->background);
    this->data.gui.Display(this->data.window);
}

void PauseState::transitionToMenu()
{
    this->scoreLabel->Show(false);
    this->quitButton->Show(false);
    this->playButton->Show(false);

    std::sort(this->data.scores.rbegin(), this->data.scores.rend());
    this->data.scores.back() = 0;

    this->stateMachine.clear();
    this->stateMachine.push(StateMachine::StateID::MenuState);
}

void PauseState::transitionToPlay()
{
    this->scoreLabel->Show(false);
    this->quitButton->Show(false);
    this->playButton->Show(false);
    this->stateMachine.pop();
}