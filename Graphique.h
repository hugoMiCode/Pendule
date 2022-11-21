#pragma once
#include <SFML/Graphics.hpp>

class Graphique
{
public:
	Graphique(sf::Vector2f pos, sf::Vector2f size);

	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setOutlineThickness(float outlineThickness);

	void loop();
	void show(sf::RenderWindow* window);

private:
	sf::RectangleShape rectangle;
	std::vector<std::pair<float, float>> courbe;
	float tempsMax;
};

