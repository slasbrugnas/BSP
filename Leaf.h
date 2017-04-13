#ifndef LEAF_H
#define LEAF_H

#include <SFML/Graphics.hpp>

class Leaf
{
private:
    static const int MIN_SIZE = 8;
    Leaf *m_left_child,
         *m_right_child;
    sf::FloatRect m_cadre;
    sf::RectangleShape m_room;
public:
    Leaf();
    Leaf(sf::FloatRect);
    Leaf get_left_child() const;
    Leaf get_right_child() const;
    void createRooms();
    void set_cadre(sf::FloatRect cadre);
    void draw_to(sf::RenderWindow& window);
};

#endif // LEAF_H
