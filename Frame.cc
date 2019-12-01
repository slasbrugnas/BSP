#include "Frame.h"

int Frame::m_max_depth;

Frame::Frame(sf::FloatRect cadre, Frame *parent)
    : m_frame{cadre},
      m_parent{parent},
      isLast{false}
{
    m_first_child = nullptr;
    m_second_child = nullptr;
    m_depth = (m_parent != nullptr) ? m_parent->getDepth() + 1 : 0;
    Frame::m_max_depth = (m_depth > Frame::m_max_depth) ? m_depth : m_max_depth;
}

Frame::~Frame()
{
    delete m_first_child;
    delete m_second_child;
    delete m_parent;
}

Frame * Frame::getFirstChild() const {
    return m_first_child;
}

Frame * Frame::getSecondChild() const {
    return m_second_child;
}

sf::FloatRect Frame::getFrame() const
{
    return m_frame;
}

int Frame::getDepth() const {
    return m_depth;
}

void Frame::setDepth(int depth) {
    m_depth = depth;
}

void Frame::setCadre(sf::FloatRect cadre)
{
    m_frame = cadre;
}

void Frame::slice()
{

    if(m_frame.width <= m_min_frame_size ||
       m_frame.height <= m_min_frame_size)
    {
        isLast = true;
        define_room();
        make_path();
    }
    else
    {
        m_first_child  = new Frame(sf::FloatRect(0.0f,0.0f,
                                                 0.0f,0.0f),
                                                 this);
        m_second_child = new Frame(sf::FloatRect(0.0f,0.0f,
                                                 0.0f,0.0f),
                                                 this);
        if(m_frame.width > m_frame.height)
        {
            m_first_child->setCadre(sf::FloatRect(m_frame.left,
                                                  m_frame.top,
                                                  (rand() % static_cast<int>(0.2*m_frame.width))+(0.4*m_frame.width),
                                                  m_frame.height));

            m_second_child->setCadre(sf::FloatRect(m_frame.left+m_first_child->getFrame().width,
                                                   m_frame.top,
                                                   m_frame.width-m_first_child->getFrame().width,
                                                   m_frame.height));
        }
        else // m_frame.height > m_frame.width
        {
            m_first_child->setCadre(sf::FloatRect(m_frame.left,
                                                  m_frame.top,
                                                  m_frame.width,
                                                  (rand() % static_cast<int>(0.2*m_frame.height))+(0.4*m_frame.height)));

            m_second_child->setCadre(sf::FloatRect(m_frame.left,
                                                   m_frame.top+m_first_child->getFrame().height,
                                                   m_frame.width,
                                                   m_frame.height-m_first_child->getFrame().height));
        }
        m_first_child->slice();
        m_second_child->slice();
    }
}

// Dessine les cadres pour l'instant
void Frame::define_room()
{
    if (m_frame.width > m_frame.height) {
        m_room.setSize({(rand() % static_cast<int>(0.2 * m_frame.width) + (0.4f * m_frame.width)),
                        (rand() % static_cast<int>(0.4 * m_frame.height) + (0.4f * m_frame.height))});
    } else {
        m_room.setSize({(rand() % static_cast<int>(0.4 * m_frame.width) + (0.4f * m_frame.width)),
                        (rand() % static_cast<int>(0.2 * m_frame.height) + (0.4f * m_frame.height))});
    }
    

    float randPosX = m_frame.left + (m_frame.width - m_room.getSize().x)/2;
    float randPosY = m_frame.top  + (m_frame.height- m_room.getSize().y)/2;

    m_room.setPosition({randPosX,
                        randPosY});

    m_room.setFillColor(sf::Color(220,220,220));

    m_frame_border.setPosition({m_frame.left,m_frame.top});
    m_frame_border.setSize({m_frame.width,m_frame.height});
    m_frame_border.setOutlineThickness(1.0f);
    m_frame_border.setFillColor(sf::Color::Transparent);
    // Coloration des cadres en fonction de la largeur et de la hauteur
    // if(m_frame.height < m_frame.width)
    //     m_frame_border.setOutlineColor(sf::Color(235,20,20));
    // else
    //     m_frame_border.setOutlineColor(sf::Color(20,235,20));
    m_frame_border.setOutlineColor(sf::Color(235,235,235));
}

void Frame::make_path()
{
   if (m_parent != nullptr) {
       const Frame * sibling = m_parent->getSecondChild();
       if (sibling != nullptr && this != sibling && m_depth == Frame::m_max_depth) {
            const sf::FloatRect sibling_frame = sibling->getFrame();
            sf::Vector2f center, size;
            if (m_frame.left == sibling_frame.left)
            {
                center = { m_frame.left + m_frame.width / 2 - 25.0f,
                                        m_frame.top + m_frame.height / 2};
                size = { 50.0f,
                                        m_frame.height};
            }
            else {
                center = {m_frame.left + m_frame.width / 2 - 25.0f,
                                       m_frame.top + m_frame.height / 2};
                size = {m_frame.width,
                                     50.0f};
            }
            m_path.setPosition(center);
            m_path.setSize(size);
            m_path.setFillColor(sf::Color(220, 220, 220));
       }
   }
}

void Frame::draw_to(sf::RenderWindow& window)
{
    if(isLast)
    {
        window.draw(m_room);
        window.draw(m_frame_border);
        window.draw(m_path);
    }
    else
    {
        m_first_child->draw_to(window);
        m_second_child->draw_to(window);
    }
}
