#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "TileMap.h"
#include "Rain.h"
#include "GUI.h"

class GameState : public State
{
private:

	sf::View view;

	Player* player;
	GUI* ui;

	TileMap* map;
	std::vector<Tile*> mapItems;

	std::vector<Weather*> weather;

	std::vector<Mage*> enemies;

	std::map<std::string, sf::Music*> bgm;
	bool playBgm;

	sf::Font font;
	
	void initUI();
	void initFont();
	void initView();
	void initKeybinds();
	void initTextures();
	void initMap();
	void initWeather();
	void initPlayers();
	void initEnemies();
	void initBgm();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	~GameState();

	void cameraMovement(const float& dt, const float x, const float y);
	void setCameraPos(sf::Vector2f pos);
	void enemyUpdate(const float& dt);
	void weatherUpdate(const float& dt);
	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void checkCollision(const float& dt);
	void checkMapItemCollision(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};
#endif

