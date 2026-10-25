#ifndef TILEMAP_H
#define TILEMAP_H

#include "AnimeTree.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned int gridSizeU;
	unsigned int layers;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::vector<Tile*> mapItems;

public:
	TileMap(sf::Texture* mapTexture, unsigned int gridSize, sf::Vector2u maxSize);
	virtual ~TileMap();

	void update(const float& dt);
	void addItem(Tile* item);
	unsigned int getGridSize();
	sf::Vector2u getBoundary();
	void render(sf::RenderTarget *target, sf::Vector2f playerPos);
	void renderItems(sf::RenderTarget* target, sf::Vector2f playerPos);
};
#endif

