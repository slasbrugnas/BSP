#include "Dungeon.h"

Dungeon::Dungeon(sf::FloatRect size)
    : m_size{size},
      m_root{size}
{
    generate();
}

void Dungeon::generate()
{
    slice();
}

void Dungeon::slice()
{
    m_root.slice();
}

void Dungeon::draw_to(sf::RenderWindow& window)
{
    m_root.draw_to(window);
}
