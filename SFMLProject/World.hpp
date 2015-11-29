#pragma once

#include <array>

#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Entities/PlayerEntity.hpp"
#include "Entities/SceneNode.hpp"
#include "Input/CommandQueue.hpp"
#include "Utilities/ResourceHolder.hpp"
#include "Utilities/ResourceIdentifiers.hpp"


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit		World(sf::RenderWindow& window);
	void			update(sf::Time deltaTime);
	void			draw() const;

	CommandQueue&	getCommandQueue();

private:
	void		loadTextures();
	void		buildScene();

	void		adaptPlayerPosition() const;
	void		adaptPlayerVelocity() const;

private:
	enum Layer
	{
		Background,
		Ground,
		LayerCount
	};

private:
	sf::RenderWindow&					m_window;
	sf::View							m_worldView;
	TextureHolder						m_textures;

	SceneNode							m_sceneGraph;
	std::array<SceneNode*, LayerCount>	m_sceneLayers;
	CommandQueue						m_commandQueue;

	sf::FloatRect						m_worldBounds;
	sf::Vector2f						m_spawnPosition;
	PlayerEntity*						m_player;
};
