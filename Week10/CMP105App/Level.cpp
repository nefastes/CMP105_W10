#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	playerTex.loadFromFile("gfx/Player.png");
	player.setTexture(&playerTex);
	player.setSize(sf::Vector2f(32, 32));
	//player.setOrigin(sf::Vector2f(player.getSize().x /2, player.getSize().y /2));
	player.setInput(input);
	player.setWindow(window);
	player.setPosition(sf::Vector2f(100, 200));
	player.setVelocity(sf::Vector2f(200, 0));
	player.setCollisionBox(sf::FloatRect(6, 6, 20, 26));

	//Debugging of all initialised objects in level.h
	if (masterDebug)
	{
		player.setDebugging(true);
		debugTxtFont.loadFromFile("font/arial.ttf");
		debugPos.setFont(debugTxtFont);
		debugPos.setCharacterSize(24);
		debugPos.setPosition(0, 0);
		debugPos.setFillColor(sf::Color::Red);
		tileWork.setDebugging(true);
	}
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	player.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	player.update(dt);
	tileWork.update(dt, player);

	if (masterDebug)
	{
		debugPos.setString(std::to_string(player.getPosition().x) +", " +std::to_string(player.getPosition().y));
	}
}

// Render level
void Level::render()
{
	beginDraw();
	tileWork.renderMap(window);
	window->draw(player);
	if (masterDebug)
	{
		window->draw(*player.getDebugObjectSize());
		window->draw(*player.getDebugCollisionBox());
		tileWork.renderDebuggingTiles(window);
		window->draw(debugPos);
	}
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}