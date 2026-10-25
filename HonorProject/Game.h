#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Window
	sf::RenderWindow *window;
	sf::Event event;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	//Delta Time
	sf::Clock dtClock;
	float dt;

	//States of the Game
	std::stack<State*> states;

	//Key Map
	std::map<std::string, int> supportedKeys;

	//Initialization
	void initWindow();
	void initState();
	void initKeys();
public:
	Game();
	virtual ~Game();

	void endApplication();
	void updateSFMLEvent();
	void update();
	void render();
	void run();
	void updateDt();
	float getDt();
};
#endif

