#ifndef SFPLOT_HEATMAP_H
#define SFPLOT_HEATMAP_H

#pragma once

#include <SFML/Graphics.hpp>

namespace sfplot
{
    class Heatmap : public sf::Transformable, public sf::Drawable
    {
    private:
        unsigned cols;
        unsigned rows;

        unsigned rectWidth;
        unsigned rectHeight;

        // Mutable added because the const attribute of the draw method
        mutable std::vector<std::vector<sf::Text>> texts;
        mutable std::vector<std::vector<sf::RectangleShape>> rectangles;

        mutable std::vector<sf::Text> ticksTextsx;
        mutable std::vector<sf::RectangleShape> ticksx;

        mutable std::vector<sf::Text> ticksTextsy;
        mutable std::vector<sf::RectangleShape> ticksy;

        // x and y axis
        sf::RectangleShape xAxisLine;
        sf::RectangleShape yAxisLine;

    public:
        unsigned y;
        unsigned x;
        unsigned width;
        unsigned height;
        unsigned textSize;
        unsigned squareSize;

        float maxValue;

        sf::Font font;
        std::vector<std::vector<float>>& data;

    public:
        Heatmap(
                sf::Font font,
                unsigned textSize,
                unsigned squareSize,
                float maxValue,
                unsigned width,
                unsigned height,
                unsigned x,
                unsigned y,
                std::vector<std::vector<float>>& data
        );
        ~Heatmap();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        inline void drawAxis(sf::RenderTarget& target) const;
    };

} // namespace sfplot
#endif
