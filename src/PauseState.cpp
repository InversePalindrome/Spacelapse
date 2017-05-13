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
	quitButton(),
	playButton()
{
	data.window.setView(data.window.getDefaultView());

	data.textures.load(Textures::PauseBackground, "Resources/Images/SpaceBackground2.jpg");
	data.images.load(Images::QuitButton, "Resources/Images/QuitButton.png");
	data.images.load(Images::PlayButton, "Resources/Images/PlayButton.png");

	auto& backgroundTexture = data.textures.get(Textures::PauseBackground);
	backgroundTexture.setRepeated(true);
	
	background.setTexture(backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0,  2 * data.window.getSize().x, data.window.getSize().y));

	quitButton = sfg::Button::Create();
	quitButton->SetImage(sfg::Image::Create(data.images.get(Images::QuitButton)));
	quitButton->SetPosition(sf::Vector2f(1020.f, 550.f));
	quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { return transitionToMenu(); });

	playButton = sfg::Button::Create();
	playButton->SetImage(sfg::Image::Create(data.images.get(Images::PlayButton)));
	playButton->SetPosition(sf::Vector2f(1020.f, 800.f));
	playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { return transitionToPlay(); });

	data.hud.Add(quitButton);
	data.hud.Add(playButton);
}

void PauseState::handleEvent(const sf::Event& event)
{
	this->data.hud.HandleEvent(event);
}

void PauseState::update(sf::Time deltaTime)
{
	this->quitButton->Show(true);
	this->data.hud.Update(deltaTime.asMicroseconds());
}

void PauseState::draw()
{
	this->data.window.draw(this->background);
	this->data.gui.Display(this->data.window);
}

void PauseState::transitionToMenu()
{
	this->quitButton->Show(false);
	this->playButton->Show(false);
	this->stateMachine.clear();
	this->stateMachine.push(StateMachine::StateID::MenuState);
}

void PauseState::transitionToPlay()
{
	this->quitButton->Show(false);
	this->playButton->Show(false);
	this->stateMachine.pop();
}