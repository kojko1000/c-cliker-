#include "SimpleButton.h"
#include <random>
#include <iostream>

bool SimpleButton::loadTextures(const std::string& normal, const std::string& hover, const std::string& clicked) {
    textures.resize(3);

    if (!textures[0].loadFromFile(normal)) {
        std::cout << "Не загружена текстура: " << normal << std::endl;
        return false;
    }
    if (!textures[1].loadFromFile(hover)) {
        std::cout << "Не загружена текстура: " << hover << std::endl;
        textures[1] = textures[0];
    }
    if (!textures[2].loadFromFile(clicked)) {
        std::cout << "Не загружена текстура: " << clicked << std::endl;
        textures[2] = textures[1];
    }

    sprite.setTexture(textures[0]);
    return true;
}

void SimpleButton::setPosition(float x, float y) {
    originalPos = sf::Vector2f(x, y);
    sprite.setPosition(x, y);
}

void SimpleButton::setScale(float scale) {
    sprite.setScale(scale, scale);
}

void SimpleButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool SimpleButton::contains(sf::Vector2f point) {
    return sprite.getGlobalBounds().contains(point);
}

sf::Vector2f SimpleButton::getPosition() {
    return sprite.getPosition();
}

sf::FloatRect SimpleButton::getBounds() {
    return sprite.getGlobalBounds();
}

void SimpleButton::handleMousePress(const sf::Vector2f& mousePos) {
    if (contains(mousePos)) {
        isPressed = true;
        updateTexture();
    }
}

void SimpleButton::handleMouseRelease(const sf::Vector2f& mousePos, std::function<void()> callback) {
    if (isPressed && contains(mousePos)) {
        // Клик завершен успешно
        startShake();
        if (callback) {
            callback();
        }
    }

    isPressed = false;
    updateTexture();
}

void SimpleButton::update(const sf::Vector2f& mousePos) {
    bool wasMouseOver = isMouseOver;
    isMouseOver = contains(mousePos);

    // Обновляем текстуру только если состояние изменилось
    if (wasMouseOver != isMouseOver && !isPressed) {
        updateTexture();
    }
}

void SimpleButton::startShake() {
    if (!isShaking) {
        isShaking = true;
        shakeTimer.restart();
    }
}

void SimpleButton::updateShake() {
    if (isShaking) {
        float elapsed = shakeTimer.getElapsedTime().asSeconds();
        if (elapsed < shakeDuration) {
            static std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<float> dis(-shakeIntensity, shakeIntensity);

            float offsetX = dis(gen);
            float offsetY = dis(gen);
            sprite.setPosition(originalPos.x + offsetX, originalPos.y + offsetY);
        }
        else {
            isShaking = false;
            sprite.setPosition(originalPos);
            updateTexture(); // Восстанавливаем правильную текстуру после тряски
        }
    }
}

void SimpleButton::updateTexture() {
    if (isShaking) return; // Не меняем текстуру во время тряски

    if (isPressed) {
        sprite.setTexture(textures[2]); // Нажатое состояние
    }
    else if (isMouseOver) {
        sprite.setTexture(textures[1]); // Ховер состояние
    }
    else {
        sprite.setTexture(textures[0]); // Нормальное состояние
    }
}