/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Application.hpp
InversePalindrome.com
*/


#pragma once

#include "Player.hpp"
#include "StateMachine.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class Application
{
public:
	Application();

	void run();

private:
	void processInput();
	void update(sf::Time deltaTime);
	void render();

	sf::RenderWindow window;
	sfg::SFGUI gui;
	sfg::Desktop hud;

	StateMachine stateMachine;
	TextureManager textures;
	ImageManager images;
	Player player;
};