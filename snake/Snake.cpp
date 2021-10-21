#include "Snake.hpp"

#include "Food.hpp"
#include "PlayingField.hpp"

void kp::Snake::initOfBaseTypes()
{
	m_delay = 0.2f;
	m_score = 0;
	m_direction = sf::Keyboard::Key::Unknown;
}

void kp::Snake::initHead()
{
	m_head = new sf::RectangleShape();

	if (m_head != nullptr)
	{
		m_head->setSize(sf::Vector2f(20.0f, 20.0f));
		m_head->setFillColor(sf::Color(210, 120, 0, 255));
		m_head->setOutlineColor(sf::Color(150, 50, 0, 255));
		m_head->setOutlineThickness(2.0f);
		m_head->setOrigin(sf::Vector2f(m_head->getSize().x / 2.0f, m_head->getSize().y / 2.0f));
	}
}

void kp::Snake::initBodyPart()
{
	m_bodyPart = new sf::RectangleShape();

	if (m_bodyPart != nullptr)
	{
		m_bodyPart->setSize(sf::Vector2f(20.0f, 20.0f));
		m_bodyPart->setFillColor(sf::Color(230, 130, 0, 255));
		m_bodyPart->setOutlineColor(sf::Color(170, 80, 0, 255));
		m_bodyPart->setOutlineThickness(2.0f);
		m_bodyPart->setOrigin(sf::Vector2f(m_bodyPart->getSize().x / 2.0f, m_bodyPart->getSize().y / 2.0f));
	}
}

void kp::Snake::initBodyPartsIndex()
{
	m_BodyPartsIndex.push_back(new sf::Vector2u());
}

void kp::Snake::initSupportedKeys()
{
	m_supportedKeys.emplace("Up", sf::Keyboard::Key::Up);
	m_supportedKeys.emplace("Down", sf::Keyboard::Key::Down);
	m_supportedKeys.emplace("Left", sf::Keyboard::Key::Left);
	m_supportedKeys.emplace("Right", sf::Keyboard::Key::Right);

	m_supportedKeys.emplace("W", sf::Keyboard::Key::W);
	m_supportedKeys.emplace("S", sf::Keyboard::Key::S);
	m_supportedKeys.emplace("A", sf::Keyboard::Key::A);
	m_supportedKeys.emplace("D", sf::Keyboard::Key::D);
}

void kp::Snake::chooseRandomIndex()
{
	m_tileIndex = sf::Vector2u(rand() % m_gridSize.x, rand() % m_gridSize.y);
	*m_BodyPartsIndex[0] = m_tileIndex;
	m_head->setPosition(sf::Vector2f(*m_tilePositions[m_tileIndex.x][m_tileIndex.y]));

	KP_LOG("Snake tile index: " << "x-" << m_tileIndex.x << "/" << "y-" << m_tileIndex.y);
}

void kp::Snake::chooseDirection()
{
	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Up"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["W"]))
	{
		m_direction = m_supportedKeys["Up"];
	}
	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Down"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["S"]))
	{
		m_direction = m_supportedKeys["Down"];
	}
	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Left"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["A"]))
	{
		m_direction = m_supportedKeys["Left"];
	}
	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Right"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["D"]))
	{
		m_direction = m_supportedKeys["Right"];
	}
}

void kp::Snake::moveHead()
{
	if (m_delay <= 0.0f)
	{
		if (m_direction == m_supportedKeys["Up"])
		{
			--m_tileIndex.y;
		}
		if (m_direction == m_supportedKeys["Down"])
		{
			++m_tileIndex.y;
		}
		if (m_direction == m_supportedKeys["Left"])
		{
			--m_tileIndex.x;
		}
		if (m_direction == m_supportedKeys["Right"])
		{
			++m_tileIndex.x;
		}

		*m_BodyPartsIndex[0] = m_tileIndex;
	}
}

void kp::Snake::moveBodyParts()
{
	if (m_delay <= 0.0f)
	{
		sf::Vector2u prev = *m_BodyPartsIndex[0];
		sf::Vector2u prev2;

		for (size_t index = 1; index < m_BodyPartsIndex.size(); ++index)
		{
			prev2 = *m_BodyPartsIndex[index];
			*m_BodyPartsIndex[index] = prev;
			prev = prev2;
		}
	}
}

void kp::Snake::addBodyPartIndex()
{
	sf::Vector2u* newBodyPartIndex = new sf::Vector2u();

	if (newBodyPartIndex != nullptr)
	{
		if (m_direction == m_supportedKeys["Up"])
		{
			*newBodyPartIndex = m_BodyPartsIndex.size() > 1 ?
				sf::Vector2u(m_tileIndex.x, m_tileIndex.y + 1) :
				sf::Vector2u(m_BodyPartsIndex.back()->x, m_BodyPartsIndex.back()->y + 1);
		}
		if (m_direction == m_supportedKeys["Down"])
		{
			*newBodyPartIndex = m_BodyPartsIndex.size() > 1 ?
				sf::Vector2u(m_tileIndex.x, m_tileIndex.y - 1) :
				sf::Vector2u(m_BodyPartsIndex.back()->x, m_BodyPartsIndex.back()->y - 1);
		}
		if (m_direction == m_supportedKeys["Left"])
		{
			*newBodyPartIndex = m_BodyPartsIndex.size() > 1 ?
				sf::Vector2u(m_tileIndex.x + 1, m_tileIndex.y) :
				sf::Vector2u(m_BodyPartsIndex.back()->x + 1, m_BodyPartsIndex.back()->y);
		}
		if (m_direction == m_supportedKeys["Right"])
		{
			*newBodyPartIndex = m_BodyPartsIndex.size() > 1 ?
				sf::Vector2u(m_tileIndex.x - 1, m_tileIndex.y) :
				sf::Vector2u(m_BodyPartsIndex.back()->x - 1, m_BodyPartsIndex.back()->y);
		}

		m_BodyPartsIndex.push_back(newBodyPartIndex);
	}
}

kp::Snake::Snake(sf::RenderWindow* window)
	: m_window(window)
{
	initOfBaseTypes();
	initHead();
	initBodyPart();
	initBodyPartsIndex();
	initSupportedKeys();
}

void kp::Snake::setTileSize(sf::Vector2f tileSize)
{
	m_tileSize = tileSize;

	m_head->setSize(sf::Vector2f(m_tileSize.x - 4.0f, m_tileSize.y - 4.0f));
	m_head->setOrigin(sf::Vector2f(m_head->getSize().x / 2.0f, m_head->getSize().y / 2.0f));

	m_bodyPart->setSize(sf::Vector2f(m_tileSize.x - 4.0f, m_tileSize.y - 4.0f));
	m_bodyPart->setOrigin(sf::Vector2f(m_bodyPart->getSize().x / 2.0f, m_bodyPart->getSize().y / 2.0f));
}

void kp::Snake::setTileIndex(sf::Vector2u tileIndex)
{
	m_tileIndex = tileIndex;
}

void kp::Snake::setGridSize(sf::Vector2u gridSize)
{
	m_gridSize = gridSize;
}

void kp::Snake::setTilePositions(kp::tilePositions_t tilePositions)
{
	m_tilePositions = tilePositions;
}

sf::Vector2f kp::Snake::getTileSize() const
{
	return m_tileSize;
}

sf::Vector2u kp::Snake::getTileIndex() const
{
	return m_tileIndex;
}

sf::Vector2u kp::Snake::getGridSize() const
{
	return m_gridSize;
}

kp::tilePositions_t kp::Snake::getTilePositions() const
{
	return m_tilePositions;
}

bool kp::Snake::isEating(sf::Vector2u foodIndex)
{
	if (m_tileIndex == foodIndex)
	{
		++m_score;

		addBodyPartIndex();

		KP_LOG("Snake: eat" << " | " << "Score: " << m_score);

		return true;
	}

	return false;
}

bool kp::Snake::isDead()
{
	if ((m_tileIndex.x < 0 || m_tileIndex.x > m_gridSize.x
		|| m_tileIndex.y < 0 || m_tileIndex.y > m_gridSize.y)
		|| isCollideWithMyself())
	{
		KP_LOG("Snake: dead" << " | " << "Tile index: " << m_tileIndex.x << "/" << m_tileIndex.y);

		return true;
	}

	return false;
}

bool kp::Snake::isCollideWithMyself()
{
	for (size_t index = 1; index < m_BodyPartsIndex.size(); ++index)
	{
		if (m_tileIndex == *m_BodyPartsIndex[index])
		{
			KP_LOG("Collide on index: "
				<< std::to_string(m_tileIndex.x) + "/" + std::to_string(m_tileIndex.y) << " | "
				<< std::to_string(m_BodyPartsIndex[index]->x) + "/" + std::to_string(m_BodyPartsIndex[index]->y));

			return true;
		}
	}

	return false;
}

int16_t kp::Snake::getScore() const
{
	return m_score;
}

void kp::Snake::restart()
{
	m_score = 0;
	m_direction = sf::Keyboard::Key::Unknown;
	
	for (size_t index = 1; index < m_BodyPartsIndex.size(); ++index)
	{
		delete m_BodyPartsIndex[index];
	}

	m_BodyPartsIndex.resize(1);

	chooseRandomIndex();
}

void kp::Snake::render()
{
	for (size_t index = 1; index < m_BodyPartsIndex.size(); ++index)
	{
		if (m_BodyPartsIndex[index]->x >= 0 && m_BodyPartsIndex[index]->y >= 0 &&
			m_BodyPartsIndex[index]->x < m_gridSize.x && m_BodyPartsIndex[index]->y < m_gridSize.y)
		{
			m_bodyPart->setPosition(*m_tilePositions[m_BodyPartsIndex[index]->x][m_BodyPartsIndex[index]->y]);
			m_window->draw(*m_bodyPart);
		}
	}

	if (m_tileIndex.x >= 0 && m_tileIndex.y >= 0 && m_tileIndex.x < m_gridSize.x && m_tileIndex.y < m_gridSize.y)
	{
		m_head->setPosition(sf::Vector2f(*m_tilePositions[m_tileIndex.x][m_tileIndex.y]));
		m_window->draw(*m_head);
	}
}

void kp::Snake::update(float dT)
{
	m_dT = dT;

	static const float m_delayBuffer = m_delay;
	m_delay -= m_dT;

	chooseDirection();
	moveBodyParts();
	moveHead();

	if (m_delay <= 0.0f)
	{
		m_delay = m_delayBuffer;
	}
}

kp::Snake::~Snake()
{
	delete m_head;
	delete m_bodyPart;

	for (size_t index = 0; index < m_BodyPartsIndex.size(); ++index)
	{
		delete m_BodyPartsIndex[index];
	}
}