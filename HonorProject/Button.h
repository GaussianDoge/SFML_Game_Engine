#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum BUTTON_STATES{IDLE = 0, PRESSED, HOVER};

class Button
{
private:
	unsigned short buttonState;
	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idelColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, 
		sf::Color idelColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	const bool isPressed() const;
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};
#endif

