#include "Mage.h"

void Mage::initAnimation()
{
	SpriteAnimation* mage1 = new SpriteAnimation(texture, 1.f, 85, 94, 0, 0, 4);
	SpriteAnimation* mage2 = new SpriteAnimation(texture, 1.f, 85, 94, 0, 94, 4);

	this->animeMap["ANIME_1"] = mage1;
	this->animeMap["ANIME_2"] = mage2;
}

Mage::Mage(int health, float x, float y, sf::Texture* texture) : Enemy(health, x, y)
{
	coolDownTimer = 0.f;
	coolDown = 10.f;
	bulletVelocity = 300.f;

	createSprite(texture, 85, 94);
	setPosition(x, y);
	initAnimation();
}

Mage::~Mage()
{
	for (auto item : bullets)
	{
		if (item != nullptr)
		{
			delete item;
		}
	}
}

int Mage::checkBulletDamge(const sf::RectangleShape& player)
{
	int damageDone = 0;

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i) != nullptr)
		{
			if (bullets.at(i)->getHitbox().getGlobalBounds().intersects(player.getGlobalBounds()))
			{
				damageDone++;
				delete bullets.at(i);
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}

	return damageDone;
}

void Mage::setVelocity(float velocity)
{
	this->velocity = velocity;
}

void Mage::shoot(const sf::Vector2f& targetPos, const float& dt, sf::Texture* bulletTexture)
{
	coolDownTimer += 10 * dt;
	if (coolDownTimer >= coolDown)
	{
		if (abs(targetPos.x - getPosition().x) < 500.f && abs(targetPos.y - getPosition().y) < 500.f)
		{
			MageBullet* bullet = new MageBullet(targetPos, getPosition(), this->sprite->getPosition().x, this->sprite->getPosition().y, bulletTexture);
			bullet->setVelocity(bulletVelocity);
			bullets.push_back(bullet);
			coolDownTimer = 0.f;
		}
	}
}

void Mage::update(const float& dt, const sf::Vector2f& targetPos, sf::Texture* bulletTexture)
{
	shoot(targetPos, dt, bulletTexture);

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i) != nullptr)
		{
			bullets.at(i)->update(dt, sprite->getPosition());
			if (bullets.at(i)->isOutRange())
			{
				delete bullets.at(i);
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
	}
}

void Mage::render(sf::RenderTarget* target)
{
	Entity::render(target);

	for (auto item : bullets)
	{
		if (item != nullptr)
		{
			item->render(target);
		}
	}
}
