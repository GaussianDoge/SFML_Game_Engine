#ifndef MAGEBULLET_H
#define MAGEBULLET_H

#include "Bullet.h"
class MageBullet :
    public Bullet
{
private:
    float relativeDistance;
    float maxDistance;
    sf::Vector2f vector;

    void initAnimation();

public:
    MageBullet(sf::Vector2f targetPos, const sf::Vector2f& ownerPos, float x, float y, sf::Texture* texture);
    virtual ~MageBullet();

    void setMaxDistance(float newDistance);
    void updateRelativePosition(const sf::Vector2f& ownerPos);
    bool isOutRange();
    void update(const float& dt, const sf::Vector2f& ownerPos);
};
#endif

