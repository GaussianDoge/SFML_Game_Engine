#include "GameState.h"

void GameState::initUI()
{
	ui = new GUI();
}

void GameState::initFont()
{
	if (!font.loadFromFile("Resources/Fonts/PTSansNarrow-Bold.ttf"))
	{
		throw("Error: GameState could not load font file");
	}
}

void GameState::initView()
{
	view = sf::View();
	view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
}

void GameState::initKeybinds()
{
	std::ifstream keys("Config/controlKeys.ini");

	if (keys)
	{
		std::string function;
		std::string key;

		while (keys >> function >> key)
		{
			keybinds[function] = supportedKeys->at(key);
		}
	}
	
	keys.close();
}

void GameState::initTextures()
{
	sf::Texture playerTexture;
	if (playerTexture.loadFromFile("Resources/Textures/Player/minotaur_alpha.png"))
	{
		textures["PLAYER"] = playerTexture;
	}
	else
	{
		throw("ERROR: GameState couldn't load player texture");
	}

	sf::Texture mapTexture;
	if (mapTexture.loadFromFile("Resources/Textures/Grid/grass.png"))
	{
		textures["MAP"] = mapTexture;
	}
	else
	{
		throw("ERROR: GameState couldn't load map texture");
	}

	sf::Texture mageTexture;
	if (mageTexture.loadFromFile("Resources/Textures/Enemy/mage-1-85x94.png"))
	{
		textures["MAGE"] = mageTexture;
	}
	else
	{
		throw("ERROR: GameState couldn't load mage texture");
	}

	sf::Texture animeTreeTexture;
	if (animeTreeTexture.loadFromFile("Resources/Textures/Tree/animTree/animTreepathing.png"))
	{
		textures["ANIMTREE"] = animeTreeTexture;
	}
	else
	{
		throw("ERROR: GameState couldn't load animTree texture");
	}

	sf::Texture treeFour;
	for (int i = 0; i < 8; i++)
	{
		std::string address = "Resources/Textures/Tree/treeFour";
		address.append(std::to_string(i));
		address.append(".png");
		if (treeFour.loadFromFile(address))
		{
			std::string name = "TREE_FOUR";
			name.append(std::to_string(i));
			textures[name] = treeFour;
		}
		else
		{
			throw("ERROR: GameState couldn't load treeFour texture");
		}
	}

	sf::Texture mageBullet;
	if (mageBullet.loadFromFile("Resources/Textures/Enemy/mage-bullet-13x13.png"))
	{
		textures["MAGE_BULLET"] = mageBullet;
	}
	else
	{
		throw("ERROR: GameState couldn't load mageBullet texture");
	}

	sf::Texture rainEffect;
	if (rainEffect.loadFromFile("Resources/Effects/rain.png"))
	{
		textures["RAIN_EFFECT"] = rainEffect;
	}
	else
	{
		throw("ERROR: GameState couldn't load rainEffect texture");
	}

	sf::Texture bossRoom;
	if (bossRoom.loadFromFile("Resources/Textures/Buildings/bossRoom.png"))
	{
		textures["BOSS_ROOM"] = bossRoom;
	}
	else
	{
		throw("ERROR: GameState couldn't load bossRoom texture");
	}
}

void GameState::initMap()
{
	map = new TileMap(&textures["MAP"], 256, sf::Vector2u(100, 100));
	unsigned int gridSize = map->getGridSize();

	
	AnimeTree* animTree = new AnimeTree(6 * gridSize, 6 * gridSize, gridSize, &textures["ANIMTREE"]);
	mapItems.push_back(animTree);
	map->addItem(animTree);
	

	//Tree
	for (int i = 0; i < 30; i++)
	{
		std::string address = "TREE_FOUR";
		address.append(std::to_string(i % 8));
		TileGrid* treeFour = new TileGrid((1.5 + i) * gridSize, 0.5 * gridSize, gridSize, &textures[address]);
		mapItems.push_back(treeFour);
		map->addItem(treeFour);
	}

	for (int i = 0; i < 30; i++)
	{
		std::string address = "TREE_FOUR";
		address.append(std::to_string(i % 8));
		TileGrid* treeFour = new TileGrid((1 + i) * gridSize, 1 * gridSize, gridSize, &textures[address]);
		mapItems.push_back(treeFour);
		map->addItem(treeFour);
	}

	//BossRoom
	TileGrid* bossRoom = new TileGrid(2 * gridSize, 3 * gridSize, gridSize, &textures["BOSS_ROOM"]);
	bossRoom->setIneractable(true);
	bossRoom->scale(0.5);
	bossRoom->setHitBoxSize(350, 300);
	mapItems.push_back(bossRoom);
	map->addItem(bossRoom);
}

void GameState::initWeather()
{
	Rain* rain = new Rain(&textures["RAIN_EFFECT"]);
	weather.push_back(rain);
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, &textures["PLAYER"]);
	player->setPosition(view.getCenter().x, view.getCenter().y);
	player->setInvicible(true);
}

void GameState::initEnemies()
{
	for (int i = 0; i < 10; i++)
	{
		int randomX = rand() % 3000;
		int randomY = rand() % 3000;
		enemies.push_back(new Mage(2, (float) randomX, (float) randomY, &textures["MAGE"]));
		enemies[i]->setVelocity(50.f);
	}
}

void GameState::initBgm()
{
	sf::Music* grass = new sf::Music();
	grass->openFromFile("Resources/Music/MONACA.flac");
	bgm["Grass"] = grass;
}

//Constructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	playBgm = false;
	initFont();
	initView();
	initKeybinds();	
	initTextures();
	initMap();
	initWeather();
	initPlayers();
	initEnemies();
	initUI();
	initBgm();
}

GameState::~GameState()
{
	delete this->player;
	for (auto* item : enemies)
	{
		delete item;
	}
	for (auto item : bgm)
	{
		delete item.second;
	}
	for (auto item : mapItems)
	{
		delete item;
	}
	for (auto item : weather)
	{
		delete item;
	}
}



void GameState::cameraMovement(const float& dt, const float x, const float y)
{
	if (x == 0.f || y == 0.f)
	{
		view.move(x * player->getVelocity() * dt, -y * player->getVelocity() * dt);
	}
	else
	{
		view.move(player->getVelocity() * cos(PI / 4.f) * x * dt, player->getVelocity() * sin(PI / 4.f) * -y * dt);
	}
}

void GameState::setCameraPos(sf::Vector2f pos)
{
	view.move(pos.x - view.getCenter().x, pos.y - view.getCenter().y);
}

void GameState::enemyUpdate(const float& dt)
{
	for (auto* item : enemies)
	{
		item->playAnimation("ANIME_1", dt);
		item->move(dt, player->getPosition().x, player->getPosition().y);
		item->update(dt, player->getPosition(), &textures["MAGE_BULLET"]);
	}
}

void GameState::weatherUpdate(const float& dt)
{
	for (auto item : weather)
	{
		if (item != nullptr)
		{
			item->update(dt);
		}
	}
}

void GameState::endState()
{
	quit = true;
}

void GameState::updateInput(const float& dt)
{
	bool isPressed = false;
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	sf::Vector2f vector(0.f, 0.f);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))) //Left
	{
		isPressed = true;
		left = true;
		vector.x -= 1.f;
		player->left();
		player->playAnimation("LEFT", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_LEFT", dt);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))) //Right
	{
		isPressed = true;
		right = true;
		vector.x += 1.f;
		player->right();
		player->playAnimation("RIGHT", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_RIGHT", dt);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))) // Up
	{
		isPressed = true;
		up = true;
		vector.y += 1.f;
		player->up();
		player->playAnimation("UP", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_UP", dt);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) // Down
	{
		isPressed = true;
		down = true;
		vector.y -= 1.f;
		player->down();
		player->playAnimation("DOWN", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_DOWN", dt);
		}
	}

	checkMapItemCollision(dt);
	player->move(dt, vector.x, vector.y, map->getBoundary());
	setCameraPos(player->getPosition());
	//cameraMovement(dt, vector.x, vector.y);

	if (left && up && !down && !right) // Up Left
	{
		player->playAnimation("UP_LEFT", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_UP_LEFT", dt);
		}
	}

	if (left && down && !right && !up) // Down Left
	{
		player->playAnimation("DOWN_LEFT", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_DOWN_LEFT", dt);
		}
	}

	if (right && up && !down && !left) // Up Right
	{
		player->playAnimation("UP_RIGHT", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_UP_RIGHT", dt);
		}
	}

	if (right && down && !up && !left) // Down Right
	{
		player->playAnimation("DOWN_RIGHT", dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->playAnimation("ATTACK_DOWN_RIGHT", dt);
		}
	}

	if (isPressed)
	{
		if (!up && !down)
		{
			player->resetYVector();
		}

		if (!left && !right)
		{
			player->resetXVector();
		}
	}

	if (player->getVectorDir().y > 0.f && player->getVectorDir().x == 0.f) //Idle Upward
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) 
		{
			player->playAnimation("IDLE_UP", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_UP", dt);
			}
		}
	}

	if (player->getVectorDir().y < 0.f && player->getVectorDir().x == 0.f) //Idle Downward
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_DOWN", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_DOWN", dt);
			}
		}
	}

	if (player->getVectorDir().y == 0.f && player->getVectorDir().x < 0.f) //Idle Left
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_LEFT", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_LEFT", dt);
			}
		}
	}

	if (player->getVectorDir().y == 0.f && player->getVectorDir().x > 0.f) //Idle Right
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_RIGHT", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_RIGHT", dt);
			}
		}
	}

	if (player->getVectorDir().y > 0.f && player->getVectorDir().x < 0.f) //Idle Up Left
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_UP_LEFT", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_UP_LEFT", dt);
			}
		}
	}

	if (player->getVectorDir().y > 0.f && player->getVectorDir().x > 0.f) //Idle Up Right
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_UP_RIGHT", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_UP_RIGHT", dt);
			}
		}
	}

	if (player->getVectorDir().y < 0.f && player->getVectorDir().x < 0.f) //Idle Down Left
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_DOWN_LEFT", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_DOWN_LEFT", dt);
			}
		}
	}

	if (player->getVectorDir().y < 0.f && player->getVectorDir().x > 0.f) //Idle Down Right
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playAnimation("IDLE_DOWN_RIGHT", dt);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				player->playAnimation("ATTACK_DOWN_RIGHT", dt);
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
	{
		endState();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		player->attack(dt);
	}
}

void GameState::update(const float &dt)
{
	updateMousePositions();
	updateInput(dt);
	enemyUpdate(dt);
	checkCollision(dt);

	player->update(dt);
	ui->update(player);
	map->update(dt);
	weatherUpdate(dt);
}

void GameState::checkMapItemCollision(const float& dt)
{
	for (auto item : mapItems)
	{
		if (item != nullptr)
		{
			if (item->getInteractable())
			{
				if (item->hitBox.getGlobalBounds().intersects(player->getHitbox().getGlobalBounds()))
				{
					if (abs(item->hitBox.getGlobalBounds().left - (player->getHitbox().getGlobalBounds().left + player->getHitbox().getGlobalBounds().width)) < 20)
					{
						player->stop(1, 0);
					}
					else if (abs(item->hitBox.getGlobalBounds().left + item->hitBox.getGlobalBounds().width - player->getHitbox().getGlobalBounds().left < 20))
					{
						player->stop(-1, 0);
					}
					else if (abs(item->hitBox.getGlobalBounds().top - (player->getHitbox().getGlobalBounds().top + player->getHitbox().getGlobalBounds().height)) < 20)
					{
						player->stop(0, -1);
					}
					else if (abs(item->hitBox.getGlobalBounds().top + item->hitBox.getGlobalBounds().height - player->getHitbox().getGlobalBounds().top < 20))
					{
						player->stop(0, 1);
					}
				}
				else
				{
					player->resetDir();
				}
			}
		}
	}
}

void GameState::checkCollision(const float &dt)
{
	//Check player primary attack
	if (player->getAttackFinished())
	{
		if (player->getAttack())
		{
			for (int i = 0; i < enemies.size(); i++)
			{
				if (player->getHitbox().getGlobalBounds().intersects(enemies.at(i)->getHitbox().getGlobalBounds()))
				{
					enemies.at(i)->decreaseHealth();
					if (enemies.at(i)->getHealth() < 1)
					{
						delete enemies.at(i);
						enemies.erase(enemies.begin() + i);
						player->increaseHP(2);
						break;
					}
				}
			}
		}
	}

	//Check Mage Bullet
	int damageDone = 0;
	for (auto item : enemies)
	{
		if (item != nullptr)
		{
			damageDone += item->checkBulletDamge(player->getHitbox());
		}
	}

	player->decreaseHP(damageDone);
	
	if (player->getHP() <= 0 && !player->isInvicible())
	{
		endState();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	//Set View
	target->setView(view);

	//Map
	map->render(target, player->getPosition());

	//Player
	player->render(target);

	//Enemies
	for (auto* item : enemies)
	{
		item->render(target);
	}

	//Map Items
	map->renderItems(target, player->getPosition());

	//Bgm
	if (!this->playBgm)
	{
		bgm.at("Grass")->setVolume(20);
		bgm.at("Grass")->setLoop(true);
		bgm.at("Grass")->play();
		playBgm = true;
	}

	//Weather
	for (auto item : weather)
	{
		if (item != nullptr)
		{
			item->render(target, player->getPosition());
		}
	}

	//Reset view
	target->setView(target->getDefaultView());

	//UI
	ui->render(target);

	sf::Text hp;
	hp.setFont(font);
	hp.setFillColor(sf::Color::Red);
	std::stringstream info;
	info << player->getHP() << "/" << player->getMaxHP();
	hp.setString(info.str());
	hp.setPosition(sf::Vector2f(283, 10));
	target->draw(hp);

}
