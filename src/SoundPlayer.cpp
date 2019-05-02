/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SoundPlayer.cpp
InversePalindrome.com
*/


#include "SoundPlayer.hpp"

#include <SFML/Audio/Listener.hpp>

#include <cmath>


const float SoundPlayer::zPosition = 300.f;
const float SoundPlayer::attenuation = 8.f;
const float SoundPlayer::minDistance2d = 200.f;
const float SoundPlayer::minDistance3d = std::sqrt(std::pow(minDistance2d, 2) + std::pow(zPosition, 2));

SoundPlayer::SoundPlayer() :
    soundBuffers(),
    sounds(),
    volume(100.f)
{
    soundBuffers.load(Sounds::LaserShot, "Resources/Sounds/LaserShot.wav");
}

void SoundPlayer::play(Sounds sound)
{
    this->play(sound, this->getListenerPosition());
}

void SoundPlayer::play(Sounds sound, sf::Vector2f position)
{
    this->sounds.push_back(sf::Sound(this->soundBuffers.get(sound)));

    this->sounds.back().setVolume(this->volume);
    this->sounds.back().setPosition(position.x, -position.y, 0.f);
    this->sounds.back().setAttenuation(this->attenuation);
    this->sounds.back().setMinDistance(this->minDistance3d);

    this->sounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
    this->sounds.remove_if([](const auto & sound) { return sound.getStatus() == sf::Sound::Stopped; });
}

void SoundPlayer::setVolume(float volume)
{
    this->volume = volume;
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, this->zPosition);
}

float SoundPlayer::getVolume() const
{
    return this->volume;
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    return sf::Vector2f(sf::Listener::getPosition().x, -sf::Listener::getPosition().y);
}