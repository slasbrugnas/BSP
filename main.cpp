#include <iostream>
#include <ctime>
#include <random>
#include <SFML/Graphics.hpp>
#include "Leaf.h"

const int W = 600;
const int H = 600;

using namespace std;

int main()
{
    srand(time(NULL));

    sf::Color fadeBlack = sf::Color(20,20,20);

    sf::RenderWindow window(sf::VideoMode(W,H), "BSP");
    sf::Event event;

    sf::FloatRect ecran;
    ecran.top = 0;
    ecran.left = 0;
    ecran.height = H;
    ecran.width = W;
    Leaf dungeon(ecran);

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case event.Closed:
                window.close();
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                default:
                    break;
                }

            default:
                break;
            }

            window.clear(fadeBlack);
            dungeon.draw_to(window);
            window.display();
        }
    }
    return 0;
}

