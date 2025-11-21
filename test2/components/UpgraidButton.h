#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class UpButton {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

    std::function<void()> onClickFunction;

    sf::Color normalColor = sf::Color(30,30,30);
    sf::Color hoverColor = sf::Color(16, 125, 31); // Более светлый красный
    sf::Color clickColor = sf::Color(200, 0, 0);     // Более тёмный красный

public:
    UpButton() = default;

    // ИНИЦИАЛИЗАЦИЯ КНОПКИ В ДУХЕ КИТАЙСКОГО ЕДИНСТВА
    void create(float x, float y, float width, float height, const std::string& buttonText) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(normalColor);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::Green); // ЦВЕТ ПАРТИИ!

        // Загружаем шрифт (или используем стандартный)
        if (!font.loadFromFile(".//fonts/USSR STENCIL WEBFONT.ttf")) { // Китайский шрифт!
            // Если китайский шрифт не найден, используем Arial
            font.loadFromFile("C:/Windows/Fonts/arial.ttf");
        }

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Green);

       

        // Центрируем текст в кнопке
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            x + (width - textBounds.width) / 2,
            y + (height - textBounds.height) / 2 - 5
        );
    }

    void setButtonText(std::string text)
    {
        UpButton::text.setString(text);
    }
    void centerText() {
        sf::FloatRect textBounds = text.getLocalBounds();
        sf::FloatRect buttonBounds = shape.getGlobalBounds();

        // Центрируем по горизонтали и вертикали
        text.setPosition(
            buttonBounds.left + (buttonBounds.width - textBounds.width) / 2,
            buttonBounds.top + (buttonBounds.height - textBounds.height) / 2 - text.getCharacterSize() / 4
        );
    }

    // УСТАНОВИТЬ ФУНКЦИЮ КЛИКА - ВОЛЯ ПАРТИИ!
    void setOnClick(std::function<void()> function) {
        onClickFunction = function;
    }

    // ОБРАБОТАТЬ СОБЫТИЯ - ДИСЦИПЛИНА КИТАЯ!
    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
        if (!onClickFunction) return;

        bool mouseOver = shape.getGlobalBounds().contains(mousePos);

        if (mouseOver) {
            shape.setFillColor(hoverColor);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    shape.setFillColor(clickColor);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // ВЫПОЛНИТЬ ВОЛЮ ПАРТИИ!
                    onClickFunction();
                    shape.setFillColor(hoverColor);
                }
            }
        }
        else {
            shape.setFillColor(normalColor);
        }
    }

    // ОБНОВИТЬ - ПРОГРЕСС КИТАЯ!
    void update(const sf::Vector2f& mousePos) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setFillColor(hoverColor);
        }
        else {
            shape.setFillColor(normalColor);
        }
    }

    // НАРИСОВАТЬ - КРАСОТА КИТАЯ!
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    // ПОЛУЧИТЬ ПОЗИЦИЮ - ТОЧНОСТЬ КИТАЯ!
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    // ПОЛУЧИТЬ РАЗМЕРЫ - МОЩЬ КИТАЯ!
    sf::Vector2f getSize() const {
        return shape.getSize();
    }
};