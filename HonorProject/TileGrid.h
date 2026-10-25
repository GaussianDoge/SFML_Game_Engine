#pragma once
#include "Tile.h"
class TileGrid :
    public Tile
{
protected:

    void initHitbox();

public:
    TileGrid();
    TileGrid(float x, float y, float gridSize, sf::Texture* texture);
    TileGrid(float x, float y, float gridSize, sf::Texture* texture, bool isRandom);
    virtual ~TileGrid();

    virtual void update(const float& dt);
    void setIneractable(bool interactable);
    bool checkInteraction(const sf::RectangleShape& playerPos);
    void setHitBoxSize(float width, float height);
    void scale(float size);

    void renderHitbox(sf::RenderTarget* target);
};

