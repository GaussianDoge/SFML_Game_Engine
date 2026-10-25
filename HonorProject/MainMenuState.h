#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	bool playBgm;
	sf::Music* bgm;

	std::map<std::string, Button*> buttons;

	void initBacground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initBgm();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	~MainMenuState();

	void endBgm();
	void endState();
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};
#endif

