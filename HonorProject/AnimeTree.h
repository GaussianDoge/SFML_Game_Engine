#ifndef ANIMETREE_H
#define ANIMETREE_H
#include "TileGrid.h"

class AnimeTree :
    public TileGrid
{
private:

    float timer;
    float frameTime;
    int numFile;
    bool reverse;

public:
    AnimeTree(float x, float y, float gridSize, sf::Texture* texture);
    virtual ~AnimeTree();

    void update(const float &dt) override;
};
#endif

