/*
Copyright (c) 2017 InversePalindrome
Spacelapse - OptionsState.cpp
InversePalindrome.com
*/


#include "HighScoreState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"

#include <SFGUI/Image.hpp>


HighScoreState::HighScoreState(StateMachine& stateMachine, Data data) :
	State(stateMachine, data),
	background(),
	scoreLabels(),
	menuButton()
{
	background.setTexture(data.textures.get(Textures::HighScoreBackground));
	background.setOrigin(sf::Vector2f(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f));
	background.setPosition(data.window.getSize().x / 2.f, data.window.getSize().y / 2.f);

	for (std::size_t i = 0; i < scoreLabels.size() - 1; i++)
	{
		scoreLabels.at(i) = sfg::Label::Create(std::to_string(i + 1) + "   -   " + std::to_string(data.scores.at(i)));
		scoreLabels.at(i)->SetPosition(sf::Vector2f(940.f, 350.f + (120.f * i)));
		data.hud.Add(scoreLabels.at(i));
	}

	auto menuImage = sfg::Image::Create(data.images.get(Images::MenuButton));

	menuButton = sfg::Button::Create();
	menuButton->SetImage(menuImage);
	menuButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&]
	{
		for (std::size_t i = 0; i < scoreLabels.size() - 1; i++)
		{
			scoreLabels.at(i)->Show(false);
		}

		menuButton->Show(false);
		stateMachine.pop(); 
	});

	data.hud.SetProperty("*", "FontSize", 85.f);
	data.hud.SetProperty("*", "FontName", "Resources/Fonts/Bebas.ttf");
	data.hud.Add(menuButton);
}

void HighScoreState::handleEvent(const sf::Event& event)
{
	this->data.hud.HandleEvent(event);
}

void HighScoreState::update(sf::Time deltaTime)
{
	this->data.hud.Update(deltaTime.asMicroseconds());
}

void HighScoreState::draw()
{
	this->data.window.clear(sf::Color::Black);
	this->data.window.draw(this->background);
	this->data.gui.Display(this->data.window);
}