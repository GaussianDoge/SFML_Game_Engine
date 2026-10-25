#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSize, sf::Texture* texture)
{
	this->texture = texture;
	grid.setTexture(*this->texture);
	grid.setOrigin(grid.getGlobalBounds().width / 2, grid.getGlobalBounds().height / 2);
	grid.setPosition(x, y);
}

Tile::Tile(float x, float y, float gridSize, sf::Texture* texture, bool isRandom)
{
	if (isRandom)
	{
		this->texture = texture;
		int period = rand() % 4 + 1;
		grid.setTexture(*this->texture);
		grid.setOrigin(grid.getGlobalBounds().width / 2, grid.getGlobalBounds().height / 2);
		grid.rotate(90 * period);
		grid.setPosition(x, y);
	}
	else
	{
		this->texture = texture;
		grid.setTexture(*this->texture);
		grid.setPosition(x, y);
	}
}

Tile::~Tile()
{
}

bool Tile::getInteractable()
{
	return isInteractable;
}

void Tile::update(const float& dt)
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(grid);
}

void Tile::renderHitbox(sf::RenderTarget* target)
{
}
