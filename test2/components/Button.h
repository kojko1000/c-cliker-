#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class Button {
private:
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    int state = 0;
    //для тряски-----------
    bool isShaking = false;
    sf::Vector2f originalPos;
    sf::Clock shakeTimer;
    float shakeDuration = 0.1;
    float shakeIntensity = 5.0;
public:
    //инициация
    bool loadTextures(const std::vector<std::string>& paths);
    bool contains(sf::Vector2f point);
    void draw(sf::RenderWindow& window);
    //функции
    void onClick();
    //сетеры
    void setScale(float scale);
    void setPosition(float x, float y);
    //гетеры
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    //для тряски-----------
    void startShake();
    void updateShake();
};