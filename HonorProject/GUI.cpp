#include "GUI.h"

GUI::GUI()
{
	texture.loadFromFile("Resources/GUI/ui_resource_bars.png");

	healthBar1.setTexture(texture);
	healthBar1.setTextureRect(sf::IntRect(283, 0, 283, 44));
	healthBar1.setPosition(0, 0);

	healthBar2.setTexture(texture);
	healthBar2.setTextureRect(sf::IntRect(0, 0, 240, 44));
	healthBar2.setPosition(7, 0);
}

GUI::~GUI()
{
}

void GUI::update(Player* player)
{
	int maxHP = player->getMaxHP();
	int curHP = player->getHP();

	healthBar2.setTextureRect(sf::IntRect(0, 0, 36 + 204 * curHP / maxHP, 44));
}

void GUI::render(sf::RenderTarget* target)
{
	target->draw(healthBar1);
	target->draw(healthBar2);
}
