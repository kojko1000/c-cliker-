#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>

class SimpleButton {
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> textures; // 0-норма, 1-наведение, 2-нажатие
    sf::Vector2f originalPos;

    // Состояния
    bool isMouseOver = false;
    bool isPressed = false;

    // Для тряски
    bool isShaking = false;
    sf::Clock shakeTimer;
    float shakeDuration = 0.1f;
    float shakeIntensity = 3.0f;

public:
    // Загрузка 3 текстур: норма, ховер, клик
    bool loadTextures(const std::string& normal, const std::string& hover, const std::string& clicked);

    // Основные методы
    void setPosition(float x, float y);
    void setScale(float scale);
    void draw(sf::RenderWindow& window);
    bool contains(sf::Vector2f point);
    sf::Vector2f getPosition();
    sf::FloatRect getBounds();

    // Обработка событий мыши
    void handleMousePress(const sf::Vector2f& mousePos);
    void handleMouseRelease(const sf::Vector2f& mousePos, std::function<void()> callback = nullptr);

    // Обновление состояния
    void update(const sf::Vector2f& mousePos);

    // Тряска
    void startShake();
    void updateShake();

private:
    void updateTexture();
};