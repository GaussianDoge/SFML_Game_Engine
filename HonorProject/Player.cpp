#include "Player.h"

void Player::initSoundEffect()
{
	sf::Music* axe = new sf::Music();
	if (axe->openFromFile("Resources/Sounds/axe.wav"))
	{
		sounds["AXE"] = axe;
	}
	else
	{
		throw("ERROR: Player couldn't load axe soundEffect");
	}
	
}

void Player::initVariable()
{
	currentHP = MAX_HEALTH;
	invincible = false;
	attackFinished = false;
	isAttacking = false;
	attackTimer = 0.f;
	vectorDir = sf::Vector2f(0.f, 1.f);
	attackDamage = 1;
}

void Player::initComponent()
{
	
}

void Player::initAnimation()
{
	SpriteAnimation* left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 0, 8);
	SpriteAnimation* right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 512, 8);
	SpriteAnimation* up = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 256, 8);
	SpriteAnimation* down = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 768, 8);

	SpriteAnimation* idle_up = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 256, 4);
	SpriteAnimation* idle_down = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 768, 4);
	SpriteAnimation* idle_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 0, 4);
	SpriteAnimation* idle_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 512, 4);

	SpriteAnimation* idle_up_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 128, 4);
	SpriteAnimation* idle_up_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 384, 4);
	SpriteAnimation* idle_down_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 896, 4);
	SpriteAnimation* idle_down_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 0, 640, 4);

	SpriteAnimation* attack_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 0, 6);
	SpriteAnimation* attack_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 512, 6);
	SpriteAnimation* attack_up = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 256, 6);
	SpriteAnimation* attack_down = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 768, 6);

	SpriteAnimation* up_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 128, 8);
	SpriteAnimation* up_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 384, 8);
	SpriteAnimation* down_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 896, 8);
	SpriteAnimation* down_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 512, 640, 8);

	SpriteAnimation* attack_up_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 128, 6);
	SpriteAnimation* attack_up_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 384, 6);
	SpriteAnimation* attack_down_left = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 896, 6);
	SpriteAnimation* attack_down_right = new SpriteAnimation(texture, FRAMETIME, 128, 128, 1536, 640, 6);

	animeMap["LEFT"] = left;
	animeMap["RIGHT"] = right;
	animeMap["UP"] = up;
	animeMap["DOWN"] = down;

	animeMap["IDLE_UP"] = idle_up;
	animeMap["IDLE_DOWN"] = idle_down;
	animeMap["IDLE_LEFT"] = idle_left;
	animeMap["IDLE_RIGHT"] = idle_right;

	animeMap["IDLE_UP_LEFT"] = idle_up_left;
	animeMap["IDLE_UP_RIGHT"] = idle_up_right;
	animeMap["IDLE_DOWN_LEFT"] = idle_down_left;
	animeMap["IDLE_DOWN_RIGHT"] = idle_down_right;

	animeMap["ATTACK_LEFT"] = attack_left;
	animeMap["ATTACK_RIGHT"] = attack_right;
	animeMap["ATTACK_UP"] = attack_up;
	animeMap["ATTACK_DOWN"] = attack_down;

	animeMap["UP_LEFT"] = up_left;
	animeMap["UP_RIGHT"] = up_right;
	animeMap["DOWN_LEFT"] = down_left;
	animeMap["DOWN_RIGHT"] = down_right;

	animeMap["ATTACK_UP_LEFT"] = attack_up_left;
	animeMap["ATTACK_UP_RIGHT"] = attack_up_right;
	animeMap["ATTACK_DOWN_LEFT"] = attack_down_left;
	animeMap["ATTACK_DOWN_RIGHT"] = attack_down_right;
}

Player::Player(float x, float y, sf::Texture* texture)
{
	initVariable();
	initComponent();
	createSprite(texture, 128, 128);
	initAnimation();
	setPosition(x, y);
	initSoundEffect();
	resizeHitbox(sf::Vector2f(70.f, 70.f));
}

Player::~Player()
{
	for (auto item : animeMap)
	{
		delete item.second;
	}

	for (auto item : sounds)
	{
		delete item.second;
	}
}

void Player::attack(const float &dt)
{
	if (attackTimer <= FRAMETIME)
	{
		attackTimer += dt;
		if (!isAttacking)
		{
			sounds["AXE"]->play();
		}
		isAttacking = true;
	}
	else
	{
		endAttack();
		attackTimer = 0.f;
	}
}

void Player::endAttack()
{
	isAttacking = false;
	sounds["AXE"]->stop();
}

bool Player::getAttack()
{
	return isAttacking;
}

bool Player::getAttackFinished()
{
	return attackFinished;
}

void Player::playAnimation(std::string dir, const float dt)
{
	attackFinished = animeMap.at(dir)->play(dt);
	sprite->setTextureRect(*animeMap.at(dir)->getState());
}

void Player::up()
{
	vectorDir.y = 1.f;
}

void Player::down()
{
	vectorDir.y = -1.f;
}

void Player::left()
{
	vectorDir.x = -1.f;
}

void Player::right()
{
	vectorDir.x = 1.f;
}

void Player::resetXVector()
{
	vectorDir.x = 0.f;
}

void Player::resetYVector()
{
	vectorDir.y = 0.f;
}

sf::Vector2f Player::getVectorDir()
{
	return vectorDir;
}

int Player::getHP()
{
	return currentHP;
}

int Player::getMaxHP()
{
	return MAX_HEALTH;
}

int Player::getAttackDamage()
{
	return attackDamage;
}

void Player::decreaseHP(const int& num)
{
	if (num > 0)
	{
		hitbox.setOutlineColor(sf::Color::Red);
	}

	if (num <= 0)
	{
		hitbox.setOutlineColor(sf::Color::White);
	}

	currentHP -= num;
	if (currentHP < 0)
	{
		currentHP = 0;
	}
}

void Player::increaseHP(const int& num)
{
	currentHP += num;
	if (currentHP > MAX_HEALTH)
	{
		currentHP = MAX_HEALTH;
	}
}

bool Player::isInvicible()
{
	return invincible;
}

void Player::setInvicible(bool isInvicible)
{
	this->invincible = isInvicible;
}


