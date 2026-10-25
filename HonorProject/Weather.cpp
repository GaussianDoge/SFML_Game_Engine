#include "Weather.h"

Weather::Weather(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
}

Weather::~Weather()
{
}

void Weather::update(const float& dt)
{
}

void Weather::render(sf::RenderTarget* target, const sf::Vector2f& playerPos)
{
	screenWidth = target->getSize().x;
	screenHeight = target->getSize().y;

	float width = sprite.getGlobalBounds().width;
	float height = sprite.getGlobalBounds().height;

	int x = target->getSize().x / sprite.getGlobalBounds().width + 1;
	int y = target->getSize().y / sprite.getGlobalBounds().height + 1;

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			sprite.setPosition(sf::Vector2f(sprite.getGlobalBounds().width * i, j * sprite.getGlobalBounds().height));
			target->draw(sprite);
		}
	}
}
