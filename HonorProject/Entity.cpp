#include "Entity.h"

void Entity::initVariable()
{
	texture = nullptr;
	sprite = nullptr;
	velocity = 200.0;
	positiveX = positiveY = negativeX = negativeY = true;
}

Entity::Entity()
{
	initVariable();
}

Entity::~Entity()
{
	delete this->sprite;
}

void Entity::createSprite(sf::Texture* texture, int x, int y)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
	sprite->setTextureRect(sf::IntRect(0, 0, x, y));
	sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
	hitbox.setSize(sf::Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::White);
	hitbox.setOutlineThickness(1);
	hitbox.setOrigin(sf::Vector2f(hitbox.getSize().x/2, hitbox.getSize().y/2));
	hitbox.setPosition(sprite->getPosition());
}

float Entity::getVelocity()
{
	return this->velocity;
}

sf::FloatRect Entity::getGlobalBounds()
{
	return sprite->getGlobalBounds();
}

void Entity::setPosition(const float x, const float y)
{
	if (sprite)
	{
		sprite->setPosition(x, y);
		hitbox.setPosition(x, y);
	}
}

sf::Vector2f Entity::getPosition()
{
	return sprite->getPosition();
}

sf::RectangleShape Entity::getHitbox()
{
	return this->hitbox;
}

void Entity::resizeHitbox(sf::Vector2f newSize)
{
	hitbox.setSize(newSize);
	hitbox.setOrigin(sf::Vector2f(newSize.x / 2, newSize.y / 2));
}

void Entity::move(const float &dt, const float x, const float y, sf::Vector2u mapBoundary)
{
	float i = x, j = y;

	if (abs(x) > 1.f)
	{
		x > 0 ? i = 1.f : i = -1.f;
	}

	if (abs(y) > 1.f)
	{
		y > 0 ? j = 1.f : j = -1.f;
	}

	j = -j; //Downward is positive

	//Check Map Border
	if (hitbox.getPosition().x < -128.f && i < 0.f)
	{
		i = 0.f;
	}
	else if (hitbox.getPosition().x > mapBoundary.x && i > 0.f)
	{
		i = 0.f;
	}

	if (hitbox.getPosition().y < -128.f && j < 0.f)
	{
		j = 0.f;
	}
	else if (hitbox.getPosition().y > mapBoundary.y && j > 0.f)
	{
		j = 0.f;
	}

	//Check Movement Direction
	if (!positiveX && i > 0.f)
	{
		i = 0.f;
	}

	if (!negativeX && i < 0.f)
	{
		i = 0.f;
	}

	if (!positiveY && j < 0.f)
	{
		j = 0.f;
	}

	if (!negativeY && j > 0.f)
	{
		j = 0.f;
	}

	if (sprite)
	{
		if (x == 0.f || y == 0.f)
		{
			sprite->move(i * velocity * dt, j * velocity * dt);
		}
		else
		{
			sprite->move(velocity * cos(PI / 4.f) * i * dt, velocity * sin(PI / 4.f) * j * dt);
		}
	}	

	hitbox.setPosition(sprite->getPosition());
}

bool Entity::isOutMap(sf::Vector2u mapBoundary)
{
	if (sprite->getPosition().x < 0.f 
		|| sprite->getPosition().y < 0.f 
		|| sprite->getPosition().x > mapBoundary.x 
		|| sprite->getPosition().y > mapBoundary.y)
	{
		return true;
	}
	return false;
}

void Entity::stop(int xDir, int yDir)
{
	if (xDir > 0)
	{
		positiveX = false;
	}
	else if (xDir < 0)
	{
		negativeX = false;
	}

	if (yDir > 0)
	{
		positiveY = false;
	}
	else if (yDir < 0)
	{
		negativeY = false;
	}
}

void Entity::resetDir()
{
	positiveX = positiveY = negativeX = negativeY = true;
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	if (sprite)
	{
		target->draw(*sprite);
		
		//hitbox debug
		target->draw(hitbox);
	}
	
}
