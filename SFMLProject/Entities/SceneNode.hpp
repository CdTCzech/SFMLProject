#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>


struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> SceneNodePtr;

public:
	SceneNode();

	void					attachChild(SceneNodePtr child);
	SceneNodePtr			detachChild(const SceneNode& node);

	void					update(sf::Time deltaTime);

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;

	void					onCommand(const Command& command, sf::Time deltaTime);
	virtual unsigned int	getCategory() const;


private:
	virtual void	updateCurrent(sf::Time deltaTime);
	void			updateChildren(sf::Time deltaTime);

	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void			drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<SceneNodePtr>	m_children;
	SceneNode*					m_parent;
};
