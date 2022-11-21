#pragma once
#include "Slider.h"
#include "Button.h"

struct InitVal {
	float g{ 9.81 };
	float m1{ 200 };
	float m2{ 200 };
	float r1{ 180 };
	float r2{ 180 };
	float k{ 1 };
};

class Option
{
public:
	Option(sf::Vector2f pos, sf::Vector2f size);

	void reset();

	bool resetButtonIsPressed();
	bool playButtonIsPressed();

	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setOutlineThickness(float outlineThickness);

	float getValSliderM1();
	float getValSliderM2();
	float getValSliderR1();
	float getValSliderR2();
	float getValSliderFrottement();
	float getValSliderGravitation();

	sf::FloatRect getGlobalBounds();

	void mousePressed(int key, sf::RenderWindow* window);
	void mouseReleased(int key, sf::RenderWindow* window);
	void mouseMoved(sf::RenderWindow* window);

	void show(sf::RenderWindow* window);
	void loop(sf::RenderWindow* window); // dommage...

private:
	sf::RectangleShape rectangle;

	InitVal initVal;
	std::vector<Slider*> sliders;
	Slider* sliderM1;
	Slider* sliderM2;
	Slider* sliderR1;
	Slider* sliderR2;
	Slider* sliderFrottement;
	Slider* sliderGravitation;

	std::vector<Button*> buttons;
	Button* exitButton;
	Button* resetButton;
	Button* playButton;
};

