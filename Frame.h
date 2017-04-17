#ifndef FRAME_H
#define FRAME_H

#include <random>
#include "SFML/Graphics.hpp"

class Frame
{
private:
    sf::FloatRect m_cadre;
    static const int m_min_frame_size = 100;
    Frame *m_first_child,
          *m_second_child;
    sf::RectangleShape m_room;
    sf::RectangleShape m_dessin_cadre;
    bool isLast;
public:
    Frame(sf::FloatRect cadre);
    ~Frame();

    sf::FloatRect getCadre() const;
    void setCadre(sf::FloatRect);

    void slice();
    void define_room();
    void draw_to(sf::RenderWindow& window);
};

#endif // FRAME_H
