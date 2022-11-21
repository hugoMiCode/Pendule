#pragma once
#include "Ressources.h"

class Button
{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, sf::String str);

	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setOutlineThickness(float outlineThickness);
	void setButtonText(sf::String str);

	void mousePressed(int key, sf::RenderWindow* window);
	void mouseReleased(int key, sf::RenderWindow* window);
	void mouseMoved(sf::RenderWindow* window);
	bool isPressed();

	void addVectColor(sf::Vector3f vectColor);

	void loop();
	void show(sf::RenderWindow* window);

private:
	sf::RectangleShape rectangle;
	sf::Text buttonText;
	sf::Color fillColor;
	bool pressed{ false };
	bool mouseIn{ false };
	bool mouseClisk{ false };
};

