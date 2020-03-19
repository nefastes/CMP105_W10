#include "TileWork.h"
TileWork::TileWork()
{
	//Load the texture only once
	tileMap.loadTexture("gfx/marioTiles.png");

	//Creating the tileSet
	for(int i = 0; i < 21; i++)				//General init of all tiles to default settings, tiles specific settings are stated just after this loop
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}

	tiles[0].setCollider(false);			//It's going to be the sky texture, set we do not want to collide with it.
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16));		//Set the texture to the sky square only
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16));			//etc.
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tiles[4].setTextureRect(sf::IntRect(0, 17, 16, 16));
	tiles[5].setTextureRect(sf::IntRect(17, 17, 16, 16));
	tiles[6].setTextureRect(sf::IntRect(34, 17, 16, 16));
	tiles[7].setTextureRect(sf::IntRect(51, 0, 16, 16));
	tiles[8].setTextureRect(sf::IntRect(51, 17, 16, 16));
	tiles[9].setTextureRect(sf::IntRect(102, 0, 16, 16));
	tiles[10].setTextureRect(sf::IntRect(102, 17, 16, 16));
	tiles[11].setTextureRect(sf::IntRect(119, 0, 16, 16));
	tiles[12].setTextureRect(sf::IntRect(119, 17, 16, 16));
	tiles[13].setTextureRect(sf::IntRect(136, 0, 16, 16));
	tiles[14].setTextureRect(sf::IntRect(136, 17, 16, 16));
	tiles[15].setTextureRect(sf::IntRect(153, 0, 16, 16));
	tiles[16].setTextureRect(sf::IntRect(153, 17, 16, 16));
	tiles[17].setTextureRect(sf::IntRect(170, 0, 16, 16));
	tiles[18].setTextureRect(sf::IntRect(170, 17, 16, 16));
	tiles[19].setTextureRect(sf::IntRect(187, 0, 16, 16));
	tiles[20].setTextureRect(sf::IntRect(187, 17, 16, 16));

	tileMap.setTileSet(tiles);				//Finally, once all settings have been made, set it

	//Declaring the map dimensions
	sf::Vector2u mapSize(20, 10);

	//Build the map
	std::vector<int> map = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 17, 19,
		0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 9, 10, 5, 18, 20,
		0, 0, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 0, 9, 10, 5, 5, 5, 5,
		0, 0, 0, 0, 0, 0, 4, 6, 1, 2, 2, 2, 2, 2, 10, 5, 5, 5, 5, 5,
		0, 0, 0, 0, 0, 0, 4, 6, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		1, 2, 2, 2, 2, 3, 4, 6, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		4, 5, 5, 5, 5, 6, 4, 6, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	};

	//Set the map
	tileMap.setTileMap(map, mapSize);
	tileMap.setPosition(sf::Vector2f(0, 340));
	tileMap.buildLevel();
}

TileWork::~TileWork()
{

}

void TileWork::update(float dt, Player& p)
{
	bool hasCollided = false;
	std::vector<GameObject>* world = tileMap.getLevel();
	for (unsigned i = 0; i < (int)world->size(); ++i)
	{
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(&p, &(*world)[i]))
			{
				p.collisionResponse(&(*world)[i]);
				p.setGroundState(true);
				hasCollided = true;
			}
		}
	}
	if(!hasCollided) p.setGroundState(false);
}