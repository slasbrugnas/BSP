#include "Leaf.h"

Leaf::Leaf()
{
    m_cadre.top = 0;
    m_cadre.left = 0;
    m_cadre.height = 0;
    m_cadre.width = 0;
}

Leaf::Leaf(sf::FloatRect cadre)
    : m_cadre{cadre}
{
    m_room.setSize(sf::Vector2f(0.0f,0.0f));
    createRooms();
}

Leaf Leaf::get_left_child() const
{
    return *m_left_child;
}

Leaf Leaf::get_right_child() const
{
    return *m_right_child;
}

void Leaf::set_cadre(sf::FloatRect cadre)
{
    m_cadre = cadre;
}

void Leaf::createRooms()
{
    sf::Color fadeWhite = sf::Color(235,235,235);
    sf::RectangleShape line;
    line.setFillColor(fadeWhite);

    if(m_cadre.height/2 < MIN_SIZE || m_cadre.width/2 < MIN_SIZE)
    {
        m_room.setSize(sf::Vector2f(rand()%static_cast<int>(m_cadre.width-MIN_SIZE+1)+MIN_SIZE,
                                    rand()%static_cast<int>(m_cadre.height-MIN_SIZE+1)+MIN_SIZE));
        m_room.setPosition(sf::Vector2f(
                               m_cadre.left+ (rand()%static_cast<int>(m_cadre.width - m_room.getSize().x) ),
                               m_cadre.top + (rand()%static_cast<int>(m_cadre.height- m_room.getSize().y) )));
        m_room.setFillColor(fadeWhite);
    }
    else
    {
        if(m_room.getSize().x == 0.0f)
        {
            // Chambre déjà créé
        }
        else
        {
            if(m_cadre.width > m_cadre.height)
            {
                sf::FloatRect c1, c2;
                c1.top = m_cadre.top;
                c1.height = m_cadre.height;
                if(rand()%2)
                {
                    c1.left = m_cadre.left;
                    c1.width = rand()%static_cast<int>(m_cadre.width-MIN_SIZE) + (m_cadre.left+(MIN_SIZE/2));
                    c2.left = m_cadre.left + c1.width;
                }
                else
                {
                    float tmp = rand()%static_cast<int>(m_cadre.width-MIN_SIZE) + (m_cadre.left+(MIN_SIZE/2));
                    c1.left = m_cadre.left - tmp;
                    c1.width = tmp;
                    c2.left = m_cadre.left;

                }
                c2.top = m_cadre.top;
                c2.height = m_cadre.height;
                c2.width = m_cadre.width - c1.width;

                m_left_child->set_cadre(c1);
                m_right_child->set_cadre(c2);

                m_left_child->createRooms();
                m_right_child->createRooms();
            }
            else
            {
                sf::FloatRect c1, c2;
                c1.left = m_cadre.left;
                c1.width = m_cadre.width;
                if(rand()%2)
                {
                    c1.top = m_cadre.top;
                    c1.height = rand()%static_cast<int>(m_cadre.height-MIN_SIZE) + (m_cadre.top+(MIN_SIZE/2));
                    c2.top = m_cadre.top + c1.height;
                }
                else
                {
                    float tmp = rand()%static_cast<int>(m_cadre.height-MIN_SIZE) + (m_cadre.top+(MIN_SIZE/2));
                    c1.top = m_cadre.top - tmp;
                    c1.height = tmp;
                    c2.top = m_cadre.top;

                }
                c2.left = m_cadre.left;
                c2.width = m_cadre.width;
                c2.height = m_cadre.height - c1.height;

                m_left_child->set_cadre(c1);
                m_right_child->set_cadre(c2);

                m_left_child->createRooms();
                m_right_child->createRooms();
            }


        }
    }
}

void Leaf::draw_to(sf::RenderWindow &window)
{
//    if(m_left_child != nullptr && m_right_child != nullptr)
//    {
        m_left_child->draw_to(window);
        m_right_child->draw_to(window);
//    }
    window.draw(m_room);
}
