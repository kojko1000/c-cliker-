#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>


class Button {
private:
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    int texturePack = 0;
    int texturePacks = 1;
    float state = 0;

    //_____для тряски____
    bool isShaking = false;
    sf::Vector2f originalPos;
    sf::Clock shakeTimer;
    float shakeDuration = 0.1;
    float shakeIntensity = 5.0;
    //_____для бонусов
    float bonusDuration = 0.1;
    bool isScrapBonus = false;
    sf::Clock scrapBonusTimer;
    bool isCritBonus = false;
    sf::Clock critBonusTimer;


    //типо ивет
    //ИВЕНТА НЕ БУДЕТ!
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
    bool getIsScrapBonus();
    bool getIsCritBonus();
    float getState();
    //для тряски-----------
    void startShake();
    void updateShake();
    //таймеры для бонусов
    void startScrapBonus();
    void updateScrapBonus();
    void startCritBonus();
    void updateCritBonus();
    //ИВЕНТА НЕ БУДЕТ!
};