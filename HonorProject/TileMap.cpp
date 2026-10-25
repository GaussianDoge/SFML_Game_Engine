#include "TileMap.h"

TileMap::TileMap(sf::Texture* mapTexture, unsigned int gridSize, sf::Vector2u maxSize)
{
	gridSizeU = gridSize; //256
	gridSizeF = (float) gridSize;
	this->maxSize = maxSize;
	layers = 3;

	map.resize(maxSize.x);
	for (int x = 0; x < maxSize.x; x++)
	{
		map.push_back(std::vector<std::vector<Tile*>>());

		for (int y = 0; y < maxSize.y; y++)
		{
			map[x].resize(maxSize.y);
			map[y].push_back(std::vector<Tile*>());

			for (int z = 0; z < 1; z++)
			{
				map[x][y].resize(layers);
				map[x][y].push_back(new TileGrid(x * gridSizeF, y * gridSizeF, gridSizeF, mapTexture, true));
			}
		}
	}
}

TileMap::~TileMap()
{
	for (auto x : map)
	{
		for (auto y : x)
		{
			for (auto z : y)
			{
				delete z;
			}
		}
	}

	for (auto item : mapItems)
	{
		delete item;
	}
}

void TileMap::update(const float& dt)
{
	for (auto x : map)
	{
		for (auto y : x)
		{
			for (auto z : y)
			{
				if (z != nullptr)
				{
					z->update(dt);
				}
			}
		}
	}

	for (auto item : mapItems)
	{
		if (item != nullptr)
		{
			item->update(dt);
		}
	}
}



void TileMap::addItem(Tile* item)
{
	item->grid.setOrigin(sf::Vector2f(item->grid.getGlobalBounds().width / 2, item->grid.getGlobalBounds().height / 2));
	mapItems.push_back(item);
}

unsigned int TileMap::getGridSize()
{
	return gridSizeU;
}

sf::Vector2u TileMap::getBoundary()
{
	sf::Vector2u mapBoundary(maxSize.x * gridSizeU - gridSizeU / 2, maxSize.y * gridSizeU - gridSizeU / 2);
	return mapBoundary;
}

void TileMap::render(sf::RenderTarget* target, sf::Vector2f playerPos)
{
	//Grid
	for (auto x : map)
	{
		for (auto y : x)
		{
			for (auto z : y)
			{
				if (z != nullptr)
				{
					if (z->grid.getPosition().x > (playerPos.x - target->getSize().x / 2 - 2 * gridSizeF) // Left Boundary
						&& z->grid.getPosition().x < (playerPos.x + target->getSize().x / 2 + 2 * gridSizeF)) // Right Boundary
					{
						if (z->grid.getPosition().y > (playerPos.y - target->getSize().y / 2 - 2 * gridSizeF) // Upward Boundary
							&& z->grid.getPosition().y < (playerPos.y + target->getSize().y / 2 + 2 * gridSizeF)) // Downward Boundary
						{
							z->render(*target);
						}
					}
				}
			}
		}
	}

}

void TileMap::renderItems(sf::RenderTarget* target, sf::Vector2f playerPos)
{
	for (auto item : mapItems)
	{
		if (item != nullptr)
		{
			if (item->grid.getPosition().x > (playerPos.x - target->getSize().x / 2 - 2 * gridSizeF) // Left Boundary
				&& item->grid.getPosition().x < (playerPos.x + target->getSize().x / 2 + 2 * gridSizeF)) // Right Boundary
			{
				if (item->grid.getPosition().y > (playerPos.y - target->getSize().y / 2 - 2 * gridSizeF) // Upward Boundary
					&& item->grid.getPosition().y < (playerPos.y + target->getSize().y / 2 + 2 * gridSizeF)) // Downward Boundary
				{
					item->render(*target);

					//HitBox Debug
					if (item->getInteractable())
					{
						item->renderHitbox(target);
					}
				}
			}
		}
	}
}
