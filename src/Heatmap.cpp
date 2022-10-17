#include "../include/Heatmap.h"

sfplot::Heatmap::Heatmap(
    sf::Font font,
    unsigned textSize,
    float maxValue,
    unsigned width,
    unsigned height,
    unsigned x,
    unsigned y,
    std::vector<std::vector<float>>& data)
    : font(font)
    , textSize(textSize)
    , maxValue(maxValue)
    , width(width)
    , height(height)
    , x(x)
    , y(y)
    , data(data)
    , cols(data.size())
    , rows(data[0].size())
    , rectWidth(width / (float)data.size())
    , rectHeight(height / (float)data[0].size())
    , xAxisLine(sf::Vector2f(rectWidth * cols + 2, 2))
    , yAxisLine(sf::Vector2f(2, rectHeight * rows + 2))
{

    // Positioning x axis
    xAxisLine.setFillColor(sf::Color::Black);
    xAxisLine.setPosition(x, y + cols * rectHeight);

    // Positioning y axis
    yAxisLine.setFillColor(sf::Color::Black);
    yAxisLine.setPosition(x, y);

    // Allocates space for squares
    this->rectangles.resize(rows);
    this->texts.resize(rows);

    for (auto& r : rectangles)
        r.resize(cols);

    for (auto& t : texts)
        t.resize(cols);

    for (unsigned int i = 0; i < cols; i++) {
        for (unsigned int j = 0; j < rows; j++) {
            rectangles[i][j] = sf::RectangleShape(sf::Vector2f(rectWidth, rectHeight));
            rectangles[i][j].setPosition(x + i * rectWidth, y + j * rectHeight);
            // texts[i][j].setFont(font);
            // texts[i][j].setCharacterSize(resolution / 4);
            // texts[i][j].setStyle(sf::Text::Regular);
            // texts[i][j].setFillColor(sf::Color(0, 0, 0));
            // texts[i][j].setPosition(x + i * rectWidth, y + j * rectHeight);
            // texts[i][j].setString(std::to_string(value));
        }
    }

    // Allocate space for the ticks
    this->ticksx.resize(cols + 1);
    this->ticksTextsx.resize(cols + 1);
    this->ticksy.resize(rows + 1);
    this->ticksTextsy.resize(rows + 1);

    // Prepare the x and y axis ticks
    for (unsigned int i = 0; i <= cols; i++) {
        // x axis ticks
        sf::RectangleShape tickx(sf::Vector2f(2, 4));
        tickx.setFillColor(sf::Color::Black);

        sf::Text tickTextx;
        tickTextx.setCharacterSize(textSize);
        tickTextx.setFillColor(sf::Color::Black);
        tickTextx.setString(std::to_string(i));

        this->ticksx[i] = tickx;
        this->ticksTextsx[i] = tickTextx;
    }

    for (unsigned int j = 1; j <= rows; j++) {
        // y axis ticks
        sf::RectangleShape ticky(sf::Vector2f(4, 2));
        ticky.setFillColor(sf::Color::Black);

        sf::Text tickTexty;
        tickTexty.setCharacterSize(textSize);
        tickTexty.setFillColor(sf::Color::Black);
        tickTexty.setString(std::to_string(j));

        this->ticksy[j] = ticky;
        this->ticksTextsy[j] = tickTexty;
    }
}

inline void sfplot::Heatmap::drawAxis(sf::RenderTarget& target) const
{

    // Draws the x and y axis lines
    target.draw(xAxisLine);
    target.draw(yAxisLine);

    // Draws the x and y axis ticks
    for (unsigned int i = 0; i <= cols; i++) {
        // x axis ticks
        this->ticksx[i].setPosition(x + i * rectWidth, y + cols * rectHeight);

        this->ticksTextsx[i].setFont(font);
        this->ticksTextsx[i].setPosition(x + i * rectWidth - this->ticksTextsx[i].getLocalBounds().width + 3, y + cols * rectHeight + 4);

        target.draw(this->ticksx[i]);
        target.draw(this->ticksTextsx[i]);
    }
    for (unsigned int j = 1; j <= cols; j++) {
        // y axis ticks
        this->ticksy[j].setPosition(x - 2, y + j * rectHeight);

        this->ticksTextsy[j].setFont(font);
        this->ticksTextsy[j].setPosition(x - this->ticksTextsy[j].getLocalBounds().width - 6, y + cols * rectHeight - j * rectHeight - this->ticksTextsy[j].getLocalBounds().height);

        target.draw(this->ticksy[j]);
        target.draw(this->ticksTextsy[j]);
    }
}

void sfplot::Heatmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    for (unsigned int i = 0; i < cols; i++) {
        for (unsigned int j = 0; j < rows; j++) {
            auto value = data[i][j] / maxValue;

            rectangles[i][j].setFillColor(sf::Color(value * 255, 255, value * 255, 255));

            // texts[i][j].setString(std::to_string(value));

            target.draw(rectangles[i][j]);

            // window.draw(texts[i][j]);
        }
    }

    this->drawAxis(target);
}

sfplot::Heatmap::~Heatmap()
{
}
