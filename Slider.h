#pragma once
#include <SFML\Graphics.hpp>

class Slider
{
public:
	Slider(sf::Vector2f pos, sf::Vector2f size, std::pair<float, float> range);
	Slider(sf::Vector2f pos, sf::Vector2f size, std::pair<float, float> range, float initVal);

	void init(sf::Vector2f pos, sf::Vector2f size, std::pair<float, float> range);

	void setContentColor(sf::Color color);
	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setOutlineThickness(float outlineThickness);
	void setRangeVal(std::pair<float, float> newRangeVal);
	void setVal(float newVal);

	float getVal();
	sf::FloatRect getGlobalBounds();

	void mouseButtonPressed(sf::RenderWindow* window);
	void show(sf::RenderWindow* window);
	void loop();

private:
	sf::RectangleShape slide;
	sf::RectangleShape contentSlide;

	std::pair<float, float> rangeVal;

	float val; 
};

