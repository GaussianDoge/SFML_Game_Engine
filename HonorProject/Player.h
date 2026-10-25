#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
	
	const float FRAMETIME = 1;

	//Data
	const int MAX_HEALTH = 10;
	int currentHP;
	bool invincible;
	int attackDamage;

	//Attack
	bool isAttacking;
	bool attackFinished;
	float attackTimer;
	sf::Vector2f vectorDir;

	//Player Animation
	std::map<std::string, SpriteAnimation*> animeMap;

	//Sound Effect
	std::map<std::string, sf::Music*> sounds;

	void initSoundEffect();
	void initVariable();
	void initComponent();
	void initAnimation();

public:
	Player(float x, float y, sf::Texture* texture);
	virtual ~Player();

	void attack(const float &dt);
	void endAttack();
	bool getAttack();
	bool getAttackFinished();
	void playAnimation(std::string dir, const float dt);

	void up();
	void down();
	void left();
	void right();
	void resetXVector();
	void resetYVector();
	sf::Vector2f getVectorDir();

	int getHP();
	int getMaxHP();
	int getAttackDamage();
	void decreaseHP(const int& num);
	void increaseHP(const int& num);
	bool isInvicible();
	void setInvicible(bool isInvicible);
};
#endif