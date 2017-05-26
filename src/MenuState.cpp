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
	highScoresButton(),
	volumeButton()
{
	background.setTexture(data.textures.get(Textures::MenuBackground));

	background.setScale(static_cast<float>(data.window.getSize().x) / background.getLocalBounds().width, 
		static_cast<float>(data.window.getSize().y) / background.getLocalBounds().height);

	playButton = sfg::Button::Create();
	playButton->SetImage(sfg::Image::Create(data.images.get(Images::PlayButton)));
	playButton->SetPosition(sf::Vector2f(1030.f, 800.f));
	playButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToPlay(); });

	spaceshipsButton = sfg::Button::Create();
	spaceshipsButton->SetImage(sfg::Image::Create(data.images.get(Images::SpaceshipsButton)));
	spaceshipsButton->SetPosition(sf::Vector2f(1030.f, 1000.f));
    spaceshipsButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToSpaceshipSelection(); });

    highScoresButton = sfg::Button::Create();
	highScoresButton->SetImage(sfg::Image::Create(data.images.get(Images::HighScoresButton)));
	highScoresButton->SetPosition(sf::Vector2f(1030.f, 1200.f));
	highScoresButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { transitionToHighScores(); });

	volumeButton = sfg::Button::Create();
	data.soundPlayer.getVolume() == 100.f ?
	volumeButton->SetImage(sfg::Image::Create(data.images.get(Images::OnVolumeButton)))
	: volumeButton->SetImage(sfg::Image::Create(data.images.get(Images::OffVolumeButton)));
	volumeButton->SetPosition(sf::Vector2f(25.f, 25.f));
	volumeButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this] { adjustVolume(); });

	data.hud.Add(playButton);
	data.hud.Add(spaceshipsButton);
	data.hud.Add(highScoresButton);
	data.hud.Add(volumeButton);
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
	this->volumeButton->Show(true);

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
	this->volumeButton->Show(false);

	this->stateMachine.pop();
	this->stateMachine.push(StateMachine::StateID::PlayState);
}

void MenuState::transitionToSpaceshipSelection()
{
	this->playButton->Show(false);
	this->spaceshipsButton->Show(false);
	this->highScoresButton->Show(false);
	this->volumeButton->Show(false);

	this->stateMachine.push(StateMachine::StateID::SpaceshipSelectionState);
}

void MenuState::transitionToHighScores()
{
	this->playButton->Show(false);
	this->spaceshipsButton->Show(false);
    this->highScoresButton->Show(false);
	this->volumeButton->Show(false);

	this->stateMachine.push(StateMachine::StateID::HighScoreState);
}

void MenuState::adjustVolume()
{
	if (this->data.soundPlayer.getVolume() == 0.f)
	{
		this->data.soundPlayer.setVolume(100.f);
		this->volumeButton->SetImage(sfg::Image::Create(data.images.get(Images::OnVolumeButton)));
	}
	else
	{
		this->data.soundPlayer.setVolume(0.f);
		this->volumeButton->SetImage(sfg::Image::Create(data.images.get(Images::OffVolumeButton)));
	}
}