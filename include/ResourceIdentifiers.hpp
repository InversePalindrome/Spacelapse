/*
Copyright (c) 2017 InversePalindrome
Spacelapse - Application.hpp
InversePalindrome.com
*/


#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


enum class Textures
{
	SplashScreen, MenuBackground, SpaceshipsBackground, HighScoreBackground, PlayBackground, PauseBackground, BlueSpaceship, RegularAsteroid, LavaAsteroid
};
enum class Images
{ 
	PlayButton, SpaceshipsButton, HighScoresButton, MenuButton, QuitButton, SettingsButton 
};
enum class Fonts {};
enum class Sounds {};

template<typename Resource, typename Identifier>
class ResourceManager;

using TextureManager = ResourceManager<sf::Texture, Textures>;
using ImageManager = ResourceManager<sf::Image, Images>;
using FontManager = ResourceManager<sf::Font, Fonts>;
using SoundManager = ResourceManager<sf::SoundBuffer, Sounds>;