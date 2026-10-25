#include "Rain.h"

void Rain::initRain(const sf::Vector2f& playerPos)
{
	int x = (screenWidth / sprite.getGlobalBounds().width) * 3;
	int y = (screenHeight / sprite.getGlobalBounds().height) * 2;

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			int randPos = rand() % 100 - 50;
			sf::Sprite* drop = new sf::Sprite();
			drop->setTexture(*texture);
			sf::Vector2f pos(playerPos.x + sprite.getGlobalBounds().width / 2 * (i - x / 2) + randPos, (j - y / 2) * sprite.getGlobalBounds().height + randPos);
			drop->setPosition(pos);
			rain.push_back(drop);
			rainOriginalPos.push_back(pos);
		}
	}
}

void Rain::resetRain()
{
	if (rain.size() == rainOriginalPos.size())
	{
		for (int i = 0; i < rain.size(); i++)
		{
			if (rain.at(i) != nullptr)
			{
				rain.at(i)->setPosition(rainOriginalPos.at(i));
			}
		}
	}
}

Rain::Rain(sf::Texture* texture) : Weather(texture)
{
	rainTimer = 0.f; 
	isInit = false;

	rainSound = new sf::Music();
	rainSound->openFromFile("Resources/Sounds/rain.ogg");
	rainSound->setLoop(true);
	rainSound->play();
}

Rain::~Rain()
{
	for (auto item : rain)
	{
		if (item != nullptr)
		{
			delete item;
		}
	}

	rainSound->pause();
	delete rainSound;
}

void Rain::update(const float& dt)
{
	this->dt = dt;

	rainTimer += dt;
}

void Rain::render(sf::RenderTarget* target, const sf::Vector2f& playerPos)
{
	if (!isInit)
	{
		this->screenWidth = target->getSize().x;
		this->screenHeight = target->getSize().y;
		initRain(playerPos);
		isInit = true;
	}


	for (auto item : rain)
	{
		if (item != nullptr)
		{
			target->draw(*item);
			item->move(0.f, 600.f * dt);
		}
	}

	for (auto item : rain)
	{
		if (item != nullptr)
		{
			if (item->getPosition().y > screenHeight + playerPos.y)
			{
				int randPos = rand() % 100 - 50;
				item->setPosition(sf::Vector2f(item->getPosition().x, (playerPos.y - screenHeight + randPos + sprite.getGlobalBounds().height)));
			}

			if (item->getPosition().x < playerPos.x - screenWidth)
			{
				int randPos = rand() % 100 - 50;
				item->setPosition(sf::Vector2f(playerPos.x + screenWidth / 2 + randPos + sprite.getGlobalBounds().width / 2, item->getPosition().y));
			}


			if (item->getPosition().x > playerPos.x + screenWidth)
			{
				int randPos = rand() % 100 - 50;
				item->setPosition(sf::Vector2f(playerPos.x - screenWidth / 2 + randPos - sprite.getGlobalBounds().width / 2, item->getPosition().y));
			}
		}
	}
}
