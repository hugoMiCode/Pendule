#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, sf::String str)
{
	rectangle.setPosition(pos);
	rectangle.setSize(size);

	buttonText.setFont(Ressources::font_JAi_____);
	buttonText.setString(str);
	buttonText.setCharacterSize(30);
	buttonText.setOrigin(buttonText.getGlobalBounds().width / 2.f, 12 + buttonText.getGlobalBounds().height / 2.f);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(pos + size / 2.f);
}

void Button::setFillColor(sf::Color color)
{
	rectangle.setFillColor(color);
	fillColor = color;
}

void Button::setOutlineColor(sf::Color color)
{
	rectangle.setOutlineColor(color);
}

void Button::setPosition(sf::Vector2f pos)
{
	rectangle.setPosition(pos);
}

void Button::setOutlineThickness(float outlineThickness)
{
	rectangle.setOutlineThickness(outlineThickness);
}

void Button::setButtonText(sf::String str)
{
	buttonText.setString(str);
}

void Button::mousePressed(int key, sf::RenderWindow* window)
{
	if (rectangle.getGlobalBounds().contains(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))))
		mouseClisk = true;
	else {
		pressed = false;
		mouseClisk = false;
		mouseIn = false;
	}
}

void Button::mouseReleased(int key, sf::RenderWindow* window)
{
	if (rectangle.getGlobalBounds().contains(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))) {
		pressed = true;
	}
	else {
		pressed = false;
	}

	mouseClisk = false;
}

void Button::mouseMoved(sf::RenderWindow* window)
{
	if (rectangle.getGlobalBounds().contains(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))))
		mouseIn = true;
	else {
		mouseIn = false;
		pressed = false;
		mouseClisk = false;
	}
}

bool Button::isPressed()
{
	if (pressed) {
		pressed = false;
		return true;
	}

	return false;
}

void Button::addVectColor(sf::Vector3f vectColor)
{
	sf::Vector3f rvb{ };
	rvb.x = fillColor.r;
	rvb.y = fillColor.g;
	rvb.z = fillColor.b;

	rvb -= vectColor;

	if (rvb.x < 0)
		rvb.x = 0;
	if (rvb.y < 0)
		rvb.y = 0;
	if (rvb.z < 0)
		rvb.z = 0;

	rectangle.setFillColor(sf::Color(rvb.x, rvb.y, rvb.z));
}

void Button::loop()
{
}

void Button::show(sf::RenderWindow* window)
{
	if (mouseClisk) {
		addVectColor(sf::Vector3f(80, 80, 80));
	}
	else if (mouseIn) {
		addVectColor(sf::Vector3f(40, 40, 40));
	}
	else
		rectangle.setFillColor(fillColor);

	window->draw(rectangle);
	window->draw(buttonText);
}