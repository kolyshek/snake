#include "Food.hpp"

#include "PlayingField.hpp"

void kp::Food::initFood()
{
	m_foodPart = new sf::RectangleShape;

	if (m_foodPart != nullptr)
	{
		m_foodPart->setSize(sf::Vector2f(20.0f, 20.0f));
		m_foodPart->setFillColor(sf::Color(50, 200, 50, 255));
		m_foodPart->setOrigin(sf::Vector2f(m_foodPart->getSize().x / 2.0f, m_foodPart->getSize().y / 2.0f));
	}
}

void kp::Food::pulsationSize()
{
	static const sf::Vector2f sizeBuffer = m_foodPart->getSize();
	static const float sizeStep = sizeBuffer.x / 0.8f;
	static const float positionStep = sizeBuffer.x / 0.8f / 2.0f;
	static bool decrease = true;

	if (decrease)
	{
		if (m_foodPart->getSize().x < sizeBuffer.x / 2.0f)
		{
			decrease = false;

			return;
		}

		m_foodPart->setSize(sf::Vector2f(m_foodPart->getSize().x - sizeStep * m_dT, m_foodPart->getSize().y - sizeStep * m_dT));
		m_foodPart->setPosition(sf::Vector2f(m_foodPart->getPosition().x + positionStep * m_dT, m_foodPart->getPosition().y + positionStep * m_dT));
	}
	else
	{
		if (m_foodPart->getSize().x > sizeBuffer.x)
		{
			decrease = true;

			return;
		}

		m_foodPart->setSize(sf::Vector2f(m_foodPart->getSize().x + sizeStep * m_dT, m_foodPart->getSize().y + sizeStep * m_dT));
		m_foodPart->setPosition(sf::Vector2f(m_foodPart->getPosition().x - positionStep * m_dT, m_foodPart->getPosition().y - positionStep * m_dT));
	}
}

kp::Food::Food(sf::RenderWindow* window)
	: m_window(window)
{
	initFood();
}

void kp::Food::setTileSize(sf::Vector2f tileSize)
{
	m_tileSize = tileSize;

	m_foodPart->setSize(sf::Vector2f(m_tileSize.x - 4.0f, m_tileSize.y - 4.0f));
	m_foodPart->setOrigin(sf::Vector2f(m_foodPart->getSize().x / 2.0f, m_foodPart->getSize().y / 2.0f));
}

void kp::Food::setTileIndex(sf::Vector2u tileIndex)
{
	m_tileIndex = tileIndex;
}

void kp::Food::setGridSize(sf::Vector2u gridSize)
{
	m_gridSize = gridSize;
}

void kp::Food::setTilePositions(kp::tilePositions_t tilePositions)
{
	m_tilePositions = tilePositions;
}

sf::Vector2u kp::Food::getGridSize() const
{
	return m_gridSize;
}

kp::tilePositions_t kp::Food::getTilePositions() const
{
	return m_tilePositions;
}

void kp::Food::chooseRandomIndex()
{
	m_tileIndex = sf::Vector2u(rand() % m_gridSize.x, rand() % m_gridSize.y);
	m_foodPart->setPosition(sf::Vector2f(*m_tilePositions[m_tileIndex.x][m_tileIndex.y]));

	KP_LOG("Food tile index: " << "x-" << m_tileIndex.x << "/" << "y-" << m_tileIndex.y);
}

sf::Vector2f kp::Food::getTileSize() const
{
	return m_tileSize;
}

sf::Vector2u kp::Food::getTileIndex() const
{
	return m_tileIndex;
}

void kp::Food::render()
{
	m_window->draw(*m_foodPart);
}

void kp::Food::update(float dT)
{
	m_dT = dT;

	pulsationSize();
}

kp::Food::~Food()
{
	delete m_foodPart;
}