#include "TileGrid.h"

void TileGrid::initHitbox()
{
	hitBox.setSize(sf::Vector2f(grid.getGlobalBounds().width, grid.getGlobalBounds().height));
	//hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::White);
	hitBox.setOutlineThickness(1);
	hitBox.setPosition(grid.getPosition());
}

TileGrid::TileGrid()
{
	isInteractable = false;
	initHitbox();
}

TileGrid::TileGrid(float x, float y, float gridSize, sf::Texture* texture):Tile(x, y, gridSize, texture)
{
	isInteractable = false;
	initHitbox();
}

TileGrid::TileGrid(float x, float y, float gridSize, sf::Texture* texture, bool isRandom):Tile(x, y, gridSize, texture, isRandom)
{
	isInteractable = false;
	initHitbox();
}

TileGrid::~TileGrid()
{
}

void TileGrid::update(const float& dt)
{
}

void TileGrid::setIneractable(bool interactable)
{
	isInteractable = interactable;
}

bool TileGrid::checkInteraction(const sf::RectangleShape& playerPos)
{
	return grid.getGlobalBounds().intersects(playerPos.getGlobalBounds());
}

void TileGrid::setHitBoxSize(float width, float height)
{
	hitBox.setSize(sf::Vector2f(width, height));
	//hitBox.setOrigin(sf::Vector2f(width / 2, height / 2));
}

void TileGrid::scale(float size)
{
	grid.setScale(size, size);
	grid.setOrigin(grid.getGlobalBounds().width / 2, grid.getGlobalBounds().height / 2);
	hitBox.setPosition(grid.getPosition());
	//hitBox.setPosition(grid.getPosition().x + grid.getOrigin().x / 2, grid.getPosition().y + grid.getOrigin().y / 2);
}

void TileGrid::renderHitbox(sf::RenderTarget* target)
{
	target->draw(hitBox);
}
