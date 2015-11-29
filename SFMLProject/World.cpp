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
	, m_spawnPosition(m_worldBounds.width / 2.f, m_worldBounds.height / 2.f)
	, m_player(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	m_worldView.setCenter(m_spawnPosition);
}

void World::update(sf::Time deltaTime)
{
	// Reset player velocity
	m_player->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity
	while (!m_commandQueue.isEmpty())
	{
		m_sceneGraph.onCommand(m_commandQueue.pop(), deltaTime);
	}
	adaptPlayerVelocity();

	auto oldPosition = m_player->getPosition();

	// Apply movements
	m_sceneGraph.update(deltaTime);
	adaptPlayerPosition();

	// Move the world view
	m_worldView.move((m_player->getPosition() - oldPosition));
}

void World::draw() const
{
	m_window.setView(m_worldView);
	m_window.draw(m_sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return m_commandQueue;
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
	std::unique_ptr<PlayerEntity> leader(new PlayerEntity(PlayerEntity::Type::BibleThumpReverse, m_textures));
	m_player = leader.get();
	m_player->setPosition(m_spawnPosition);
	m_sceneLayers[Ground]->attachChild(std::move(leader));
}

void World::adaptPlayerPosition() const
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	const float borderDistance = 150.f;

	sf::Vector2f position = m_player->getPosition();
	position.x = std::max(position.x, 0 + borderDistance);
	position.x = std::min(position.x, m_worldBounds.width- borderDistance);
	position.y = std::max(position.y, 0 + borderDistance);
	position.y = std::min(position.y, m_worldBounds.height - borderDistance);
	m_player->setPosition(position);
}

void World::adaptPlayerVelocity() const
{
	sf::Vector2f velocity = m_player->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
	{
		m_player->setVelocity(velocity / std::sqrt(2.f));
	}
}
