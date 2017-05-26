/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"
#include "PauseState.hpp"
#include "SplashState.hpp"
#include "GameOverState.hpp"
#include "HighScoreState.hpp"
#include "SpaceshipSelectionState.hpp"

#include <SFML/Window/Event.hpp>

#include <fstream>
#include <iostream>


Application::Application() :
	window(sf::VideoMode(2560, 1440), "Spacelapse", sf::Style::Titlebar | sf::Style::Close),
	spaceshipType(Spaceship::Type::BlueSpaceship),
	scores(),
	stateMachine(State::Data(window, gui, hud, textures, images, soundPlayer, player, spaceshipType, scores))
{
	loadData();
	loadTextures();

	stateMachine.registerState<SplashState>(StateMachine::StateID::SplashState);
	stateMachine.registerState<MenuState>(StateMachine::StateID::MenuState);
	stateMachine.registerState<PlayState>(StateMachine::StateID::PlayState);
	stateMachine.registerState<SpaceshipSelectionState>(StateMachine::StateID::SpaceshipSelectionState);
	stateMachine.registerState<HighScoreState>(StateMachine::StateID::HighScoreState);
	stateMachine.registerState<PauseState>(StateMachine::StateID::PauseState);
	stateMachine.registerState<GameOverState>(StateMachine::StateID::GameOverState);
	
	stateMachine.push(StateMachine::StateID::SplashState);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (this->window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		elapsedTime += deltaTime;

		while (elapsedTime > timePerFrame)
		{
			elapsedTime -= timePerFrame;

			this->processInput();
			this->update(timePerFrame);

			if (!this->stateMachine.hasStates())
			{
				this->saveData();
				this->window.close();
			}
		}

		this->render();
	}
}

void Application::processInput()
{
	sf::Event event;

	while (this->window.pollEvent(event))
	{
		this->stateMachine.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			this->saveData();
			this->window.close();
			break;
		}
	}
}

void Application::update(sf::Time deltaTime)
{
	this->stateMachine.update(deltaTime);
}

void Application::render()
{
	this->window.clear(sf::Color::White);

	this->stateMachine.draw();

	this->window.display();
}

void Application::saveData()
{
	std::ofstream outSaveFile("Resources/TextFiles/SaveFile.txt");

	for (std::size_t i = 0; i < scores.size() - 1; i++)
	{
		outSaveFile << scores.at(i) << std::endl;
	}

	outSaveFile << static_cast<std::size_t>(this->spaceshipType) << std::endl;

	outSaveFile.close();
}

void Application::loadData()
{
	std::ifstream inSaveFile("Resources/TextFiles/SaveFile.txt");
	std::size_t data;

	std::size_t i = 0;

	while (inSaveFile >> data)
	{
		if (i < this->scores.size() - 1)
		{
			this->scores.at(i++) = data;
		}
		else
		{
			this->spaceshipType = static_cast<Spaceship::Type>(data);
		}
	}


	inSaveFile.close();
}

void Application::loadTextures()
{
	this->textures.load(Textures::SplashScreen, "Resources/Images/InversePalindromeLogo.png");
	this->textures.load(Textures::MenuBackground, "Resources/Images/MenuBackground.jpg");
	this->textures.load(Textures::HighScoreBackground, "Resources/Images/HighScoreBackground.png");
	this->textures.load(Textures::SpaceshipsBackground, "Resources/Images/SpaceshipsBackground.png");
	this->textures.load(Textures::BlueSpaceship, "Resources/Images/BlueSpaceship.png");
	this->textures.load(Textures::RedSpaceship, "Resources/Images/RedSpaceship.png");
	this->textures.load(Textures::GreenSpaceship, "Resources/Images/GreenSpaceship.png");
	this->textures.load(Textures::YellowSpaceship, "Resources/Images/YellowSpaceship.png");
	this->textures.load(Textures::FireProjectile, "Resources/Images/FireProjectile.png");
	this->textures.load(Textures::RegularAsteroid, "Resources/Images/RegularAsteroid.png");
	this->textures.load(Textures::LavaAsteroid, "Resources/Images/LavaAsteroid.png");
	this->textures.load(Textures::BluePointTarget, "Resources/Images/BluePointTarget.png");
	this->textures.load(Textures::GreenPointTarget, "Resources/Images/GreenPointTarget.png");
	this->textures.load(Textures::YellowPointTarget, "Resources/Images/YellowPointTarget.png");
	this->textures.load(Textures::PlayBackground, "Resources/Images/SpaceBackground.jpg");
	this->textures.load(Textures::PauseBackground, "Resources/Images/SpaceBackground2.jpg");
	this->textures.load(Textures::GameOverBackground, "Resources/Images/SpaceBackground3.jpg");

	this->images.load(Images::PlayButton, "Resources/Images/PlayButton.png");
	this->images.load(Images::QuitButton, "Resources/Images/QuitButton.png");
	this->images.load(Images::SpaceshipsButton, "Resources/Images/SpaceshipsButton.png");
	this->images.load(Images::HighScoresButton, "Resources/Images/HighScoresButton.png");
	this->images.load(Images::MenuButton, "Resources/Images/MenuButton.png");
	this->images.load(Images::SelectButton, "Resources/Images/SelectButton.png");
	this->images.load(Images::OnVolumeButton, "Resources/Images/OnVolumeButton.png");
	this->images.load(Images::OffVolumeButton, "Resources/Images/OffVolumeButton.png");
}