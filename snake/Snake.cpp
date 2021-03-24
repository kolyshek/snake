#include "Snake.h"

Snake::Snake(sf::RenderWindow& window, Food& food, PlayingField& playingfield)
	: m_window(window), m_food(food), m_playingfield(playingfield)
{
	m_head.setRadius(8);
	m_head.setFillColor(sf::Color(230, 138, 0, 255));
	m_head.setOutlineColor(sf::Color(150, 59, 0, 255));
	m_head.setOutlineThickness(2.0f);
	m_head.setOrigin(sf::Vector2f(m_head.getRadius(), m_head.getRadius()));
	m_head.setPosition(sf::Vector2f(float(m_window.getSize().x / 2), float(m_window.getSize().y / 2)));

	m_bodyPart.setRadius(8);
	m_bodyPart.setFillColor(sf::Color(230, 138, 0, 255));
	m_bodyPart.setOutlineColor(sf::Color(170, 81, 0, 255));
	m_bodyPart.setOutlineThickness(2.0f);
	m_bodyPart.setOrigin(sf::Vector2f(m_bodyPart.getRadius(), m_bodyPart.getRadius()));

	m_changedBodyPart = 1;

	if (m_font.loadFromFile("fonts/PixellettersFull.ttf"))
	{
		m_score.setFont(m_font);
		m_score.setFillColor(sf::Color(255, 255, 255, 255));
		m_score.setPosition(sf::Vector2f(20.0f, 0.0f));
	}
	else
	{
		std::cout << "File \"fonts/PixellettersFull.ttf\" is not found!" << "\n";
	}

	m_speed = 100;

	m_supportedKeys.emplace("Up", sf::Keyboard::Up);
	m_supportedKeys.emplace("Down", sf::Keyboard::Down);
	m_supportedKeys.emplace("Left", sf::Keyboard::Left);
	m_supportedKeys.emplace("Right", sf::Keyboard::Right);

	m_supportedKeys.emplace("W", sf::Keyboard::W);
	m_supportedKeys.emplace("S", sf::Keyboard::S);
	m_supportedKeys.emplace("A", sf::Keyboard::A);
	m_supportedKeys.emplace("D", sf::Keyboard::D);
}

void Snake::init()
{
	std::ifstream ifsInit("config/snake.ini");

	if (ifsInit.is_open())
	{
		std::string functionOfTheString;

		int radius;
		int r, g, b, a;
		int thickness;

		ifsInit >> functionOfTheString >> radius;
		std::cout << functionOfTheString << " " << radius << "\n";

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		m_head.setRadius(float(radius));
		m_head.setFillColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		ifsInit >> functionOfTheString >> thickness;
		std::cout << functionOfTheString << " " << thickness << "\n";

		m_head.setOutlineColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));
		m_head.setOutlineThickness(float(thickness));

		ifsInit >> functionOfTheString >> m_speed;
		std::cout << functionOfTheString << " " << m_speed << "\n";

		ifsInit >> functionOfTheString >> radius;
		std::cout << functionOfTheString << " " << radius << "\n";

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		m_bodyPart.setRadius(float(radius));
		m_bodyPart.setFillColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		ifsInit >> functionOfTheString >> thickness;
		std::cout << functionOfTheString << " " << thickness << "\n";

		m_bodyPart.setOutlineColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));
		m_bodyPart.setOutlineThickness(float(thickness));
	}
	else
	{
		std::cout << "File \"config/snake.ini\" is not found!" << "\n";
	}

	ifsInit.close();

	std::cout << "\n";
}

void Snake::updateDt()
{
	m_dT = m_clock.restart().asSeconds();
}

void Snake::updateDirection()
{
	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Up"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["W"]))
		m_direction = m_supportedKeys["Up"];

	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Down"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["S"]))
		m_direction = m_supportedKeys["Down"];

	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Left"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["A"]))
		m_direction = m_supportedKeys["Left"];

	if (sf::Keyboard::isKeyPressed(m_supportedKeys["Right"])
		|| sf::Keyboard::isKeyPressed(m_supportedKeys["D"]))
		m_direction = m_supportedKeys["Right"];
}

void Snake::updatePosition(sf::CircleShape& object)
{
	/*if (object.getPosition().y + object.getRadius() >= playingfield.getPosition().y + playingfield.getSize().y / 2)
		object.setPosition(sf::Vector2f(object.getPosition().x,
			(playingfield.getPosition().y - playingfield.getSize().y / 2 + object.getRadius()) + 1.0f));

	if (object.getPosition().y - object.getRadius() <= playingfield.getPosition().y - playingfield.getSize().y / 2)
		object.setPosition(sf::Vector2f(object.getPosition().x,
			(playingfield.getPosition().y + playingfield.getSize().y / 2 - object.getRadius()) + 1.0f));

	if (object.getPosition().x + object.getRadius() >= playingfield.getPosition().x + playingfield.getSize().x / 2)
		object.setPosition(sf::Vector2f((playingfield.getPosition().x - playingfield.getSize().x / 2 + object.getRadius()) + 1.0f,
			object.getPosition().y));

	if (object.getPosition().x - object.getRadius() <= playingfield.getPosition().x - playingfield.getSize().x / 2)
		object.setPosition(sf::Vector2f((playingfield.getPosition().x + playingfield.getSize().x / 2 - object.getRadius()) + 1.0f,
			object.getPosition().y));*/

	if (m_direction == m_supportedKeys["Up"])
		object.move(0.0f * m_dT * m_speed, -1.0f * m_dT * m_speed);
	if (m_direction == m_supportedKeys["Down"])
		object.move(0.0f * m_dT * m_speed, 1.0f * m_dT * m_speed);
	if (m_direction == m_supportedKeys["Left"])
		object.move(-1.0f * m_dT * m_speed, 0.0f * m_dT * m_speed);
	if (m_direction == m_supportedKeys["Right"])
		object.move(1.0f * m_dT * m_speed, 0.0f * m_dT * m_speed);
}

void Snake::updatePosition(sf::Vector2f value, sf::CircleShape& object)
{
	object.move(value.x * m_dT * m_speed, value.y * m_dT * m_speed);
}

bool Snake::eat()
{
	if (std::pow(m_food.getPosition().x - m_head.getPosition().x, 2)
		+ std::pow(m_head.getPosition().y - m_food.getPosition().y, 2)
		<= std::pow(m_head.getRadius() + m_food.getRadius(), 2))
	{
		addBodyPart();

		std::cout << "body parts/score: " << m_coordinatesOfBodyParts.size() << "\n\n";

		return true;
	}

	return false;
}

void Snake::addBodyPart()
{
	if (m_coordinatesOfBodyParts.empty())
	{
		if (m_direction == m_supportedKeys["Up"])
			m_bodyPart.setPosition(m_head.getPosition().x, m_head.getPosition().y + m_head.getRadius() * 2 + 4.0f);
		if (m_direction == m_supportedKeys["Down"])
			m_bodyPart.setPosition(m_head.getPosition().x, m_head.getPosition().y - m_head.getRadius() * 2 - 4.0f);
		if (m_direction == m_supportedKeys["Left"])
			m_bodyPart.setPosition(m_head.getPosition().x + m_head.getRadius() * 2 + 4.0f, m_head.getPosition().y);
		if (m_direction == m_supportedKeys["Right"])
			m_bodyPart.setPosition(m_head.getPosition().x - m_head.getRadius() * 2 - 4.0f, m_head.getPosition().y);
	}
	else
	{
		if (m_direction == m_supportedKeys["Up"])
			m_bodyPart.setPosition(m_coordinatesOfBodyParts.back().getPosition().x,
				m_coordinatesOfBodyParts.back().getPosition().y + (m_head.getRadius() * 2 - (m_head.getRadius() - m_bodyPart.getRadius()) + 4.0f));
		if (m_direction == m_supportedKeys["Down"])
			m_bodyPart.setPosition(m_coordinatesOfBodyParts.back().getPosition().x,
				m_coordinatesOfBodyParts.back().getPosition().y - (m_head.getRadius() * 2 - (m_head.getRadius() - m_bodyPart.getRadius() - 4.0f)));
		if (m_direction == m_supportedKeys["Left"])
			m_bodyPart.setPosition(
				m_coordinatesOfBodyParts.back().getPosition().x + (m_head.getRadius() * 2 - (m_head.getRadius() - m_bodyPart.getRadius()) + 4.0f),
				m_coordinatesOfBodyParts.back().getPosition().y);
		if (m_direction == m_supportedKeys["Right"])
			m_bodyPart.setPosition(
				m_coordinatesOfBodyParts.back().getPosition().x - (m_head.getRadius() * 2 - (m_head.getRadius() - m_bodyPart.getRadius() - 4.0f)),
				m_coordinatesOfBodyParts.back().getPosition().y);
	}

	m_coordinatesOfBodyParts.push_back(m_bodyPart);
}

void Snake::updateBodyParts()
{
	if (!m_coordinatesOfBodyParts.empty())
	{
		if (m_coordinatesOfBodyParts[0].getPosition().y - m_bodyPart.getRadius()
			> m_head.getPosition().y + m_head.getRadius() * 2)
		{
			updatePosition(sf::Vector2f(0.0f, -1.0f), m_coordinatesOfBodyParts[0]);

			if (m_coordinatesOfBodyParts[0].getPosition().x < m_head.getPosition().x
				|| m_coordinatesOfBodyParts[0].getPosition().x > m_head.getPosition().x)
			{
				m_coordinatesOfBodyParts[0].setPosition(m_head.getPosition().x,
					m_head.getPosition().y + (m_head.getRadius() * 2 + 4.0f));
			}
		}
		if (m_coordinatesOfBodyParts[0].getPosition().y + m_bodyPart.getRadius()
			< m_head.getPosition().y - m_head.getRadius() * 2)
		{
			updatePosition(sf::Vector2f(0.0f, 1.0f), m_coordinatesOfBodyParts[0]);

			if (m_coordinatesOfBodyParts[0].getPosition().x < m_head.getPosition().x
				|| m_coordinatesOfBodyParts[0].getPosition().x > m_head.getPosition().x)
			{
				m_coordinatesOfBodyParts[0].setPosition(m_head.getPosition().x,
					m_head.getPosition().y - (m_head.getRadius() * 2 + 4.0f));
			}
		}
		if (m_coordinatesOfBodyParts[0].getPosition().x - m_bodyPart.getRadius()
			> m_head.getPosition().x + m_head.getRadius() * 2)
		{
			updatePosition(sf::Vector2f(-1.0f, 0.0f), m_coordinatesOfBodyParts[0]);

			if (m_coordinatesOfBodyParts[0].getPosition().y < m_head.getPosition().y
				|| m_coordinatesOfBodyParts[0].getPosition().y > m_head.getPosition().y)
			{
				m_coordinatesOfBodyParts[0].setPosition(m_head.getPosition().x + (m_head.getRadius() * 2 + 4.0f),
					m_head.getPosition().y);
			}
		}
		if (m_coordinatesOfBodyParts[0].getPosition().x + m_bodyPart.getRadius()
			< m_head.getPosition().x - m_head.getRadius() * 2)
		{
			updatePosition(sf::Vector2f(1.0f, 0.0f), m_coordinatesOfBodyParts[0]);

			if (m_coordinatesOfBodyParts[0].getPosition().y < m_head.getPosition().y
				|| m_coordinatesOfBodyParts[0].getPosition().y > m_head.getPosition().y)
			{
				m_coordinatesOfBodyParts[0].setPosition(m_head.getPosition().x - (m_head.getRadius() * 2 + 4.0f),
					m_head.getPosition().y);
			}
		}

		for (int index = 1; index < int(m_coordinatesOfBodyParts.size()); ++index)
		{
			if (m_coordinatesOfBodyParts[index].getPosition().y - m_bodyPart.getRadius()
				> m_coordinatesOfBodyParts[index - 1].getPosition().y + m_bodyPart.getRadius() * 2)
			{
				updatePosition(sf::Vector2f(0.0f, -1.0f), m_coordinatesOfBodyParts[index]);

				if (m_coordinatesOfBodyParts[index].getPosition().x < m_head.getPosition().x
					|| m_coordinatesOfBodyParts[index].getPosition().x > m_head.getPosition().x)
				{
					m_coordinatesOfBodyParts[index].setPosition(m_coordinatesOfBodyParts[index - 1].getPosition().x,
						m_coordinatesOfBodyParts[index - 1].getPosition().y + (m_coordinatesOfBodyParts[index - 1].getRadius() * 2 + 4.0f));
				}
			}
			if (m_coordinatesOfBodyParts[index].getPosition().y + m_bodyPart.getRadius()
				< m_coordinatesOfBodyParts[index - 1].getPosition().y - m_bodyPart.getRadius() * 2)
			{
				updatePosition(sf::Vector2f(0.0f, 1.0f), m_coordinatesOfBodyParts[index]);

				if (m_coordinatesOfBodyParts[index].getPosition().x < m_head.getPosition().x
					|| m_coordinatesOfBodyParts[index].getPosition().x > m_head.getPosition().x)
				{
					m_coordinatesOfBodyParts[index].setPosition(m_coordinatesOfBodyParts[index - 1].getPosition().x,
						m_coordinatesOfBodyParts[index - 1].getPosition().y - (m_coordinatesOfBodyParts[index - 1].getRadius() * 2 + 4.0f));
				}
			}
			if (m_coordinatesOfBodyParts[index].getPosition().x - m_bodyPart.getRadius()
				> m_coordinatesOfBodyParts[index - 1].getPosition().x + m_bodyPart.getRadius() * 2)
			{
				updatePosition(sf::Vector2f(-1.0f, 0.0f), m_coordinatesOfBodyParts[index]);

				if (m_coordinatesOfBodyParts[index].getPosition().y < m_head.getPosition().y
					|| m_coordinatesOfBodyParts[index].getPosition().y > m_head.getPosition().y)
				{
					m_coordinatesOfBodyParts[index].setPosition(
						m_coordinatesOfBodyParts[index - 1].getPosition().x + (m_coordinatesOfBodyParts[index - 1].getRadius() * 2 + 4.0f),
						m_coordinatesOfBodyParts[index - 1].getPosition().y);
				}
			}
			if (m_coordinatesOfBodyParts[index].getPosition().x + m_bodyPart.getRadius()
				< m_coordinatesOfBodyParts[index - 1].getPosition().x - m_bodyPart.getRadius() * 2)
			{
				updatePosition(sf::Vector2f(1.0f, 0.0f), m_coordinatesOfBodyParts[index]);

				if (m_coordinatesOfBodyParts[index].getPosition().y < m_head.getPosition().y
					|| m_coordinatesOfBodyParts[index].getPosition().y > m_head.getPosition().y)
				{
					m_coordinatesOfBodyParts[index].setPosition(
						m_coordinatesOfBodyParts[index - 1].getPosition().x - (m_coordinatesOfBodyParts[index - 1].getRadius() * 2 + 4.0f),
						m_coordinatesOfBodyParts[index - 1].getPosition().y);
				}
			}
		}
	}
}

void Snake::updateScore()
{
	m_score.setString("Score: " + std::to_string(m_coordinatesOfBodyParts.size()));
}

int Snake::getScore() const
{
	return int(m_coordinatesOfBodyParts.size());
}

bool Snake::isDead()
{
	for (int index = 0; index < int(m_coordinatesOfBodyParts.size()); ++index)
	{
		if (std::pow(m_coordinatesOfBodyParts[index].getPosition().x - m_head.getPosition().x, 2)
			+ std::pow(m_head.getPosition().y - m_coordinatesOfBodyParts[index].getPosition().y, 2)
			<= std::pow(m_head.getRadius() + m_bodyPart.getRadius(), 2))
		{
			std::cout << "snake is dead" << "\n\n";

			return true;
		}
	}

	if (m_head.getPosition().y + m_head.getRadius() >= m_playingfield.getPosition().y + m_playingfield.getSize().y / 2
		|| m_head.getPosition().y - m_head.getRadius() <= m_playingfield.getPosition().y - m_playingfield.getSize().y / 2
		|| m_head.getPosition().x + m_head.getRadius() >= m_playingfield.getPosition().x + m_playingfield.getSize().x / 2
		|| m_head.getPosition().x - m_head.getRadius() <= m_playingfield.getPosition().x - m_playingfield.getSize().x / 2)
	{
		std::cout << "snake is dead" << "\n\n";

		return true;
	}

	return false;
}

void Snake::clear()
{
	m_direction = sf::Keyboard::Key::Unknown;
	m_coordinatesOfBodyParts.clear();
	m_head.setPosition(sf::Vector2f(float(m_window.getSize().x / 2), float(m_window.getSize().y / 2)));
}

void Snake::render()
{
	m_window.draw(m_head);

	for (int index = 0; index < int(m_coordinatesOfBodyParts.size()); ++index)
		m_window.draw(m_coordinatesOfBodyParts[index]);

	m_window.draw(m_score);
}

void Snake::update()
{
	updateDt();
	updateDirection();
	updatePosition(m_head);
	updateBodyParts();
	updateScore();

	render();
}