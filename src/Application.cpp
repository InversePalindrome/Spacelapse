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
#include "HighScoreState.hpp"
#include "SpaceshipSelectionState.hpp"

#include <SFML/Window/Event.hpp>


Application::Application() :
	window(sf::VideoMode(2560, 1440), "Spacelapse", sf::Style::Titlebar | sf::Style::Close),
	stateMachine(State::Data(window, gui, hud, textures, images, player))
{
	stateMachine.registerState<SplashState>(StateMachine::StateID::SplashState);
	stateMachine.registerState<MenuState>(StateMachine::StateID::MenuState);
	stateMachine.registerState<PlayState>(StateMachine::StateID::PlayState);
	stateMachine.registerState<SpaceshipSelectionState>(StateMachine::StateID::SpaceshipSelectionState);
	stateMachine.registerState<HighScoreState>(StateMachine::StateID::HighScoreState);
	stateMachine.registerState<PauseState>(StateMachine::StateID::PauseState);

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