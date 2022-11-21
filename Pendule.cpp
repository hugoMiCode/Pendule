#include "DoublePendulum.h"
#include "Option.h"
#include "Graphique.h"

int main()
{
    Ressources::load();
    sf::Vector2f sizeWindow(1980, 1080);
    sf::Vector2f sizeGraphique(320, 160);
    sf::Vector2f offsetWindow(20, 20);
    sf::RenderWindow window(sf::VideoMode(sizeWindow.x, sizeWindow.y), "Pendule", sf::Style::Fullscreen);
    sf::View view(sf::Vector2f(), sizeWindow);
    std::vector<DoublePendulum*> pendules;
    Option option(-sizeWindow / 2.f + offsetWindow, sf::Vector2f(400, 800));
    Graphique graphique(sf::Vector2f(sizeWindow.x / 2.f - sizeGraphique.x - offsetWindow.x, -sizeWindow.y / 2.f + offsetWindow.y), sizeGraphique);

    window.setView(view);

    option.setFillColor(sf::Color(168, 168, 168));
    option.setOutlineThickness(4);
    option.setOutlineColor(sf::Color(100, 100, 100));

    graphique.setFillColor(sf::Color(200, 200, 200));
    graphique.setOutlineThickness(4);
    graphique.setOutlineColor(sf::Color(100, 100, 100));


    for (unsigned int i{ 0 }; i < 1; i++) {
        pendules.push_back(new DoublePendulum(3.1415926535 / 2.f, 0.00000000000001 * i + 3.1415926535 / 2.f));
        if (i < 256) {
            pendules[pendules.size() - 1]->setFillColor(sf::Color(255, 0, i));
        }
        else if (i < 2 * 256) {
            pendules[pendules.size() - 1]->setFillColor(sf::Color(2 * 256 - i, 0, 255));
        }
        else if (i < 3 * 256) {
            pendules[pendules.size() - 1]->setFillColor(sf::Color(0, i - 2 * 256, 255));
        }
        else if (i < 4 * 256) {
            pendules[pendules.size() - 1]->setFillColor(sf::Color(0, 255, 4 * 256 - i ));
        }
        else if (i < 5 * 256) {
            pendules[pendules.size() - 1]->setFillColor(sf::Color(i - 4 * 256, 255, 0));
        }
        else if (i < 6 * 256) {
            pendules[pendules.size() - 1]->setFillColor(sf::Color(255, 5 * 256 - i, 0));
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    for (unsigned int i{ 0 }; i < pendules.size(); i++) {
                        pendules[i]->changePlay();
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (option.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    option.mousePressed(event.key.code, &window);
                else
                    for (unsigned int i{ 0 }; i < pendules.size(); i++) {
                        pendules[i]->mouseButtonPressed(event.key.code, &window);
                    }
            }
            if (event.type == sf::Event::MouseMoved) {
                option.mouseMoved(&window);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                option.mouseReleased(event.key.code, &window);
                for (unsigned int i{ 0 }; i < pendules.size(); i++) {
                    pendules[i]->mouseButtonReleased(event.key.code, &window);
                }
            }
        }

        option.loop(&window);
        graphique.loop();

        for (DoublePendulum* pendule : pendules) {
            pendule->loop();
            pendule->setM2(option.getValSliderM2());
            pendule->setM1(option.getValSliderM1());
            pendule->setR1(option.getValSliderR1());
            pendule->setR2(option.getValSliderR2());
            pendule->setFrottement(option.getValSliderFrottement());
            pendule->setGravitation(option.getValSliderGravitation());
        }

        if (option.resetButtonIsPressed()) {
            for (DoublePendulum* pendule : pendules) {
                pendule->reset();
                option.reset();
            }
        }
        else if (option.playButtonIsPressed()) {
            for (DoublePendulum* pendule : pendules) {
                pendule->changePlay();
            }
        }


        window.clear(sf::Color::White);
        option.show(&window);
        graphique.show(&window);

        for (unsigned int i{ 0 }; i < pendules.size(); i++) {
            pendules[i]->show(&window);
        }

        window.display();
    }

    return 0;
}
