#include "MageBullet.h"

void MageBullet::initAnimation()
{
	SpriteAnimation* mageBullet1 = new SpriteAnimation(texture, 1.f, 13, 13, 0, 0, 5);

	this->animeMap["MAGE_BULLET_1"] = mageBullet1;
}

MageBullet::MageBullet(sf::Vector2f targetPos, const sf::Vector2f& ownerPos, float x, float y, sf::Texture* texture):Bullet(13, 13, texture)
{
	relativeDistance = 0.f;
	maxDistance = 500.f;
	this->vector.x = targetPos.x - ownerPos.x;
	this->vector.y = -(targetPos.y - ownerPos.y);
	setPosition(x, y);
	sprite->scale(sf::Vector2f(2.f, 2.f));
	initAnimation();
}

MageBullet::~MageBullet()
{
}

void MageBullet::setMaxDistance(float newDistance)
{
	this->maxDistance = newDistance;
}

void MageBullet::updateRelativePosition(const sf::Vector2f& ownerPos)
{
	this->relativeDistance = sqrt(pow(this->sprite->getPosition().x - ownerPos.x, 2) + pow(this->sprite->getPosition().y - ownerPos.y, 2));
}

bool MageBullet::isOutRange()
{
	return relativeDistance > maxDistance;
}

void MageBullet::update(const float& dt, const sf::Vector2f& ownerPos)
{
	playAnimation("MAGE_BULLET_1", dt);
	updateRelativePosition(ownerPos);
	move(dt, vector.x, vector.y);
}
