#ifndef GUI_H
#define GUI_H

#include "Button.h"
#include "Player.h"

class GUI
{
private:
	sf::Texture texture;

	sf::Sprite healthBar1;
	sf::Sprite healthBar2;

public:
	GUI();
	virtual ~GUI();

	void update(Player* player);
	void render(sf::RenderTarget* target);
};
#endif
