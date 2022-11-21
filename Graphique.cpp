#include "Graphique.h"

Graphique::Graphique(sf::Vector2f pos, sf::Vector2f size)
{
	rectangle.setPosition(pos);
	rectangle.setSize(size);

	tempsMax = 30; // en seconds
}

void Graphique::setFillColor(sf::Color color)
{
	rectangle.setFillColor(color);
}

void Graphique::setOutlineColor(sf::Color color)
{
	rectangle.setOutlineColor(color);
}

void Graphique::setPosition(sf::Vector2f pos)
{
	rectangle.setPosition(pos);
}

void Graphique::setOutlineThickness(float outlineThickness)
{
	rectangle.setOutlineThickness(outlineThickness);
}

void Graphique::loop()
{
}

void Graphique::show(sf::RenderWindow* window)
{
	window->draw(rectangle);
}
