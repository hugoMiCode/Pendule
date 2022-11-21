#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(float init_a1, float init_a2, float init_m1, float init_m2, float init_r1, float init_r2)
{
    initAngle = std::make_pair(init_a1, init_a2);
    anglePos = initAngle;
    masses = std::make_pair(init_m1, init_m2);
    distances = std::make_pair(init_r1, init_r2);

    pt0.setRadius(10);
    pt1.setRadius(masses.first / 10);
    pt2.setRadius(masses.second / 10);

    pt0.setOrigin(pt0.getRadius(), pt0.getRadius());
    pt1.setOrigin(pt1.getRadius(), pt1.getRadius());
    pt2.setOrigin(pt2.getRadius(), pt2.getRadius());

    pt0.setFillColor(sf::Color::Black);
    pt1.setFillColor(sf::Color::Blue);
    pt2.setFillColor(sf::Color::Blue);
    
    traceColor = sf::Color::Red;

    li1.setSize(sf::Vector2f(distances.first, 8));
    li1.setFillColor(traceColor);
    li1.setOrigin(sf::Vector2f(0, li1.getSize().y / 2.f));

    li2.setSize(sf::Vector2f(distances.second, 8));
    li2.setFillColor(traceColor);
    li2.setOrigin(sf::Vector2f(0, li2.getSize().y / 2.f));

    pt1.setPosition(sf::Vector2f(sin(anglePos.first) * distances.first, cos(anglePos.first) * distances.first));
    pt2.setPosition(sf::Vector2f(sin(anglePos.second) * distances.second, cos(anglePos.second) * distances.second) + pt1.getPosition());

}

void DoublePendulum::setFillColor(sf::Color color)
{
    traceColor = color;
    pt1.setFillColor(color);
    pt2.setFillColor(color);
    li1.setFillColor(traceColor);
    li2.setFillColor(traceColor);
}

void DoublePendulum::setM1(float newM1)
{
    masses.first = newM1;

    pt1.setRadius(masses.first / 10);
    pt1.setOrigin(pt1.getRadius(), pt1.getRadius());
}

void DoublePendulum::setM2(float newM2)
{
    masses.second = newM2;

    pt2.setRadius(masses.second / 10);
    pt2.setOrigin(pt2.getRadius(), pt2.getRadius());
}

void DoublePendulum::setR1(float newR1)
{
    distances.first = newR1;
    li1.setSize(sf::Vector2f(distances.first, 8));
    pt1.setPosition(sf::Vector2f(sin(anglePos.first) * distances.first, cos(anglePos.first) * distances.first));
}

void DoublePendulum::setR2(float newR2)
{
    distances.second = newR2;
    li2.setSize(sf::Vector2f(distances.second, 8));
    pt2.setPosition(sf::Vector2f(sin(anglePos.second) * distances.second, cos(anglePos.second) * distances.second) + pt1.getPosition());
}

void DoublePendulum::setFrottement(float newK)
{
    k = newK;
}

void DoublePendulum::setGravitation(float newG)
{
    g = newG;
}

float DoublePendulum::distance(sf::Vector2f pt1, sf::Vector2f pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

float DoublePendulum::getAngle(sf::Vector2f pt1, sf::Vector2f pt2)
{
    float dis{ distance(pt1, pt2) };
    if (dis > 0.01) {
        if (pt2.x < pt1.x)
            return acos((pt1.y - pt2.y) / dis) + 3.14;
        else
            return -acos((pt1.y - pt2.y) / dis) + 3.14;
    }
    return 0;
}

bool DoublePendulum::getPause()
{
    return pause;
}

void DoublePendulum::reset()
{
    anglePos = initAngle;
    angleVel = std::make_pair(0, 0);
    angleAcc = std::make_pair(0, 0);

    path.clear();

    pt1.setPosition(sf::Vector2f(sin(anglePos.first) * distances.first, cos(anglePos.first) * distances.first));
    pt2.setPosition(sf::Vector2f(sin(anglePos.second) * distances.second, cos(anglePos.second) * distances.second) + pt1.getPosition());
}

void DoublePendulum::changePlay()
{
    pause = !pause;
}

void DoublePendulum::mouseButtonPressed(int key, sf::RenderWindow* window)
{
    if (key == sf::Mouse::Left) {
        mouseIsPressed = true;
        sf::Vector2f posSouris{ window->mapPixelToCoords(sf::Mouse::getPosition(*window)) };


        if (distance(posSouris, pt1.getPosition()) < distance(posSouris, pt2.getPosition())) {
            posOrigine = posSouris - distances.first * sf::Vector2f(sin(anglePos.first), cos(anglePos.first));
            focusMasses = 1;
        }
        else {
            posOrigine = posSouris - distances.second * sf::Vector2f(sin(anglePos.second), cos(anglePos.second));
            focusMasses = 2;
        }
    }
}

void DoublePendulum::mouseButtonReleased(int key, sf::RenderWindow* window)
{
    if (key == sf::Mouse::Left && mouseIsPressed) {
        path.clear();
        mouseIsPressed = false;
        focusMasses = 0;
    }
}

void DoublePendulum::loop()
{
    sf::Vector2f pos1A(pt1.getPosition());
    sf::Vector2f pos2A(pt2.getPosition());

    float dt{ time.restart().asMicroseconds() / 100000.f };

    if (mouseIsPressed) {
        angleAcc = std::make_pair(0.f, 0.f);
        angleVel = std::make_pair(0.f, 0.f);
    }
    else if (!pause) {
        float m1 = masses.first;
        float m2 = masses.second;

        float a1 = anglePos.first;
        float a2 = anglePos.second;

        float a1_v = angleVel.first;
        float a2_v = angleVel.second;

        float r1 = distances.first;
        float r2 = distances.second;

        float d1{ r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2)) };
        float d2{ r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2)) };


        angleAcc.first = (-g * (2 * m1 + m2) * sin(a1) - m2 * g * sin(a1 - 2 * a2) - 2 * sin(a1 - a2) - 2 * sin(a1 - a2) * m2 * (a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2))) / d1;
        angleAcc.second = (2 * sin(a1 - a2) * (a1_v * a1_v * r1 * (m1 + m2) + g * (m1 + m2) * cos(a1) + a2_v * a2_v * r2 * m2 * cos(a1 - a2))) / d2;

        angleVel.first += angleAcc.first * dt;
        angleVel.second += angleAcc.second * dt;

        angleVel.first *= pow(k, dt);
        angleVel.second *= pow(k, dt);

        anglePos.first += angleVel.first * dt;
        anglePos.second += angleVel.second * dt;

        pt1.setPosition(sf::Vector2f(sin(anglePos.first) * distances.first, cos(anglePos.first) * distances.first));
        pt2.setPosition(sf::Vector2f(sin(anglePos.second) * distances.second, cos(anglePos.second) * distances.second) + pt1.getPosition());
        
        path.push_front(pt2.getPosition());

        if (path.size() > 1000) {
            path.pop_back();
        }
    }

    sf::Vector2f pos1B(pt1.getPosition());
    sf::Vector2f pos2B(pt2.getPosition());

    float vel1{ sqrt(pow(((pos1B - pos1A) / dt).x, 2.f) + pow(((pos1B - pos1A) / dt).y, 2.f)) };
    float vel2{ sqrt(pow(((pos2B - pos2A) / dt).x, 2.f) + pow(((pos2B - pos2A) / dt).y, 2.f)) };

    ec = 0.5f * (masses.first * pow(vel1, 2.f) + masses.second * pow(vel2, 2.f));  
    ep = -g * (masses.first * (pos1B.y - distances.first) + masses.second * (pos2B.y - distances.first - distances.second));
    em = ec + ep;

    std::cout << ec + ep << std::endl;
}

void DoublePendulum::show(sf::RenderWindow* window)
{

    if (mouseIsPressed) {
        if (focusMasses == 1) {
            float newAngle{ getAngle(posOrigine, sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) };
            anglePos.first = newAngle;
        }
        else if (focusMasses == 2) {
            float newAngle{ getAngle(posOrigine, sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) };
            anglePos.second = newAngle;
        }

        sf::CircleShape origine(4);
        origine.setOrigin(origine.getRadius(), origine.getRadius());
        origine.setFillColor(sf::Color(20, 20, 20));
        origine.setPosition(posOrigine);
        window->draw(origine);
    }

    /*
    for (unsigned int i{ 0 }; i < path.size(); i++) {
        sf::CircleShape trace(2);
        trace.setOrigin(trace.getRadius(), trace.getRadius());
        trace.setFillColor(traceColor);
        trace.setPosition(path[i]);

        window->draw(trace);
    }

    */
    sf::RectangleShape rectest1(sf::Vector2f(distances.first, 8));
    rectest1.setFillColor(traceColor);
    rectest1.setOrigin(sf::Vector2f(0, 4));


    li1.setRotation(-anglePos.first * 180 / 3.1415 + 90);

    li2.setRotation(-anglePos.second * 180 / 3.1415 + 90);
    li2.setPosition(pt1.getPosition());


    window->draw(li1);
    window->draw(li2);
    window->draw(pt0);
    window->draw(pt1);
    window->draw(pt2);
}
