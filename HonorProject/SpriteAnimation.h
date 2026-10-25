#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class SpriteAnimation
{
private:
    sf::Texture* textureSheet;
    sf::Sprite sprite;
    float frameTime;
    float timer;
    int frames;
    sf::IntRect initRect;
    sf::IntRect endRect;
    sf::IntRect curRect;
    int width;
    int height;
    bool isPaused;
    bool done;

public:
    SpriteAnimation(sf::Texture* textureSheet, float frameTime, int width, int height, int initX, int initY, int frames);
    virtual ~SpriteAnimation();

    bool play(const float dt);
    sf::IntRect* getState();
    void reset();
    void pause();
    void unPause();
    void setTexture(sf::Texture* textureSheet);
    bool isDone();
};
#endif

