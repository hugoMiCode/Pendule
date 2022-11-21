#include "Slider.h"
#include <iostream>

Slider::Slider(sf::Vector2f pos, sf::Vector2f size, std::pair<float, float> range)
{
	init(pos, size, range);

	val = rangeVal.first + abs(rangeVal.first - rangeVal.second) / 2.f;
}

Slider::Slider(sf::Vector2f pos, sf::Vector2f size, std::pair<float, float> range, float initVal)
{
	init(pos, size, range);

	val = initVal;
}

void Slider::init(sf::Vector2f pos, sf::Vector2f size, std::pair<float, float> range)
{
	rangeVal = range;

	slide.setPosition(pos);
	slide.setSize(size);
	
	contentSlide.setPosition(pos);
}

void Slider::setContentColor(sf::Color color)
{
	contentSlide.setFillColor(color);
}

void Slider::setFillColor(sf::Color color)
{
	slide.setFillColor(color);
}

void Slider::setOutlineColor(sf::Color color)
{
	slide.setOutlineColor(color);
}

void Slider::setPosition(sf::Vector2f pos)
{
	slide.setPosition(pos);
	contentSlide.setPosition(pos);
}

void Slider::setOutlineThickness(float outlineThickness)
{
	slide.setOutlineThickness(outlineThickness);
}

void Slider::setRangeVal(std::pair<float, float> newRangeVal)
{
	rangeVal = newRangeVal;
}

void Slider::setVal(float newVal)
{
	val = newVal;
}

float Slider::getVal()
{
	return val;
}

sf::FloatRect Slider::getGlobalBounds()
{
	return slide.getGlobalBounds();
}

void Slider::mouseButtonPressed(sf::RenderWindow* window)
{
	float x{ (window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x - slide.getPosition().x) / slide.getSize().x };
	val = x * abs(rangeVal.first - rangeVal.second) + rangeVal.first;
}

void Slider::show(sf::RenderWindow* window)
{
	window->draw(slide);
	window->draw(contentSlide);
}

void Slider::loop()
{
	if (val > rangeVal.second)
		val = rangeVal.second;
	else if (val < rangeVal.first)
		val = rangeVal.first;

	float x{ (val - rangeVal.first) / abs(rangeVal.first - rangeVal.second) };
	contentSlide.setSize(sf::Vector2f(x * slide.getSize().x, slide.getSize().y));
}
