#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"

const int W = 768;
const int H = 768;

using namespace std;

void change_seed(sf::Event d, unsigned int & seed)
{
    switch(d.key.code)
    {
        case sf::Keyboard::Up:
            seed += 65536;
            break;
        case sf::Keyboard::Down:
            seed -= 65536;
            break;
        case sf::Keyboard::Left:
            seed--;
            break;
        case sf::Keyboard::Right:
            seed++;
            break;
        default:;
            break;
    }
}

int main()
{
    unsigned int seed;
    srand(time(NULL));
    cout << "Choix du seed" << endl;
    cout << "1. Aléatoire" << endl;
    cout << "2. Manuel" << endl;
    cout << "3. Quitter" << endl;
    int choix;
    do
    {
        cout << "choix ?" << endl;
        cin >> choix;
        switch(choix)
        {
        case 1:
            seed = rand();
            break;
        case 2:
            cout << "seed ?" << endl;
            cin >> seed;
            break;
        case 3:
            return EXIT_SUCCESS;
        default:
            cout << "Choix incorrect" << endl;
            break;
        }
    }while(choix != 1 && choix != 2 && choix != 3);

    srand(seed);

    sf::Color fadeBlack = sf::Color(20,20,20);

    sf::RenderWindow window(sf::VideoMode(W,H), "BSP");
    sf::Event event;

    Dungeon dungeon(sf::FloatRect(10,10,W-20,H-20));

    bool seedChanged = false;
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
                case sf::Keyboard::J:
                    cout << "jump to seed ?" << endl;
                    cin >> seed;
                    seedChanged = true;
                    break;
                case sf::Keyboard::Up:
                case sf::Keyboard::Down:
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    change_seed(event,seed);
                    seedChanged = true;
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                default:
                    break;
                }

            default:
                break;
            }
            srand(seed);
            if(seedChanged)
            {

                cout << "seed : 0x" << std::hex << seed << endl;
                dungeon = *new Dungeon(sf::FloatRect(10,10,W-20,H-20));
                seedChanged = false;
            }

            window.clear(fadeBlack);
            dungeon.draw_to(window);
            window.display();
        }
    }
    return EXIT_SUCCESS;
}
