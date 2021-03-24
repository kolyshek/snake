#include "Snake.h"
#include "Food.h"
#include "PlayingField.h"

void run(sf::RenderWindow& window, PlayingField& playingfield, Food& food, Snake& snake);
void windowInit(sf::RenderWindow& window);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	sf::RenderWindow window;
    windowInit(window);

	PlayingField playingfield(window);
	playingfield.init();

	Food food(window);
	food.init();

	Snake snake(window, food, playingfield);
	snake.init();

	run(window, playingfield, food, snake);

	return EXIT_SUCCESS;
}

void run(sf::RenderWindow& window, PlayingField& playingfield, Food& food, Snake& snake)
{
	food.setRandomPosition(playingfield, snake);

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Key::Escape)
			{
				std::cout << "quit" << "\n";
				window.close();
			}
        }

        window.clear(sf::Color::Black);

		playingfield.update();
		food.update();
		snake.update();

		if (snake.isDead())
			snake.clear();

		if (snake.eat())
			food.setRandomPosition(playingfield, snake);

        window.display();
    }
}

void windowInit(sf::RenderWindow& window)
{
	std::string functionOfTheString;

	std::string title("None");
	int width = 700;
	int height = 800;
	int frameRate = 120;
	bool VSync = false;

	std::ifstream ifsInit("config/window.ini");

	std::cout << std::boolalpha;

	if (ifsInit.is_open())
	{
		ifsInit >> functionOfTheString;
		std::getline(ifsInit, title);
		std::cout << functionOfTheString << title << "\n";

		ifsInit >> functionOfTheString >> width >> height;
		std::cout << functionOfTheString << " x-" << width << " y-" << height << "\n";

		ifsInit >> functionOfTheString >> frameRate;
		std::cout << functionOfTheString << " " << frameRate << "\n";

		ifsInit >> functionOfTheString >> VSync;
		std::cout << functionOfTheString << " " << VSync << "\n";
	}
	else
	{
		std::cout << "File \"config/window.ini\" is not found!" << "\n";
	}

	std::cout << std::noboolalpha;

	ifsInit.close();

	window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(frameRate);
	window.setVerticalSyncEnabled(VSync);

	std::cout << "\n";
}