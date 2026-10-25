#include "SpriteAnimation.h"



SpriteAnimation::SpriteAnimation(sf::Texture* textureSheet, float frameTime, int width, int height, int initX, int initY, int frames)
{
	this->textureSheet = textureSheet;
	this->frameTime = frameTime;
	this->width = width;
	this->height = height;
	this->timer = 0.f;
	this->frames = frames;
	initRect = sf::IntRect(initX, initY, width, height);
	endRect = sf::IntRect(initX + width * frames - width, initY, width, height);
	curRect = initRect;
	sprite.setTexture(*textureSheet);
	sprite.setTextureRect(initRect);
	isPaused = false;
	done = false;
}

SpriteAnimation::~SpriteAnimation()
{
}

bool SpriteAnimation::play(const float dt)
{
	done = false;
	timer += dt;
	if (timer >= frameTime / frames && !isPaused)
	{
		timer = 0;
		if (curRect != endRect)
		{
			curRect.left += width;
			done = false;
		}
		else
		{
			curRect.left = initRect.left;
			done = true;
		}
		sprite.setTextureRect(curRect);
	}
	return done;
}

sf::IntRect* SpriteAnimation::getState()
{
	return &curRect;
}

void SpriteAnimation::reset()
{
	curRect.left = initRect.left;
	sprite.setTextureRect(initRect);
}

void SpriteAnimation::pause()
{
	isPaused = true;
}

void SpriteAnimation::unPause()
{
	isPaused = false;
}

void SpriteAnimation::setTexture(sf::Texture* textureSheet)
{
	this->textureSheet = textureSheet;
}

bool SpriteAnimation::isDone()
{
	return done;
}
