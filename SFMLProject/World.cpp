#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entities/SpriteNode.hpp"


World::World(sf::RenderWindow& window)
	: m_window(window)
	, m_worldView(window.getDefaultView())
	, m_textures()
	, m_sceneGraph()
	, m_sceneLayers()
	, m_worldBounds(0.f, 0.f, 2000.f, 2000.f)
	, m_spawnPosition(m_worldView.getSize().x / 2.f, m_worldView.getSize().y / 2.f)
	, m_player(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	m_worldView.setCenter(m_spawnPosition);
}

void World::update(sf::Time deltaTime)
{
	// Move the player
	sf::Vector2f position = m_player->getPosition();
	sf::Vector2f velocity = m_player->getVelocity();

	// If player touches borders, flip its X velocity
	if (position.x <= m_worldBounds.left + 150.f
		|| position.x >= m_worldBounds.left + m_worldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		m_player->setVelocity(velocity);
	}

	// Scroll the world
	m_worldView.move(velocity.x * deltaTime.asSeconds(), 0.f);

	// Apply movements
	m_sceneGraph.update(deltaTime);
}

void World::draw()
{
	m_window.setView(m_worldView);
	m_window.draw(m_sceneGraph);
}

void World::loadTextures()
{
	m_textures.load(Textures::ID::Background, "Resources/Textures/Desert.png");
	m_textures.load(Textures::ID::BibleThumpReverse, "Resources/Textures/BibleThumpReverse.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::SceneNodePtr layer(new SceneNode());
		m_sceneLayers[i] = layer.get();

		m_sceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = m_textures.get(Textures::ID::Background);
	sf::IntRect textureRect(m_worldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(m_worldBounds.left, m_worldBounds.top);
	m_sceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player
	std::unique_ptr<Player> leader(new Player(Player::Type::BibleThumpReverse, m_textures));
	m_player = leader.get();
	m_player->setPosition(m_spawnPosition);
	m_player->setVelocity(100.f, 0.f);
	m_sceneLayers[Ground]->attachChild(std::move(leader));
}
