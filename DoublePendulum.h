#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

class DoublePendulum
{
public:
	DoublePendulum(float init_a1, float init_a2, float init_m1 = 100, float init_m2 = 100, float init_r1 = 180, float init_r2 = 180);

	void setFillColor(sf::Color color);
	void setM1(float newM1);
	void setM2(float newM2);
	void setR1(float newR1);
	void setR2(float newR2);
	void setFrottement(float newK);
	void setGravitation(float newG);

	float distance(sf::Vector2f pt1, sf::Vector2f pt2);
	float getAngle(sf::Vector2f pt1, sf::Vector2f pt2);
	bool getPause();

	void reset();
	void changePlay();

	void mouseButtonPressed(int key, sf::RenderWindow* window);
	void mouseButtonReleased(int key, sf::RenderWindow* window);

	void loop();
	void show(sf::RenderWindow* window);

private:
	bool pause{ true };
	bool mouseIsPressed{ false };
	sf::Vector2f posOrigine;
	int focusMasses{ 0 };

	std::pair<float, float> initAngle;
	std::pair<float, float> anglePos;
	std::pair<float, float> angleVel;
	std::pair<float, float> angleAcc;
	std::pair<float, float> masses;
	std::pair<float, float> distances;

	float k{ 1 };
	float g{ 9.81 };

	float ec;
	float ep;
	float em;

	sf::CircleShape pt0;
	sf::CircleShape pt1;
	sf::CircleShape pt2;

	sf::RectangleShape li1;
	sf::RectangleShape li2;

	sf::Clock time;
	std::deque<sf::Vector2f> path;

	sf::Color traceColor;
};

