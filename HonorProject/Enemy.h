#ifndef ENEMY_H
#define ENEMY_H

#include "MageBullet.h"

class Enemy :
    public Entity
{
protected:
	std::map<std::string, SpriteAnimation*> animeMap;
	int health;

	virtual void initAnimation() = 0;

public:
	Enemy(int health, float x, float y);
	virtual ~Enemy();

	void playAnimation(std::string dir, const float dt);
	void move(float dt, float playerX, float playerY);
	void decreaseHealth();
	int getHealth();
	sf::FloatRect getGlobalBounds();
};
#endif

