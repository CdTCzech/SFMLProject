#pragma once

#include <array>

#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Entities/Player.hpp"
#include "Entities/SceneNode.hpp"
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
	explicit	World(sf::RenderWindow& window);
	void		update(sf::Time deltaTime);
	void		draw();

private:
	void		loadTextures();
	void		buildScene();

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

	sf::FloatRect						m_worldBounds;
	sf::Vector2f						m_spawnPosition;
	Player*								m_player;
};
