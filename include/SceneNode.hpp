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

#include <set>
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

	void checkSceneCollision(SceneNode& sceneGraph, std::set<std::pair<SceneNode*, SceneNode*>>& collisions);
	void checkNodeCollision(SceneNode& node, std::set<std::pair<SceneNode*, SceneNode*>>& collisions);

	void removeMarkedNodes();

	virtual bool isMarkedForRemoval() const;
	
	virtual std::size_t getCategory() const;

	virtual sf::FloatRect getPerimeter() const;

private:
	std::vector<std::unique_ptr<SceneNode>> children;
	SceneNode* parent;

	virtual void updateCurrentNode(sf::Time deltaTime, CommandQueue& commands);
	void updateChildrenNodes(sf::Time deltaTime, CommandQueue& commands);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildrenNodes(sf::RenderTarget& target, sf::RenderStates states) const;
};

bool collision(const SceneNode& node1, const SceneNode& node2);