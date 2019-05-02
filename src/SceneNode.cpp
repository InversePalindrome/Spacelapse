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
        [&](const auto & child) { return child.get() == &node; });

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
    return this->getAbsoluteTransform()* sf::Vector2f();
}

sf::Transform SceneNode::getAbsoluteTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->parent)
    {
        transform = node->getTransform() * transform;
    }

    return transform;
}

void SceneNode::executeCommand(const Command& command, sf::Time deltaTime)
{
    if (command.category & this->getCategory())
    {
        command.action(*this, deltaTime);
    }

    for (auto& child : this->children)
    {
        child->executeCommand(command, deltaTime);
    }
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<std::pair<SceneNode*, SceneNode*>>& collisions)
{
    this->checkNodeCollision(sceneGraph, collisions);

    for (auto& child : sceneGraph.children)
    {
        this->checkSceneCollision(*child, collisions);
    }
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<std::pair<SceneNode*, SceneNode*>>& collisions)
{
    if (this != &node && collision(*this, node))
    {
        collisions.insert(std::minmax(this, &node));
    }

    for (auto& child : this->children)
    {
        child->checkNodeCollision(node, collisions);
    }
}

void SceneNode::removeMarkedNodes()
{
    auto firstMarkedNode = std::remove_if(this->children.begin(), this->children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    this->children.erase(firstMarkedNode, this->children.end());

    std::for_each(this->children.begin(), this->children.end(), std::mem_fn(&SceneNode::removeMarkedNodes));
}

bool SceneNode::isMarkedForRemoval() const
{
    return false;
}

std::size_t SceneNode::getCategory() const
{
    return Command::Category::Scene;
}

sf::FloatRect SceneNode::getPerimeter() const
{
    return sf::FloatRect();
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

bool collision(const SceneNode& node1, const SceneNode& node2)
{
    const float radius1 = (node1.getPerimeter().width + node1.getPerimeter().height) / 4.f;
    const float radius2 = (node2.getPerimeter().width + node2.getPerimeter().height) / 4.f;
    const float differenceInX = node1.getPosition().x - node2.getPosition().x;
    const float differenceInY = node1.getPosition().y - node2.getPosition().y;

    return std::sqrt(std::pow(differenceInX, 2) + std::pow(differenceInY, 2)) <= radius1 + radius2;
}
