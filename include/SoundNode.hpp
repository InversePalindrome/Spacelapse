/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SoundNode.hpp
InversePalindrome.com
*/


#pragma once

#include "SceneNode.hpp"
#include "SoundPlayer.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"


class SoundNode : public SceneNode
{
public:
    SoundNode(SoundPlayer& soundPlayer);

    void playSound(Sounds sound, sf::Vector2f position);

    virtual std::size_t getCategory() const override;

private:
    SoundPlayer& soundPlayer;
};
