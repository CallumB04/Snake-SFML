#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <ctime>
#include <random>

class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::Event event;

	sf::RectangleShape rect;
	sf::RectangleShape outline;
	sf::RectangleShape snakeBody;
	sf::RectangleShape food;
	sf::RectangleShape head;

	sf::Texture headTexture;

	// random position for the food
	int foodx;
	int foody;

	// Snake - snake[0] = head
	struct Snake {
		int x = 10, y = 10;
	} s[100];

	int xVelocity = 1, yVelocity = 0;   // snakes constant momentum
	int snakeLength;			        // snakes current length

	bool repeat = true;

	int gridAmountX = 20; int gridAmountY = 20;      // amount of squares on the grid
	int gridBoxWidth = 30; int gridBoxHeight = 30;   // width and height of each square on the grid

	// Initialisation

	void initWindow();
	void initShapes();
	void initTextures();
	void initFood();
	void initSnake();
	void initHead();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Main Functions
	void updateSFMLEvents();
	void update();
	void render();
	void run();

};

