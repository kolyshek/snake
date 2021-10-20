#include "Snake.hpp"
#include "Food.hpp"
#include "PlayingField.hpp"

void initWindow(sf::RenderWindow* window);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	sf::RenderWindow window;
	initWindow(&window);

	kp::PlayingField* playingField = new kp::PlayingField(&window);
	kp::Food* food = new kp::Food(&window);
	kp::Snake* snake = new kp::Snake(&window);

	snake->setGridSize(playingField->getGridSize());
	snake->setTilePositions(playingField->getTilePositions());
	snake->setTileSize(playingField->getTileSize());
	snake->chooseRandomIndex();
	food->setGridSize(playingField->getGridSize());
	food->setTilePositions(playingField->getTilePositions());
	food->setTileSize(playingField->getTileSize());
	food->chooseRandomIndex();

	sf::Font font;
	sf::Text score;

	if (font.loadFromFile("fonts/PixellettersFull.ttf"))
	{
		score.setFont(font);
		score.setFillColor(sf::Color(255, 255, 255, 255));
		score.setPosition(sf::Vector2f(20.0f, 0.0f));
	}
	else
	{
		KP_LOG("File \"fonts/PixellettersFull.ttf\" is not found!");
	}

	sf::Clock* clock = new sf::Clock();

	while (window.isOpen())
	{
		float dT = clock->restart().asSeconds();

		snake->update(dT);
		food->update(dT);

		if (snake->isDead())
		{
			snake->restart();
		}
		if (snake->isEating(food->getTileIndex()))
		{
			food->chooseRandomIndex();
		}

		score.setString("Score: " + std::to_string(snake->getScore()));

		sf::Event* event = new sf::Event();
		while (window.pollEvent(*event))
		{
			if (event->type == sf::Event::Closed || event->key.code == sf::Keyboard::Key::Escape)
			{
				KP_LOG("Exiting the program");
				window.close();
			}
		}
		delete event;

		window.clear(sf::Color::Black);

		playingField->render();
		snake->render();
		food->render();

		window.draw(score);
		window.display();
	}

	delete playingField;
	delete food;
	delete snake;
	delete clock;

	return EXIT_SUCCESS;
}

void initWindow(sf::RenderWindow* window)
{
	std::string functionOfTheString;

	std::string title("None");
	int width = 700;
	int height = 800;
	int frameRate = 60;
	bool vSync = false;

	std::ifstream ifsInit("config/window.ini");

	std::cout << std::boolalpha;

	if (ifsInit.is_open())
	{
		ifsInit >> functionOfTheString;
		std::getline(ifsInit, title);
		KP_LOG(functionOfTheString << title);

		ifsInit >> functionOfTheString >> width >> height;
		KP_LOG(functionOfTheString << " x-" << width << "/" << "y-" << height);

		ifsInit >> functionOfTheString >> frameRate;
		KP_LOG(functionOfTheString << " " << frameRate);

		ifsInit >> functionOfTheString >> vSync;
		KP_LOG(functionOfTheString << " " << vSync);
	}
	else
	{
		KP_LOG("File \"config/window.ini\" is not found!");
	}

	std::cout << std::noboolalpha;

	ifsInit.close();

	window->create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(frameRate);
	window->setVerticalSyncEnabled(vSync);

	std::cout << "\n";
}