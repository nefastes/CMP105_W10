#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "TileWork.h"
#include "Player.h"
#include <string>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	//Level map
	TileWork tileWork;

	//Player
	Player player;
	sf::Texture playerTex;
	sf::RectangleShape playerSize;
	sf::RectangleShape playerHitBox;

	//Debug
	bool masterDebug = false;
	sf::Text debugPos;
	sf::Font debugTxtFont;
};