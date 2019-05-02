/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SoundNode.cpp
InversePalindrome.com
*/


#include "SoundNode.hpp"


SoundNode::SoundNode(SoundPlayer& soundPlayer) :
    soundPlayer(soundPlayer)
{
}

void SoundNode::playSound(Sounds sound, sf::Vector2f position)
{
    this->soundPlayer.play(sound, position);
}

std::size_t SoundNode::getCategory() const
{
    return Command::Category::Sound;
}