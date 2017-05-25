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
	menuButton(),
	spaceshipSelections()
{
	background.setTexture(data.textures.get(Textures::SpaceshipsBackground));
	background.setOrigin(sf::Vector2f(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f));
	background.setPosition(data.window.getSize().x / 2.f, data.window.getSize().y / 2.f);

	auto menuImage = sfg::Image::Create(data.images.get(Images::MenuButton));

	menuButton = sfg::Button::Create();
	menuButton->SetImage(menuImage);
	menuButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&]
	{ 
		menuButton->Show(false);

		for (const auto& selection : spaceshipSelections)
		{
			selection.second.spaceshipButton->Show(false);
		}

		stateMachine.pop(); 
	});

	spaceshipSelections.insert(std::make_pair(Spaceship::Type::BlueSpaceship, Selection(data, Textures::BlueSpaceship, sf::Vector2f(1000.f, 500.f))));
	spaceshipSelections.insert(std::make_pair(Spaceship::Type::RedSpaceship, Selection(data, Textures::RedSpaceship, sf::Vector2f(1600.f, 500.f))));
	spaceshipSelections.insert(std::make_pair(Spaceship::Type::GreenSpaceship, Selection(data, Textures::GreenSpaceship, sf::Vector2f(1000.f, 1000.f))));
	spaceshipSelections.insert(std::make_pair(Spaceship::Type::YellowSpaceship, Selection(data, Textures::YellowSpaceship, sf::Vector2f(1600.f, 1000.f))));

	spaceshipSelections.at(Spaceship::Type::BlueSpaceship).spaceshipButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this]
	{
		selectSpaceship(Spaceship::Type::BlueSpaceship);
	});

	spaceshipSelections.at(Spaceship::Type::RedSpaceship).spaceshipButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this]
	{
		selectSpaceship(Spaceship::Type::RedSpaceship);
	});

	spaceshipSelections.at(Spaceship::Type::GreenSpaceship).spaceshipButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this]
	{
		selectSpaceship(Spaceship::Type::GreenSpaceship);
	});

	spaceshipSelections.at(Spaceship::Type::YellowSpaceship).spaceshipButton->GetSignal(sfg::Widget::OnLeftClick).Connect([this]
	{
		selectSpaceship(Spaceship::Type::YellowSpaceship);
	});

	data.hud.Add(menuButton);

	for (const auto& selection : spaceshipSelections)
	{
		data.hud.Add(selection.second.spaceshipButton);
	}
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

	for (const auto& selection : this->spaceshipSelections)
	{
		this->data.window.draw(selection.second.spaceshipSprite);
	}

	this->data.gui.Display(this->data.window);
}

SpaceshipSelectionState::Selection::Selection(Data data, Textures spaceshipTexture, sf::Vector2f position) :
	spaceshipSprite(data.textures.get(spaceshipTexture)),
	spaceshipButton()
{
	spaceshipSprite.setOrigin(spaceshipSprite.getLocalBounds().width / 2.f, spaceshipSprite.getLocalBounds().height / 2.f);
	spaceshipSprite.setPosition(position);

	spaceshipButton = sfg::Button::Create();
	spaceshipButton->SetImage(sfg::Image::Create(data.images.get(Images::SelectButton)));
	spaceshipButton->SetPosition(sf::Vector2f(position.x - 200.f, position.y + 150.f));
}

void SpaceshipSelectionState::selectSpaceship(Spaceship::Type spaceshipType)
{
	data.spaceshipType = spaceshipType;

	for (auto& selection : this->spaceshipSelections)
	{
		selection.second.spaceshipSprite.setRotation(0.f);
	}

	this->spaceshipSelections.at(spaceshipType).spaceshipSprite.setRotation(270.f);
}