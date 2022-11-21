#include "Option.h"
#include <iostream>
Option::Option(sf::Vector2f pos, sf::Vector2f size)
{
	rectangle.setPosition(pos);
	rectangle.setSize(size);

	sf::Vector2f sizeSlider(300, 40);
	sf::Vector2f sizeButton(170, 45);
	sf::Vector2f offsetButton(20, 20);

	sliderM1 = new Slider(pos + sf::Vector2f(50, 50), sizeSlider, std::make_pair(10, 800), initVal.m1);
	sliderM2 = new Slider(pos + sf::Vector2f(50, 100), sizeSlider, std::make_pair(10, 800), initVal.m2);
	sliderR1 = new Slider(pos + sf::Vector2f(50, 180), sizeSlider, std::make_pair(20, 300), initVal.r1);
	sliderR2 = new Slider(pos + sf::Vector2f(50, 230), sizeSlider, std::make_pair(20, 300), initVal.r2);
	sliderFrottement = new Slider(pos + sf::Vector2f(50, 310), sizeSlider, std::make_pair(0.9, 1), initVal.k);
	sliderGravitation = new Slider(pos + sf::Vector2f(50, 360), sizeSlider, std::make_pair(0, 20), initVal.g);

	sliders.push_back(sliderM1);
	sliders.push_back(sliderM2);
	sliders.push_back(sliderR1);
	sliders.push_back(sliderR2);
	sliders.push_back(sliderFrottement);
	sliders.push_back(sliderGravitation);

	for (Slider* slide : sliders) {
		slide->setOutlineThickness(4);
		slide->setOutlineColor(sf::Color(100, 100, 100));
		slide->setContentColor(sf::Color::Blue);
		slide->setFillColor(sf::Color::White);
	}

	exitButton = new Button(pos + size - sizeButton - offsetButton, sizeButton, "EXIT");
	resetButton = new Button(pos + sf::Vector2f(offsetButton.x, size.y - sizeButton.y - offsetButton.y), sizeButton, "RESET");
	playButton = new Button(pos + sf::Vector2f(offsetButton.x, size.y - 2 * sizeButton.y - 2 * offsetButton.y), sizeButton, "PLAY/PAUSE");

	buttons.push_back(exitButton);
	buttons.push_back(resetButton);
	buttons.push_back(playButton);

	exitButton->setFillColor(sf::Color(255, 100, 100));
	exitButton->setOutlineColor(sf::Color(100, 40, 0));
	exitButton->setOutlineThickness(2);

	resetButton->setFillColor(sf::Color(168, 168, 168));
	resetButton->setOutlineColor(sf::Color(100, 100, 100));
	resetButton->setOutlineThickness(2);

	playButton->setFillColor(sf::Color(168, 168, 168));
	playButton->setOutlineColor(sf::Color(100, 100, 100));
	playButton->setOutlineThickness(2);
}

void Option::reset()
{
	sliderFrottement->setVal(initVal.k);
	sliderGravitation->setVal(initVal.g);
	sliderM1->setVal(initVal.m1);
	sliderM2->setVal(initVal.m2);
	sliderR1->setVal(initVal.r1);
	sliderR2->setVal(initVal.r2);
}

bool Option::resetButtonIsPressed()
{
	return resetButton->isPressed();
}

bool Option::playButtonIsPressed()
{
	return playButton->isPressed();
}

void Option::setFillColor(sf::Color color)
{
	rectangle.setFillColor(color);
}

void Option::setOutlineColor(sf::Color color)
{
	rectangle.setOutlineColor(color);
}

void Option::setPosition(sf::Vector2f pos)
{
	rectangle.setPosition(pos);
}

void Option::setOutlineThickness(float outlineThickness)
{
	rectangle.setOutlineThickness(outlineThickness);
}

float Option::getValSliderM1()
{
	return sliderM1->getVal();
}

float Option::getValSliderM2()
{
	return sliderM2->getVal();
}

float Option::getValSliderR1()
{
	return sliderR1->getVal();
}

float Option::getValSliderR2()
{
	return sliderR2->getVal();
}

float Option::getValSliderFrottement()
{
	return sliderFrottement->getVal();
}

float Option::getValSliderGravitation()
{
	return sliderGravitation->getVal();
}

sf::FloatRect Option::getGlobalBounds()
{
	return rectangle.getGlobalBounds();
}

void Option::mousePressed(int key, sf::RenderWindow* window)
{
	for (Button* button : buttons) {
		button->mousePressed(key, window);
	}
}

void Option::mouseReleased(int key, sf::RenderWindow* window)
{
	for (Button* button : buttons) {
		button->mouseReleased(key, window);
	}
}

void Option::mouseMoved(sf::RenderWindow* window)
{
	for (Button* button : buttons) {
		button->mouseMoved(window);
	}
}

void Option::show(sf::RenderWindow* window)
{
	window->draw(rectangle);
	for (Slider* slide : sliders)
		slide->show(window);

	for (Button* button : buttons) {
		button->show(window);
	}
}

void Option::loop(sf::RenderWindow* window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (Slider* slide : sliders) {
			if (slide->getGlobalBounds().contains(sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))) {
				slide->mouseButtonPressed(window);
			}
		}
	}

	for (Slider* slide : sliders)
		slide->loop();

	if (exitButton->isPressed()) {
		window->close();
	}
}
