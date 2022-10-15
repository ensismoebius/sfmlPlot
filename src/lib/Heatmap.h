#ifndef SFPLOT_HEATMAP_H
#define SFPLOT_HEATMAP_H

#pragma once

#include <SFML/Graphics.hpp>

namespace sfplot
{

    class Heatmap : public sf::Transformable, public sf::Drawable
    {
    public:
        sf::Font font;
        unsigned textSize;

        //sf::RenderWindow &window;

        Heatmap(
    //sf::RenderWindow &window,
    sf::Font font,
    unsigned textSize);
        ~Heatmap();

    private:
    };

} // namespace sfplot
#endif