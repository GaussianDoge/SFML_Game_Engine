#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <math.h>
#define PI 3.1415926535897932384626433832795

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "SpriteAnimation.h"

class Entity
{
private:
	void initVariable();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::RectangleShape hitbox;
	float velocity;

	bool positiveX, positiveY, negativeX, negativeY;

public:
	Entity();
	virtual ~Entity();

	void createSprite(sf::Texture* texture, int x, int y);
	float getVelocity();
	virtual sf::FloatRect getGlobalBounds();

	virtual void setPosition(const float x, const float y);
	virtual sf::Vector2f getPosition();
	virtual sf::RectangleShape getHitbox();
	virtual void resizeHitbox(sf::Vector2f newSize);
	virtual void move(const float &dt, const float x, const float y, sf::Vector2u mapBoundary);
	virtual bool isOutMap(sf::Vector2u mapBoundary);
	virtual void stop(int xDir, int yDir);
	virtual void resetDir();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};
#endif

