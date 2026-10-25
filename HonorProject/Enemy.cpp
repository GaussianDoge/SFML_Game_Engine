#include "Enemy.h"


Enemy::Enemy(int health, float x, float y)
{
	this->health = health;
}

Enemy::~Enemy()
{
	for (auto item : animeMap)
	{
		if (item.second != nullptr)
		{
			delete item.second;
		}
	}
}

void Enemy::playAnimation(std::string dir, const float dt)
{
	this->animeMap.at(dir)->play(dt);
	sprite->setTextureRect(*animeMap.at(dir)->getState());
}

void Enemy::move(float dt, float playerX, float playerY)
{
	if (sprite)
	{
		if (abs(getPosition().x - playerX) < 700.f && abs(getPosition().y - playerY) < 700.f)
		{
			int xDir, yDir;
			xDir = playerX - getPosition().x > 0 ? 1.f : -1.f;
			yDir = playerY - getPosition().y > 0 ? 1.f : -1.f;

			if (abs(playerX - getPosition().x) < 1.5)
			{
				xDir = 0.f;
			}

			if (abs(playerY - getPosition().y) < 1.5)
			{
				yDir = 0.f;
			}

			sprite->move(xDir * velocity * dt, yDir * velocity * dt);

			hitbox.setPosition(sprite->getPosition());
		}
	}
}

void Enemy::decreaseHealth()
{
	if (health > 0)
	{
		health--;
	}
}

int Enemy::getHealth()
{
	return health;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return sprite->getGlobalBounds();
}
