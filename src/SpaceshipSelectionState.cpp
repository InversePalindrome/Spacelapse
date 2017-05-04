/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SpaceshipSelectionState.cpp
InversePalindrome.com
*/


#include "SpaceshipSelectionState.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"

#include <SFGUI/Image.hpp>


SpaceshipSelectionState::SpaceshipSelectionState(StateMachine& stateMachine, Data data) :
	State(stateMachine, data),
	background(),
	menuButton()
{
	data.textures.load(Textures::SpaceshipsBackground, "Resources/Images/SpaceshipsBackground.png");
	data.images.load(Images::MenuButton, "Resources/Images/MenuButton.png");

	background.setTexture(data.textures.get(Textures::SpaceshipsBackground));

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

void SpaceshipSelectionState::handleEvent(const sf::Event& event)
{
	this->data.hud.HandleEvent(event);
}

void SpaceshipSelectionState::update(sf::Time deltaTime)
{
	this->data.hud.Update(deltaTime.asMicroseconds());
}

void SpaceshipSelectionState::draw()
{
	this->data.window.draw(this->background);
	this->data.gui.Display(this->data.window);
}