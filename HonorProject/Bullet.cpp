#include "Bullet.h"

Bullet::Bullet(float x, float y, sf::Texture* texture)
{
	this->destroyable = false;

	createSprite(texture, x, y);
}

Bullet::~Bullet()
{
	for (auto item : animeMap)
	{
		if (item.second != nullptr)
		{
			delete item.second;
		}
	}
}

void Bullet::move(const float& dt, const float dx, const float dy)
{
	float i = dx, j = dy;

	if (abs(dx) > 1.f)
	{
		dx > 0 ? i = 1.f : i = -1.f;
	}

	if (abs(dy) > 1.f)
	{
		dy > 0 ? j = 1.f : j = -1.f;
	}


	j = -j; //Downward is positive

	if (sprite)
	{
		sprite->move(velocity * cos(atan(abs(dy / dx))) * i * dt, velocity * sin(atan(abs(dy / dx))) * j * dt);
	}

	hitbox.setPosition(sprite->getPosition());
}

void Bullet::playAnimation(std::string state, const float dt)
{
	this->animeMap.at(state)->play(dt);
	sprite->setTextureRect(*animeMap.at(state)->getState());
}

void Bullet::setVelocity(float velocity)
{
	this->velocity = velocity;
}

void Bullet::setDestroyable(bool destroyable)
{
	this->destroyable = destroyable;
}
