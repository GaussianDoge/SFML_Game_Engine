#ifndef MAGE_H
#define MAGE_H

#include "Enemy.h"

class Mage :
    public Enemy
{
private:
    sf::Vector2f curVector;

    float coolDownTimer;
    float coolDown;
    float bulletVelocity;

    std::vector<MageBullet*> bullets;

    void initAnimation();

public:

    Mage(int health, float x, float y, sf::Texture* texture);
    virtual ~Mage();

    int checkBulletDamge(const sf::RectangleShape& player);

    void setVelocity(float velocity);
    void shoot(const sf::Vector2f& targetPos, const float& dt, sf::Texture* texture);
    void update(const float& dt, const sf::Vector2f& targetPos, sf::Texture* bulletTexture);
    void render(sf::RenderTarget* target);
};
#endif

