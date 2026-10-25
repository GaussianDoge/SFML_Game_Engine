#ifndef RAIN_H
#define RAIN_H

#include "Weather.h"
class Rain :
    public Weather
{
private:

    float rainTimer;
    float dt;

    bool isInit;
    std::vector<sf::Sprite*> rain;
    std::vector<sf::Vector2f> rainOriginalPos;

    sf::Music* rainSound;

    void initRain(const sf::Vector2f& playerPos);
    void resetRain();

public:
    Rain(sf::Texture* texture);
    virtual ~Rain();

    void update(const float& dt);
    void render(sf::RenderTarget* target, const sf::Vector2f& playerPos);
};
#endif

