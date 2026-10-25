#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,
	sf::Color idelColor, sf::Color hoverColor, sf::Color activeColor)
{
	buttonState = IDLE;
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	this->font = font;
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(30);
	this->text.setPosition(shape.getPosition().x + shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		shape.getPosition().y + shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f);

	this->idelColor = idelColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	shape.setFillColor(this->idelColor);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (buttonState == PRESSED)
	{
		return true;
	}
	return false;
}

void Button::update(const sf::Vector2f mousePos)
{
	buttonState = IDLE;
	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonState = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = PRESSED;
		}
	}

	switch (buttonState)
	{
	case IDLE:
		shape.setFillColor(idelColor);
		break;
	case HOVER:
		shape.setFillColor(hoverColor);
		break;
	case PRESSED:
		shape.setFillColor(activeColor);
	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}
