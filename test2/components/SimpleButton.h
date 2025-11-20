#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

class SimpleButton {
public:
    enum State {
        NORMAL = 0,    // Обычное состояние
        HOVER = 1,     // Наведение мыши
        CLICKED = 2    // Нажатие
    };

private:
    std::vector<sf::Texture> textures; // 0-NORMAL, 1-HOVER, 2-CLICKED
    sf::Sprite sprite;
    State currentState;
    bool isMouseOver;

    // Позиция и размеры
    sf::Vector2f position;
    sf::FloatRect bounds;

    // Колбэк функция при клике
    std::function<void()> onClickCallback;

public:
    SimpleButton();

    // Загрузка текстур для всех состояний
    bool loadTextures(const std::string& normal, const std::string& hover, const std::string& clicked);

    // Альтернативный способ - одним вектором
    bool loadTextures(const std::vector<std::string>& texturePaths);

    // Установка позиции
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);

    // Установка масштаба
    void setScale(float scale);
    void setScale(float scaleX, float scaleY);

    // Установка колбэка
    void setOnClick(std::function<void()> callback);

    // Обновление (вызывать каждый кадр)
    void update(const sf::Vector2f& mousePos);

    // Отрисовка
    void draw(sf::RenderWindow& window);

    // Обработка событий мыши
    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);

    // Геттеры
    State getState() const { return currentState; }
    sf::Vector2f getPosition() const { return position; }
    sf::FloatRect getBounds() const { return bounds; }
    bool isClicked() const { return currentState == CLICKED; }

private:
    void updateTexture();
    void updateBounds();
};