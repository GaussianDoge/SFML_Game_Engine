#include "Game.h"

Game::Game()
{
	initWindow();
	initKeys();
	initState();
}

Game::~Game()
{
	delete this->window;
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

void Game::initWindow()
{
	std::ifstream file("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "Unknown";
	sf::VideoMode size = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	unsigned int framerate = 60;
	bool verticalSyncEnable = false;
	unsigned antialiasing_level = 0;

	if (file.is_open())
	{
		std::getline(file, title);
		file >> size.width >> size.height;
		file >> fullscreen;
		file >> framerate;
		file >> verticalSyncEnable;
		file >> antialiasing_level;
	}
	file.close();

	windowSettings.antialiasingLevel = antialiasing_level;
	if (fullscreen)
	{
		this->window = new sf::RenderWindow(size, title, sf::Style::Fullscreen, windowSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(size, title, sf::Style::Titlebar|sf::Style::Close, windowSettings);
	}
	window->setFramerateLimit(framerate);
	window->setVerticalSyncEnabled(verticalSyncEnable);
}

void Game::initKeys()
{
	std::ifstream keys("Config/supportedKeys.ini");
	if (keys)
	{
		std::string key;
		int keyValue;
		while (keys >> key >> keyValue)
		{
			supportedKeys[key] = keyValue;
		}
	}
	keys.close();
}

void Game::initState()
{
	states.push(new MainMenuState(window, &supportedKeys, &this->states));
}

void Game::endApplication()
{
}

void Game::updateSFMLEvent()
{
	while (window->pollEvent(this->event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update()
{
	updateSFMLEvent();
	if (!this->states.empty())
	{
		states.top()->update(this->dt);

		if (states.top()->getQuit())
		{
			states.top()->endState();
			delete this->states.top();
			states.pop();
		}
	}
	else
	{
		endApplication();
		window->close();
	}
}

void Game::render()
{
	window->clear();

	if (!states.empty())
	{
		states.top()->render(this->window);
	}

	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

void Game::updateDt()
{
	/*Time elapsed to render one frame*/
	dt = dtClock.restart().asSeconds();
}

float Game::getDt()
{
	return dt;
}
