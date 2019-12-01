#ifndef DUNGEON_H
#define DUNGEON_H

#include "SFML/Graphics.hpp"
#include "Frame.h"

class Dungeon
{
private:
    sf::FloatRect m_size;
    Frame m_root;
public:
    Dungeon(sf::FloatRect size);
    void generate();
    void slice();
    void draw_to(sf::RenderWindow& window);
};

#endif // DUNGEON_H
