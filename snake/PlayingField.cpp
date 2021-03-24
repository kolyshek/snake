#include "PlayingField.h"

PlayingField::PlayingField(sf::RenderWindow& window)
	: m_window(window)
{
	m_borders.setSize(sf::Vector2f(float(m_window.getSize().x - 40), float(m_window.getSize().y - 80)));
	m_borders.setFillColor(sf::Color(32, 32, 32, 255));
	m_borders.setOutlineThickness(2);
	m_borders.setOutlineColor(sf::Color(255, 0, 0, 255));
	m_borders.setOrigin(sf::Vector2f(m_borders.getSize().x / 2, m_borders.getSize().y / 2));
	m_borders.setPosition(sf::Vector2f(float(m_window.getSize().x / 2), float(m_window.getSize().y / 2) + 20));
}

void PlayingField::init()
{
	std::ifstream ifsInit("config/playing_field.ini");

	if (ifsInit.is_open())
	{
		std::string functionOfTheString;

		int r, g, b, a;

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		m_borders.setFillColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));

		ifsInit >> functionOfTheString >> r >> g >> b >> a;
		std::cout << functionOfTheString
			<< " r-" << r
			<< " g-" << g
			<< " b-" << b
			<< " a-" << a << "\n";

		m_borders.setOutlineColor(sf::Color(sf::Uint8(r), sf::Uint8(g), sf::Uint8(b), sf::Uint8(a)));
	}
	else
	{
		std::cout << "File \"config/playing_field.ini\" is not found!" << "\n";
	}

	ifsInit.close();

	std::cout << "\n";
}

sf::Vector2f PlayingField::getSize() const
{
	return m_borders.getSize();
}

sf::Vector2f PlayingField::getPosition() const
{
	return m_borders.getPosition();
}

void PlayingField::render()
{
	m_window.draw(m_borders);
}

void PlayingField::update()
{
	render();
}