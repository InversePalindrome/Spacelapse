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
	menuButton()
{
	data.textures.load(Textures::HighScoreBackground, "Resources/Images/HighScoreBackground.png");
	data.images.load(Images::MenuButton, "Resources/Images/MenuButton.png");

	background.setTexture(data.textures.get(Textures::HighScoreBackground));

	background.setScale(static_cast<float>(data.window.getSize().x) / background.getLocalBounds().width,
		static_cast<float>(data.window.getSize().y) / background.getLocalBounds().height);

	auto menuImage = sfg::Image::Create(data.images.get(Images::MenuButton));

	menuButton = sfg::Button::Create();
	menuButton->SetImage(menuImage);
	menuButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&]
	{
		menuButton->Show(false);
		stateMachine.pop(); 
	});

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
	this->data.window.draw(this->background);
	this->data.gui.Display(this->data.window);
}