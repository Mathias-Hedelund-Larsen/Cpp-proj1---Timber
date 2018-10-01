//Implement needed libs
#include "pch.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>

using namespace sf;

const int CLOUD_COUNT = 3;
const bool SHOW_CONSOLE = true;

int main()
{
	ShowWindow(GetConsoleWindow(), SHOW_CONSOLE);

	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Woodcutter", Style::Fullscreen);
	window.setFramerateLimit(60);

	Texture bg;

	bg.loadFromFile("graphics/background.png");

	Sprite bgs;
	bgs.setTexture(bg);
	bgs.setPosition(0, 0);

	Texture treeTexture;
	treeTexture.loadFromFile("graphics/tree.png");
	Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(810, 0);

	Texture beeTexture;
	beeTexture.loadFromFile("graphics/bee.png");
	Sprite beeSprite;
	beeSprite.setTexture(beeTexture);
	beeSprite.setPosition(0, 800);
	beeSprite.scale(-1, 1);

	bool beeMoving = false;
	float beeSpeed = 0;

	Texture cloudTexture;
	cloudTexture.loadFromFile("graphics/cloud.png");
	Sprite clouds[CLOUD_COUNT];
	bool cloudsMove[CLOUD_COUNT];
	float cloudsSpeed[CLOUD_COUNT];

	for (int i = 0; i < CLOUD_COUNT; i++)
	{
		clouds[i].setTexture(cloudTexture);
		clouds[i].setPosition(0, 250 * i);
		cloudsMove[i] = false;
		cloudsSpeed[i] = 0;
	}

	sf::Clock clock;

	//Bool to pause the game
	bool paused = false;

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		sf::Time deltaTime = clock.restart();

		if (SHOW_CONSOLE)
		{
			std::cout << "Fps: " << 1 / deltaTime.asSeconds() << "\n";
		}

		if (!beeMoving)
		{
			srand((int)time(0) * 10);
			beeSpeed = (rand() % 200) + 200;

			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			beeSprite.setPosition(1922, height);
			beeMoving = true;
		}
		else
		{
			beeSprite.setPosition(beeSprite.getPosition().x - (beeSpeed * deltaTime.asSeconds()), beeSprite.getPosition().y);

			if (beeSprite.getPosition().x <= 0)
			{
				beeMoving = false;
			}
		}

		for (int i = 0; i < CLOUD_COUNT; i++)
		{
			if (!cloudsMove[i])
			{
				srand((int)time(0) * 10 * (i + 1));
				cloudsSpeed[i] = (rand() % 200);

				srand((int)time(0) * 10 * (i + 1));
				float height = (rand() % 150);
				clouds[i].setPosition(-220, height);
				cloudsMove[i] = true;
			}
			else
			{
				clouds[i].setPosition(clouds[i].getPosition().x + (cloudsSpeed[i] * deltaTime.asSeconds()), clouds[i].getPosition().y);

				if (clouds[i].getPosition().x > 1920)
				{
					cloudsMove[i] = false;
				}
			}
		}

		window.clear();

		window.draw(bgs);

		for (int i = 0; i < CLOUD_COUNT; i++)
		{
			window.draw(clouds[i]);
		}

		window.draw(treeSprite);
		window.draw(beeSprite);

		window.display();
	}

	if (SHOW_CONSOLE)
	{
		std::cout << "Press enter to close";
		std::cin.get();
	}

	return 0;
}