#include "AnimeTree.h"

AnimeTree::AnimeTree(float x, float y, float gridSize, sf::Texture* texture):TileGrid(x, y, gridSize, texture)
{
	timer = 0.f;
	frameTime = 1.5;
	numFile = -1;
	reverse = false;
}

AnimeTree::~AnimeTree()
{
}

void AnimeTree::update(const float& dt)
{
	std::string address = "Resources/Textures/Tree/animTree/animTree";
	timer += 10 * dt;
	if (timer >= frameTime)
	{
		timer = 0;
		if (numFile < 29 && !reverse)
		{
			numFile++;
			address.append(std::to_string(numFile));
			address.append(".png");
			if (!texture->loadFromFile(address))
			{
				throw("ERROR: AnimeTree couldn't load tree texture");
			}
			grid.setTexture(*texture);

			if (numFile == 29)
			{
				reverse = true;
			}
		}
		else if (numFile >= 29 || reverse)
		{
			numFile--;
			address.append(std::to_string(numFile));
			address.append(".png");
			if (!texture->loadFromFile(address))
			{
				throw("ERROR: AnimeTree couldn't load tree texture");
			}
			grid.setTexture(*texture);

			if (numFile == 0)
			{
				reverse = false;
			}
		}
	}
}
