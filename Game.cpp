#include "Game.h"

// Initializer Functions

void Game::initWindow()
{
	// creating the window
	this->window = new sf::RenderWindow(sf::VideoMode(600, 600), "Snake Game", sf::Style::Close);

	// sets the frames per second of the window
	this->window->setFramerateLimit(10);
}

void Game::initShapes()
{
	// creating outline of grid
	outline.setFillColor			(sf::Color(0,0,0,0));
	outline.setSize					(sf::Vector2f(596,596));
	outline.setOutlineColor			(sf::Color::White);
	outline.setOutlineThickness		(2.0f);
	outline.setPosition				(2,2);

	// creating a rectangle for the grid
	rect.setFillColor				(sf::Color::Black);
	rect.setSize					(sf::Vector2f(gridBoxWidth, gridBoxHeight));
	rect.setOutlineColor			(sf::Color::White);
	rect.setOutlineThickness		(2.0f);

	// creating rectangle for snakes body
	snakeBody.setFillColor			(sf::Color::Red);
	snakeBody.setSize				(sf::Vector2f(gridBoxWidth - 2.0f, gridBoxHeight - 2.0f));

}

void Game::initTextures()
{
	headTexture.loadFromFile("snake.png");
}

void Game::initFood()
{
	// random position for the food
	foodx = (rand() % 20) * 30;
	foody = (rand() % 20) * 30;

	food.setFillColor				(sf::Color::Green);
	food.setSize					(sf::Vector2f(gridBoxWidth - 2.0f, gridBoxHeight - 2.0f));
	food.setPosition				(sf::Vector2f(foodx, foody));
}

void Game::initSnake()
{
	snakeLength = 4;
}

void Game::initHead()
{
	head.setTexture					(&headTexture);
	head.setSize					(sf::Vector2f(gridBoxWidth - 2.0f, gridBoxHeight - 2.0f));
	head.setPosition				(s[0].x, s[0].y);
}

// Constructors / Destructors

Game::Game()
{
	this->initWindow();
	this->initShapes();
	this->initFood();
	this->initSnake();
	this->initHead();
	this->initTextures();
}

Game::~Game()
{
	delete this->window;
}

// Static Functions 

void Game::updateSFMLEvents()
{

	while (this->window->pollEvent(this->event)) 
	{
		switch(this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();
}

void Game::render()
{

	this->window->clear();

	// -- Render items --

	// GRID
	for (int i{ 0 }; i < gridAmountX; i++) {

		for (int j{ 0 }; j < gridAmountY; j++) {

			int rectX = gridBoxWidth * i;
			int rectY = gridBoxHeight * j;

			rect.setPosition(sf::Vector2f(rectX, rectY));
			this->window->draw(rect);
		}
	}

	// GRID outline
	this->window->draw(outline);

	// FOOD
	this->window->draw(food);

	// SNAKE HEAD
	s[0].x += 1 * xVelocity;
	s[0].y += 1 * yVelocity;

	head.setPosition(s[0].x * gridBoxWidth, s[0].y * gridBoxHeight);

	// SNAKE BODY
	for (int i = snakeLength; i > 0; i--) {

		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;

		snakeBody.setPosition(s[i].x*gridBoxWidth, s[i].y*gridBoxHeight);
		this->window->draw(snakeBody);
	}

	this->window->draw(head);

	this->window->display();
}

void Game::run()
{

	srand(time(0));

	while (this->window->isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && xVelocity != 1)  { xVelocity = -1; yVelocity = 0; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && xVelocity != -1) { xVelocity = 1; yVelocity = 0; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && yVelocity != -1) { xVelocity = 0; yVelocity = 1; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && yVelocity != 1)  { xVelocity = 0; yVelocity = -1; }

		// checking for collision with window frame
		if (s[0].x < 0)		{ s[0].x = 20; }
		if (s[0].x > 20)	{ s[0].x = -1; }
		if (s[0].y < 0)		{ s[0].y = 20; }
		if (s[0].y > 20)	{ s[0].y = -1; }		

		// checking for collision with tail
		for (int i = 1; i < snakeLength; i++) {
			if (s[0].x == s[i+1].x && s[0].y == s[i+1].y) { snakeLength = 4; }
		}

		// checking collision with food
		if (s[0].x == foodx / 30 && s[0].y == foody / 30) {
			snakeLength++;

			// random position for the food
			foodx = (rand() % 20) * 30;
			foody = (rand() % 20) * 30;

			food.setPosition(foodx, foody);
		}

		this->update();
		this->render();

	}
}
