/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SceneNode.hpp
InversePalindrome.com
*/


#pragma once

#include "Command.hpp"
#include "CommandQueue.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <vector>
#include <memory>


class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
	void addChild(std::unique_ptr<SceneNode> child);

	std::unique_ptr<SceneNode> removeChild(const SceneNode& node);

	void update(sf::Time deltaTime, CommandQueue& commands);

	sf::Vector2f getAbsolutePosition() const;
	sf::Transform getAbsoluteTransform() const;

	void executeCommand(const Command& command, sf::Time deltaTime);

	virtual std::size_t getCategory() const;

private:
	std::vector<std::unique_ptr<SceneNode>> children;
	SceneNode* parent;

	virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands);
	void updateChildrenNodes(sf::Time deltaTime, CommandQueue& commands);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildrenNodes(sf::RenderTarget& target, sf::RenderStates states) const;
};
