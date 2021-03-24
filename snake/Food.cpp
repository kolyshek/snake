#include "Food.h"
#include "Snake.h"

Food::Food(sf::RenderWindow& window)
	: m_window(window)
{
	m_food.setRadius(8);
	m_food.setFillColor(sf::Color(51, 204, 51, 255));
	m_food.setOrigin(sf::Vector2f(m_food.getRadius(), m_food.getRadius()));
}

void Food::init()
{
	std::ifstream ifsInit("config/food.ini");

	if (ifsInit.is_open())
	{
		std::string functionOfTheString;

		int radius;
		int r, g, b, a;

		ifsInit >> functionOfTheString >> radius;
		std::cout << functionOfTheString << " " << radius << "\n";

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		m_food.setRadius(float(radius));
		m_food.setFillColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));
	}
	else
	{
		std::cout << "File \"config/food.ini\" is not found!" << "\n";
	}

	ifsInit.close();

	std::cout << "\n";
}

void Food::setRandomPosition(const PlayingField& playingfield, Snake& snake)
{
	auto getRandomNumber = [](int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

		return static_cast<int>(rand() * fraction * (static_cast<double>(max) - static_cast<double>(min) + 1) + min);
	};

	m_food.setPosition(
		float(getRandomNumber(
			int((playingfield.getPosition().x - playingfield.getSize().x / 2) + m_food.getRadius()),
			int((playingfield.getPosition().x + playingfield.getSize().x / 2) - m_food.getRadius()))),
		float(getRandomNumber(
			int((playingfield.getPosition().y - playingfield.getSize().y / 2) + m_food.getRadius()),
			int((playingfield.getPosition().y + playingfield.getSize().y / 2) - m_food.getRadius()))));

	if (!snake.getScore())
	{
		std::cout << "food x min/max position: " << int((playingfield.getPosition().x - playingfield.getSize().x / 2) + m_food.getRadius()) << "/"
			<< int((playingfield.getPosition().x + playingfield.getSize().x / 2) - m_food.getRadius()) << "\n"
			<< "food y min/max position: " << int((playingfield.getPosition().y - playingfield.getSize().y / 2) + m_food.getRadius()) << "/"
			<< int((playingfield.getPosition().y + playingfield.getSize().y / 2) - m_food.getRadius()) << "\n\n";
	}
}

float Food::getRadius() const
{
	return m_food.getRadius();
}

sf::Vector2f Food::getPosition() const
{
	return m_food.getPosition();
}

void Food::render()
{
	m_window.draw(m_food);
}

void Food::update()
{
	render();
}