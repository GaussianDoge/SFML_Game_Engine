#include "MainMenuState.h"

void MainMenuState::initBacground()
{
	this->background.setSize(sf::Vector2f((float) this->window->getSize().x, (float) this->window->getSize().y));
	
	if (!this->backgroundTexture.loadFromFile("Resources/Textures/Backgrounds/MainMenu.jpg"))
	{
		throw("ERROR: Fail to load background texture");
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Resources/Fonts/PTSansNarrow-Regular.ttf"))
	{
		throw("Error: Can't load fonts files");
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	buttons["GAME_STATE"] = new Button(window->getSize().x - window->getSize().x/4.f, window->getSize().y - 3 * window->getSize().y / 4.f, 200.f, 100.f, &font, "New Game", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["SETTINGS"] = new Button(window->getSize().x - window->getSize().x / 4.f, window->getSize().y - 2* window->getSize().y / 4.f, 200.f, 100.f, &font, "Settings", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttons["EXIT_STATE"] = new Button(window->getSize().x - window->getSize().x / 4.f, window->getSize().y - window->getSize().y / 4.f, 200.f, 100.f, &font, "Quit", sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void MainMenuState::initBgm()
{
	bgm = new sf::Music();
	bgm->openFromFile("Resources/Music/MainMenu.flac");
	bgm->setLoop(true);
	bgm->setVolume(50.f);
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	playBgm = false;
	initBacground();
	initFonts();
	initKeybinds();
	initButtons();
	initBgm();

	background.setSize(sf::Vector2f((float) window->getSize().x, (float) window->getSize().y));
	background.setFillColor(sf::Color::White);
}

MainMenuState::~MainMenuState()
{
	for (auto i = buttons.begin(); i != buttons.end(); i++)
	{
		delete i->second;
	}

	delete bgm;
}



void MainMenuState::endBgm()
{
	bgm->stop();
}

void MainMenuState::endState()
{
	quit = true;
}


void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	for (auto& item : buttons)
	{
		item.second->update(mousePosView);
	}
	
	if (buttons["GAME_STATE"]->isPressed())
	{
		playBgm = false;
		endBgm();
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}

	if (buttons["SETTINGS"]->isPressed())
	{
		
	}
}

void MainMenuState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& item : buttons)
	{
		item.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	target->draw(background);
	renderButtons(target);

	if (!playBgm)
	{
		bgm->play();
		playBgm = true;
	}


	//Debug

	sf::Text pos;
	pos.setFont(font);
	pos.setCharacterSize(20);
	pos.setFillColor(sf::Color::Black);
	std::stringstream info;
	info << mousePosView.x << " " << mousePosView.y;
	pos.setString(info.str());
	pos.setPosition(mousePosView.x - pos.getGlobalBounds().width, mousePosView.y);
	target->draw(pos);
}
