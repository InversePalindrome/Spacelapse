/*
Copyright (c) 2017 InversePalindrome
Spacelapse - SceneNode.cpp
InversePalindrome.com
*/


#include "SceneNode.hpp"

#include <algorithm>


void SceneNode::addChild(std::unique_ptr<SceneNode> child)
{
	child->parent = this;

	this->children.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::removeChild(const SceneNode& node)
{
	auto child = std::find_if(this->children.begin(), this->children.end(),
		[&](const auto& child) { return child.get() == &node; });

	auto detachedChild = std::move(*child);
	detachedChild->parent = nullptr;

	this->children.erase(child);

	return detachedChild;
}

void SceneNode::update(sf::Time deltaTime, CommandQueue& commands)
{
	this->updateCurrentNode(deltaTime, commands);
	this->updateChildrenNodes(deltaTime, commands);
}

sf::Vector2f SceneNode::getAbsolutePosition() const
{
	return this->getAbsoluteTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getAbsoluteTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
	{
		transform *= node->getTransform();
	}

	return transform;
}

void SceneNode::executeCommand(const Command& command, sf::Time deltaTime)
{
	if (static_cast<std::size_t>(command.category) & this->getCategory())
	{
		command.action(*this, deltaTime);
	}

	for (auto& child : this->children)
	{
	    child->executeCommand(command, deltaTime);
	}
}

std::size_t SceneNode::getCategory() const
{
	return static_cast<std::size_t>(Command::Category::Scene);
}

void SceneNode::updateCurrentNode(sf::Time deltaTime, CommandQueue& commands)
{

}

void SceneNode::updateChildrenNodes(sf::Time deltaTime, CommandQueue& commands)
{
	for (auto& child : this->children)
	{
		child->update(deltaTime, commands);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();

	this->drawCurrentNode(target, states);
	this->drawChildrenNodes(target, states);
}

void SceneNode::drawCurrentNode(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SceneNode::drawChildrenNodes(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& child : this->children)
	{
		child->draw(target, states);
	}
}