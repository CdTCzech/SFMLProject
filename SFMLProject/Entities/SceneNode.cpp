#include "SceneNode.hpp"

#include <algorithm>
#include <cassert>

#include "../Input/Category.hpp"
#include "../Input/Command.hpp"


SceneNode::SceneNode()
	: m_children()
	, m_parent(nullptr)
{
}

void SceneNode::attachChild(SceneNodePtr child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

SceneNode::SceneNodePtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(), [&](SceneNodePtr& p) { return p.get() == &node; });
	assert(found != m_children.end());

	SceneNodePtr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::update(sf::Time deltaTime)
{
	updateCurrent(deltaTime);
	updateChildren(deltaTime);
}

void SceneNode::updateCurrent(sf::Time /*deltaTime*/)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time deltaTime)
{
	for (SceneNodePtr& child :m_children)
	{
		child->update(deltaTime);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& child : m_children)
	{
		child->draw(target, states);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time deltaTime)
{
	// Command current node, if category matches
	if (command.category & getCategory())
	{
		command.action(*this, deltaTime);
	}

	// Command children
	for (SceneNodePtr& child : m_children)
	{
		child->onCommand(command, deltaTime);
	}
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}
