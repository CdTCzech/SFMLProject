#pragma once

#include <cassert>
#include <functional>

#include <SFML/System/Time.hpp>


class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int								category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function function)
{
	return [=](SceneNode& node, sf::Time deltaTime)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		function(static_cast<GameObject&>(node), deltaTime);
	};
}
