#pragma once
#include "Framework/TileMap.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Player.h"
class TileWork
{
private:
	TileMap tileMap;
	GameObject tile;
	std::vector<GameObject> tiles;

public:
	TileWork();
	~TileWork();
	void renderMap(sf::RenderWindow* hwnd) { tileMap.render(hwnd); };
	void update(float dt, Player& p);
};

