#include "SimpleButton.h"

SimpleButton::SimpleButton() : currentState(NORMAL), isMouseOver(false) {
    textures.resize(3); // Резервируем место под 3 текстуры
}

bool SimpleButton::loadTextures(const std::string& normal, const std::string& hover, const std::string& clicked) {
    // Загружаем текстуру для нормального состояния
    if (!textures[NORMAL].loadFromFile(normal)) {
        std::cout << "Не удалось загрузить текстуру: " << normal << std::endl;
        return false;
    }

    // Загружаем текстуру для наведения
    if (!textures[HOVER].loadFromFile(hover)) {
        std::cout << "Не удалось загрузить текстуру: " << hover << std::endl;
        // Можно использовать нормальную текстуру как fallback
        textures[HOVER] = textures[NORMAL];
    }

    // Загружаем текстуру для клика
    if (!textures[CLICKED].loadFromFile(clicked)) {
        std::cout << "Не удалось загрузить текстуру: " << clicked << std::endl;
        textures[CLICKED] = textures[HOVER]; // Fallback на hover
    }

    // Устанавливаем начальную текстуру
    sprite.setTexture(textures[NORMAL]);
    updateBounds();

    return true;
}

bool SimpleButton::loadTextures(const std::vector<std::string>& texturePaths) {
    if (texturePaths.size() < 3) {
        std::cout << "Нужно 3 текстуры: normal, hover, clicked!" << std::endl;
        return false;
    }

    return loadTextures(texturePaths[0], texturePaths[1], texturePaths[2]);
}

void SimpleButton::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position);
    updateBounds();
}

void SimpleButton::setPosition(const sf::Vector2f& pos) {
    position = pos;
    sprite.setPosition(position);
    updateBounds();
}

void SimpleButton::setScale(float scale) {
    sprite.setScale(scale, scale);
    updateBounds();
}

void SimpleButton::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
    updateBounds();
}

void SimpleButton::setOnClick(std::function<void()> callback) {
    onClickCallback = callback;
}

void SimpleButton::update(const sf::Vector2f& mousePos) {
    // Проверяем наведение мыши
    bool wasMouseOver = isMouseOver;
    isMouseOver = bounds.contains(mousePos);

    // Если мышь только что навелась
    if (isMouseOver && !wasMouseOver && currentState == NORMAL) {
        currentState = HOVER;
        updateTexture();
    }
    // Если мышь ушла
    else if (!isMouseOver && wasMouseOver && currentState == HOVER) {
        currentState = NORMAL;
        updateTexture();
    }
}

void SimpleButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void SimpleButton::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && bounds.contains(mousePos)) {
            currentState = CLICKED;
            updateTexture();
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Если кнопка была нажата и мышь всё ещё над кнопкой - вызываем колбэк
            if (currentState == CLICKED && bounds.contains(mousePos)) {
                if (onClickCallback) {
                    onClickCallback();
                }
            }

            // Возвращаем к нормальному состоянию или hover
            currentState = bounds.contains(mousePos) ? HOVER : NORMAL;
            updateTexture();
        }
    }
}

void SimpleButton::updateTexture() {
    if (currentState >= 0 && currentState < textures.size() &&
        textures[currentState].getSize().x > 0) {
        sprite.setTexture(textures[currentState]);
    }
}

void SimpleButton::updateBounds() {
    bounds = sprite.getGlobalBounds();
}