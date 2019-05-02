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
    SplashScreen, MenuBackground, SpaceshipsBackground, HighScoreBackground, PlayBackground,
    PauseBackground, GameOverBackground, BlueSpaceship, RedSpaceship, GreenSpaceship, YellowSpaceship,
    RegularAsteroid, LavaAsteroid, FireProjectile, BluePointTarget, GreenPointTarget, YellowPointTarget
};

enum class Images
{
    PlayButton, SpaceshipsButton, HighScoresButton, MenuButton, QuitButton, SettingsButton, SelectButton,
    OnVolumeButton, OffVolumeButton
};

enum class Fonts
{
    Bebas
};

enum class Sounds
{
    LaserShot
};

template<typename Resource, typename Identifier>
class ResourceManager;

using TextureManager = ResourceManager<sf::Texture, Textures>;
using ImageManager = ResourceManager<sf::Image, Images>;
using FontManager = ResourceManager<sf::Font, Fonts>;
using SoundManager = ResourceManager<sf::SoundBuffer, Sounds>;