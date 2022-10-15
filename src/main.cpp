#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "lib/Heatmap.h"

////////////////////////////////////////////
///////////////// SETTINGS /////////////////
////////////////////////////////////////////
const int SQUARE_SIZE = 50;
const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 800;
const char FONT_PATH[] = "../Arial.ttf";
////////////////////////////////////////////
////////////// SETTINGS - END //////////////
////////////////////////////////////////////

void plot(
    sf::RenderWindow &window,
    sf::Font font,
    unsigned squareSize,
    float maxValue,
    std::vector<std::vector<float>> &data,
    unsigned width,
    unsigned height,
    unsigned x,
    unsigned y,
    unsigned textSize);
void getData(std::vector<std::vector<float>> &data, unsigned amount);

int main(int, char **)
{
    /////////////////////////////
    // Window creation - BEGIN //
    /////////////////////////////

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int32_t windowStyle = sf::Style::Default;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Neural Network - float", windowStyle, settings);
    window.setFramerateLimit(0);

    // Puts the orign at the center
    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(view);

    ///////////////////////////
    // Window creation - END //
    ///////////////////////////

    // Ensuring that the random numbers are going to honor its names
    std::srand(std::time(nullptr));

    sf::Font font;
    font.loadFromFile(FONT_PATH);

    std::vector<std::vector<float>> data;

    // Aplication main loop
    while (window.isOpen())
    {
        // Drawing the data
        window.clear(sf::Color::Magenta);
        auto time = int(1000 * (std::rand() / (float)RAND_MAX));
        sf::sleep(sf::milliseconds(time));
        getData(data, 20);

        plot(window, font, SQUARE_SIZE, 1, data, 1000, 1000, 50, 50, 14);

        sfplot::Heatmap a(font,14);
 
        window.display();

        // Window and keyboard events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
        }
    }
}

void getData(std::vector<std::vector<float>> &data, unsigned amount)
{
    // data = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    data.resize(amount);

    for (auto &&line : data)
    {
        line.resize(amount);

        for (auto &&item : line)
        {
            item = std::rand() / (float)RAND_MAX;
        }
    }
}

void plot(
    sf::RenderWindow &window,
    sf::Font font,
    unsigned squareSize,
    float maxValue,
    std::vector<std::vector<float>> &data,
    unsigned width,
    unsigned height,
    unsigned x,
    unsigned y,
    unsigned textSize)
{
    std::vector<std::vector<sf::RectangleShape>> rectangles;
    std::vector<std::vector<sf::Text>> texts;

    unsigned cols = data.size();
    unsigned rows = data[0].size();
    unsigned rectWidth = width / (float)squareSize;
    unsigned rectHeight = height / (float)squareSize;

    // Positioning x axis
    sf::RectangleShape xAxis(sf::Vector2f(rectWidth * cols + 2, 2));
    xAxis.setFillColor(sf::Color::Black);
    xAxis.setPosition(x, y + cols * rectHeight);

    // Positioning y axis
    sf::RectangleShape yAxis(sf::Vector2f(2, rectHeight * rows + 2));
    yAxis.setFillColor(sf::Color::Black);
    yAxis.setPosition(x, y);

    // Allocates space for squares
    rectangles.resize(rows);
    texts.resize(rows);

    for (auto &r : rectangles)
        r.resize(cols);

    for (auto &t : texts)
        t.resize(cols);

    for (unsigned int i = 0; i < cols; i++)
    {
        for (unsigned int j = 0; j < rows; j++)
        {
            auto value = data[i][j] / maxValue;

            rectangles[i][j] = sf::RectangleShape(sf::Vector2f(rectWidth, rectHeight));
            rectangles[i][j].setPosition(x + i * rectWidth, y + j * rectHeight);
            rectangles[i][j].setFillColor(sf::Color(
                value * 255,
                255,
                value * 255,
                255));

            // texts[i][j].setFont(font);
            // texts[i][j].setCharacterSize(resolution / 4);
            // texts[i][j].setStyle(sf::Text::Regular);
            // texts[i][j].setFillColor(sf::Color(0, 0, 0));
            // texts[i][j].setPosition(x + i * rectWidth, y + j * rectHeight);
            // texts[i][j].setString(std::to_string(value));

            window.draw(rectangles[i][j]);
            window.draw(xAxis);
            window.draw(yAxis);

            // window.draw(texts[i][j]);
        }
    }

    // Draws the x and y axis
    for (unsigned int i = 0; i <= cols; i++)
    {

        // x axis ticks
        sf::RectangleShape tickx(sf::Vector2f(2, 4));
        tickx.setFillColor(sf::Color::Black);
        tickx.setPosition(x + i * rectWidth, y + cols * rectHeight);

        sf::Text tickTextx;
        tickTextx.setCharacterSize(textSize);
        tickTextx.setFont(font);
        tickTextx.setFillColor(sf::Color::Black);
        tickTextx.setPosition(x + i * rectWidth - tickTextx.getLocalBounds().width - 4, y + cols * rectHeight + 4);
        tickTextx.setString(std::to_string(i));
        window.draw(tickx);
        window.draw(tickTextx);
    }
    for (unsigned int j = 1; j <= cols; j++)
    {
        // y axis ticks
        sf::RectangleShape ticky(sf::Vector2f(4, 2));
        ticky.setFillColor(sf::Color::Black);
        ticky.setPosition(x - 2, y + j * rectHeight);

        sf::Text tickTexty;
        tickTexty.setCharacterSize(textSize);
        tickTexty.setFont(font);
        tickTexty.setFillColor(sf::Color::Black);
        tickTexty.setString(std::to_string(j));
        tickTexty.setPosition(x - tickTexty.getLocalBounds().width - 6, y + cols * rectHeight - j * rectHeight - tickTexty.getLocalBounds().height);
        window.draw(ticky);
        window.draw(tickTexty);
    }
}
