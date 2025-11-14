#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

class Button {
private:
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    int state = 0;

public:
    bool loadTextures(const std::vector<std::string>& paths);
    void setPosition(float x, float y);
    bool contains(sf::Vector2f point);
    void onClick();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void setScale(float scale);
};