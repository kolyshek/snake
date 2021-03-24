#ifndef SNAKE_H
#define SNAKE_H

#include "libraries.h"
#include "Food.h"
#include "PlayingField.h"

class Snake
{
private:
	sf::RenderWindow& m_window;
	Food& m_food;
	PlayingField& m_playingfield;

	sf::CircleShape m_head;
	sf::CircleShape m_bodyPart;
	std::vector<sf::CircleShape> m_coordinatesOfBodyParts;
	int m_changedBodyPart;

	sf::Font m_font;
	sf::Text m_score;

	sf::Clock m_clock;
	float m_dT;
	int m_speed;

	std::map<std::string, sf::Keyboard::Key> m_supportedKeys;
	sf::Keyboard::Key m_direction;

	void addBodyPart();

	void updateDt();
	void updateDirection();
	void updatePosition(sf::CircleShape& object);
	void updatePosition(sf::Vector2f value, sf::CircleShape& object);
	void updateBodyParts();
	void updateScore();

	void render();
public:
	Snake(sf::RenderWindow& window, Food& food, PlayingField& playingfield);

	void init();

	bool eat();

	int getScore() const;

	bool isDead();
	void clear();

	void update();
};

#endif // !SNAKE_H