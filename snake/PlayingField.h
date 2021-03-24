#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include "libraries.h"

class PlayingField
{
private:
	sf::RenderWindow& m_window;

	sf::RectangleShape m_borders;

	void render();
public:
	PlayingField(sf::RenderWindow& window);

	void init();

	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;

	void update();
};

#endif // !PLAYINGFIELD_H