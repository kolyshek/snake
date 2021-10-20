#include "PlayingField.hpp"

void kp::PlayingField::initGridSize()
{
	m_gridSize = sf::Vector2u(24, 24);
}

void kp::PlayingField::initTile()
{
	m_tile = new sf::RectangleShape;

	if (m_tile != nullptr)
	{
		m_tile->setSize(sf::Vector2f(static_cast<float>(m_window->getSize().x / m_gridSize.x),
			static_cast<float>(m_window->getSize().x / m_gridSize.y)));
		m_tile->setFillColor(sf::Color(32, 32, 32, 255));
		m_tile->setOutlineThickness(2);
		m_tile->setOutlineColor(sf::Color(46, 46, 46, 255));
		m_tile->setOrigin(sf::Vector2f(m_tile->getSize().x / 2.0f, m_tile->getSize().y / 2.0f));
	}
}

void kp::PlayingField::initTilePositions()
{
	sf::Vector2f startPosition(static_cast<float>(m_window->getSize().x / m_gridSize.x),
		static_cast<float>(m_window->getSize().x / m_gridSize.y));

	for (size_t outerIndex = 0; outerIndex < m_gridSize.x; ++outerIndex)
	{
		m_tilePositions.push_back(std::vector<sf::Vector2f*>());

		for (size_t innerIndex = 0; innerIndex < m_gridSize.y; ++innerIndex)
		{
			m_tilePositions[outerIndex].push_back(new sf::Vector2f(startPosition.x * outerIndex + m_tile->getSize().x / 2.0f + m_tile->getOutlineThickness(),
				startPosition.y * innerIndex + m_tile->getSize().y / 2.0f + 80.0f));
		}
	}
}

kp::PlayingField::PlayingField(sf::RenderWindow* window)
	: m_window(window)
{
	initGridSize();
	initTile();
	initTilePositions();
}

void kp::PlayingField::setGridSize(sf::Vector2u gridSize)
{
	m_gridSize = gridSize;
}

void kp::PlayingField::setTilePositions(kp::tilePositions_t tilePositions)
{
	m_tilePositions = tilePositions;
}

sf::Vector2u kp::PlayingField::getGridSize() const
{
	return m_gridSize;
}

kp::tilePositions_t kp::PlayingField::getTilePositions() const
{
	return m_tilePositions;
}

sf::Vector2f kp::PlayingField::getTileSize() const
{
	return m_tile->getSize();
}

void kp::PlayingField::update(float dT)
{
	dT;
}

void kp::PlayingField::render()
{
	for (size_t outerIndex = 0; outerIndex < m_tilePositions.size(); ++outerIndex)
	{
		for (size_t innerIndex = 0; innerIndex < m_tilePositions[outerIndex].size(); ++innerIndex)
		{
			m_tile->setPosition(*m_tilePositions[outerIndex][innerIndex]);
			m_window->draw(*m_tile);
		}
	}
}

kp::PlayingField::~PlayingField()
{
	delete m_tile;

	for (size_t outerIndex = 0; outerIndex < m_tilePositions.size(); ++outerIndex)
	{
		for (size_t innerIndex = 0; innerIndex < m_tilePositions[outerIndex].size(); ++innerIndex)
		{
			delete m_tilePositions[outerIndex][innerIndex];
		}
	}
}