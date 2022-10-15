#include "Heatmap.h"

sfplot::Heatmap::Heatmap(
    // sf::RenderWindow &window,
    sf::Font font,
    unsigned textSize) : // window(window),
                         font(font),
                         textSize(textSize)
{
}

virtual void sfplot::Heatmap::draw(sf::RenderTarget &target, sf::RenderStates states)
{
}

sfplot::Heatmap::~Heatmap()
{
}