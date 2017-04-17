#include "Frame.h"

Frame::Frame(sf::FloatRect cadre)
    : m_cadre{cadre},
      isLast{false}
{

}

Frame::~Frame()
{
    /*while(isLast != true)
    {
        delete m_first_child;
        delete m_second_child;
    }*/
}

sf::FloatRect Frame::getCadre() const
{
    return m_cadre;
}

void Frame::setCadre(sf::FloatRect cadre)
{
    m_cadre = cadre;
}

void Frame::slice()
{

    if(m_cadre.width <= m_min_frame_size ||
            m_cadre.height <= m_min_frame_size)
    {
        isLast = true;
        define_room();
    }
    else
    {
        m_first_child  = new Frame(sf::FloatRect(0.0f,0.0f,
                                                 0.0f,0.0f));
        m_second_child = new Frame(sf::FloatRect(0.0f,0.0f,
                                                 0.0f,0.0f));
        if(m_cadre.width > m_cadre.height)
        {
            m_first_child->setCadre(sf::FloatRect(m_cadre.left,
                                                  m_cadre.top,
                                                  (rand() % static_cast<int>(0.2*m_cadre.width))+(0.4*m_cadre.width),
                                                  m_cadre.height));

            m_second_child->setCadre(sf::FloatRect(m_cadre.left+m_first_child->getCadre().width,
                                                   m_cadre.top,
                                                   m_cadre.width-m_first_child->getCadre().width,
                                                   m_cadre.height));
        }
        else // m_cadre.height > m_cadre.width
        {
            m_first_child->setCadre(sf::FloatRect(m_cadre.left,
                                                  m_cadre.top,
                                                  m_cadre.width,
                                                  (rand() % static_cast<int>(0.2*m_cadre.height))+(0.4*m_cadre.height)));

            m_second_child->setCadre(sf::FloatRect(m_cadre.left,
                                                   m_cadre.top+m_first_child->getCadre().height,
                                                   m_cadre.width,
                                                   m_cadre.height-m_first_child->getCadre().height));
        }
        m_first_child->slice();
        m_second_child->slice();
    }
}

// Dessine les cadres pour l'instant
void Frame::define_room()
{
    float randPosX,randPosY;
    //if(static_cast<int>(0.15*m_cadre.left) == 0)
        randPosX = m_cadre.left;
    /*else
        randPosX = (rand() % static_cast<int>(0.15*m_cadre.left))+(m_cadre.left);*/
    //if(static_cast<int>(0.15*m_cadre.top) == 0)
        randPosY = m_cadre.top;
    /*else
        randPosY = (rand() % static_cast<int>(0.15*m_cadre.top))+(m_cadre.top);*/
    m_room.setPosition({randPosX,
                        randPosY});
    m_room.setSize({(rand() % static_cast<int>(0.5*m_cadre.width)) + (0.5*m_cadre.width),
                    (rand() % static_cast<int>(0.5*m_cadre.height)) + (0.5*m_cadre.height)});
    m_room.setFillColor(sf::Color(235,235,235,122));

    m_dessin_cadre.setPosition({m_cadre.left,m_cadre.top});
    m_dessin_cadre.setSize({m_cadre.width,m_cadre.height});
    m_dessin_cadre.setOutlineThickness(1.0f);
    m_dessin_cadre.setFillColor(sf::Color::Transparent);
    if(m_cadre.height == m_cadre.width)
        m_dessin_cadre.setOutlineColor(sf::Color(235,20,20));
    else
        m_dessin_cadre.setOutlineColor(sf::Color(235,235,235));
}

void Frame::draw_to(sf::RenderWindow& window)
{
    if(isLast)
    {
        //window.draw(m_room);
        window.draw(m_dessin_cadre);
    }
    else
    {
        m_first_child->draw_to(window);
        m_second_child->draw_to(window);
    }
}
