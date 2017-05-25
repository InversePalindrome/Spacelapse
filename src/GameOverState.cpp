/*
Copyright (c) 2017 InversePalindrome
Spacelapse - GameOverState.cpp
InversePalindrome.com
*/


#include "GameOverState.hpp"
#include "StateMachine.hpp"

#include <SFGUI/Image.hpp>


GameOverState::GameOverState(StateMachine& stateMachine, Data data) :
	State(stateMachine, data),
	background(),
	scoreLabel(),
	playButton(),
	quitButton()
{
	data.window.setView(data.window.getDefaultView());

	auto& backgroundTexture = data.textures.get(Textures::GameOverBackground);
	backgroundTexture.setRepeated(true);

	background.setTexture(backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0, 2 * data.window.getSize().x, data.window.getSize().y));

	scoreLabel = sfg::Label::Create("SCORE:  " + std::to_string(this->data.scores.back()));
	scoreLabel->SetPosition(sf::Vector2f(1020.f, 500.f));
	scoreLabel->SetId("bigScore");
	
	quitButton = sfg::Button::Create();
	quitButton->SetImage(sfg::Image::Create(data.images.get(Images::QuitButton)));
	quitButton->SetPosition(sf::Vector2f(1020.f, 700.f));
	quitButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { return transitionToMenu(); });

	playButton = sfg::Button::Create();
	playButton->SetImage(sfg::Image::Create(data.images.get(Images::PlayButton)));
	playButton->SetPosition(sf::Vector2f(1020.f, 900.f));
	playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { return transitionToPlay(); });

	data.hud.SetProperty("Label#bigScore", "FontSize", 85.f);
	data.hud.SetProperty("Label#bigScore", "FontName", "Resources/Fonts/Bebas.ttf");
	data.hud.Add(scoreLabel);
	data.hud.Add(quitButton);
	data.hud.Add(playButton);
}

void GameOverState::handleEvent(const sf::Event& event)
{
	this->data.hud.HandleEvent(event);
}

void GameOverState::update(sf::Time deltaTime)
{
	this->data.hud.Update(deltaTime.asMicroseconds());
}

void GameOverState::draw()
{
	this->data.window.draw(this->background);
	this->data.gui.Display(this->data.window);
}

void GameOverState::transitionToMenu()
{
	this->scoreLabel->Show(false);
	this->quitButton->Show(false);
	this->playButton->Show(false);
	
	std::sort(this->data.scores.rbegin(), this->data.scores.rend());
	this->data.scores.back() = 0;

	this->stateMachine.pop();
	this->stateMachine.push(StateMachine::StateID::MenuState);
}

void GameOverState::transitionToPlay()
{
	this->scoreLabel->Show(false);
	this->quitButton->Show(false);
	this->playButton->Show(false);

	std::sort(this->data.scores.rbegin(), this->data.scores.rend());
	this->data.scores.back() = 0;

	this->stateMachine.pop();
	this->stateMachine.push(StateMachine::StateID::PlayState);
}
