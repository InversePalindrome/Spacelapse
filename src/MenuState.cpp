/*
Copyright (c) 2017 InversePalindrome
Spacelapse - MenuState.cpp
InversePalindrome.com
*/


#include "MenuState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"

#include <SFGUI/Image.hpp>


MenuState::MenuState(StateMachine& stateMachine, Data data) :
	State(stateMachine, data),
	background(),
	playButton(),
	spaceshipsButton(),
	highScoresButton()
{
	data.textures.load(Textures::MenuBackground, "Resources/Images/MenuBackground.jpg");
	data.images.load(Images::PlayButton, "Resources/Images/PlayButton.png");
	data.images.load(Images::SpaceshipsButton, "Resources/Images/SpaceshipsButton.png");
	data.images.load(Images::HighScoresButton, "Resources/Images/HighScoresButton.png");

	background.setTexture(data.textures.get(Textures::MenuBackground));

	background.setScale(static_cast<float>(data.window.getSize().x) / background.getLocalBounds().width, 
		static_cast<float>(data.window.getSize().y) / background.getLocalBounds().height);

	auto playImage = sfg::Image::Create(data.images.get(Images::PlayButton));
	auto spaceshipsImage = sfg::Image::Create(data.images.get(Images::SpaceshipsButton));
	auto highScoresImage = sfg::Image::Create(data.images.get(Images::HighScoresButton));

	playButton = sfg::Button::Create();
	playButton->SetImage(playImage);
	playButton->SetPosition(sf::Vector2f(1030.f, 800.f));
	playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToPlay(); });

	spaceshipsButton = sfg::Button::Create();
	spaceshipsButton->SetImage(spaceshipsImage);
	spaceshipsButton->SetPosition(sf::Vector2f(1030.f, 1000.f));
    spaceshipsButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToSpaceshipSelection(); });

    highScoresButton = sfg::Button::Create();
	highScoresButton->SetImage(highScoresImage);
	highScoresButton->SetPosition(sf::Vector2f(1030.f, 1200.f));
	highScoresButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToOptions(); });

	data.hud.Add(playButton);
	data.hud.Add(spaceshipsButton);
	data.hud.Add(highScoresButton);
}

void MenuState::handleEvent(const sf::Event& event)
{
	this->data.hud.HandleEvent(event);
}

void MenuState::update(sf::Time deltaTime)
{
	this->playButton->Show(true);
	this->spaceshipsButton->Show(true);
	this->highScoresButton->Show(true);

	this->data.hud.Update(deltaTime.asMicroseconds());
}

void MenuState::draw()
{
	this->data.window.draw(background);
	this->data.gui.Display(this->data.window);
}

void MenuState::transitionToPlay()
{
	this->playButton->Show(false);
	this->spaceshipsButton->Show(false);
	this->highScoresButton->Show(false);

	stateMachine.push(StateMachine::StateID::PlayState);
}

void MenuState::transitionToSpaceshipSelection()
{
	this->playButton->Show(false);
	this->spaceshipsButton->Show(false);
	this->highScoresButton->Show(false);

	stateMachine.push(StateMachine::StateID::SpaceshipSelectionState);
}

void MenuState::transitionToOptions()
{
	this->playButton->Show(false);
	this->spaceshipsButton->Show(false);
    this->highScoresButton->Show(false);

	stateMachine.push(StateMachine::StateID::HighScoreState);
}