/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SoundPlayer.hpp
InversePalindrome.com
*/


#pragma once

#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <list>


class SoundPlayer
{
public:
	SoundPlayer();

	void play(Sounds sound);
	void play(Sounds sound, sf::Vector2f position);

	void removeStoppedSounds();

	void setVolume(float volume);

	void setListenerPosition(sf::Vector2f position);

	float getVolume() const;

	sf::Vector2f getListenerPosition() const;

private:
	SoundManager soundBuffers;
	std::list<sf::Sound> sounds;

	float volume;

	static const float zPosition;
	static const float attenuation;
	static const float minDistance2d;
	static const float minDistance3d;
};