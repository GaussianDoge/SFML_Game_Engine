#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Weather
{
protected:
	sf::Texture* texture;
	sf::Sprite sprite;

	float screenWidth;
	float screenHeight;

public:
	Weather(sf::Texture* texture);
	virtual ~Weather();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target, const sf::Vector2f& playerPos);
};
#endif

