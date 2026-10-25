#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "SpriteAnimation.h"


class Tile
{
public:
	sf::Sprite grid;
	sf::Texture* texture;
	sf::RectangleShape hitBox;
	bool isInteractable;

public:
	Tile();
	Tile(float x, float y, float gridSize, sf::Texture* texture);
	Tile(float x, float y, float gridSize, sf::Texture* texture, bool isRandom);
	virtual ~Tile();

	bool getInteractable();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
	virtual void renderHitbox(sf::RenderTarget* target);
};
#endif

