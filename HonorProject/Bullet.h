#ifndef BULLET_H
#define BULLET_H

#include "Player.h"

class Bullet :
    public Entity
{
protected:
    bool destroyable;
    std::map<std::string, SpriteAnimation*> animeMap;

    virtual void initAnimation() = 0;

public:
    Bullet(float x, float y, sf::Texture* texture);
    virtual ~Bullet();

    void move(const float& dt, const float dx, const float dy);
    void playAnimation(std::string state, const float dt);
    void setVelocity(float velocity);
    void setDestroyable(bool destroyable);
};
#endif

