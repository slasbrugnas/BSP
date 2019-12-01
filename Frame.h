#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"

class Frame
{
private:
    sf::FloatRect m_frame;
    static const int m_min_frame_size = 300;
    static int m_max_depth;

    Frame *m_parent,
          *m_first_child,
          *m_second_child;
    
    sf::RectangleShape m_frame_border;
    sf::RectangleShape m_path;
    sf::RectangleShape m_room;

    int m_depth;

    bool isLast;
public:
    Frame(sf::FloatRect cadre, Frame *parent = nullptr);
    ~Frame();

    sf::FloatRect getFrame() const;
    void setCadre(sf::FloatRect);
    Frame * getFirstChild() const;
    Frame * getSecondChild() const;
    int getDepth() const;
    void setDepth(int depth);

    void slice();
    void define_room();
    void make_path();
    void draw_to(sf::RenderWindow& window);
};

#endif // FRAME_H
