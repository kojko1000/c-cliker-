#include "Button.h"
#include <random>
 //загрузка текстур
	bool Button::loadTextures(const std::vector<std::string>& paths) {
		for (const std::string path : paths) {
			sf::Texture texture;
			if (!texture.loadFromFile(path)){
				std::cout << "ne"<< path <<std::endl;
				return false;
			}
			textures.push_back(texture);
		}
		if (!textures.empty())
			sprite.setTexture(textures[0]);
		
		return true;
	}

	void Button::setPosition(float x, float y){
		sprite.setPosition(x, y);
	}
	sf::Vector2f Button::getPosition() {
		return sprite.getPosition();
	}

	bool Button::contains(sf::Vector2f point) {
		return sprite.getGlobalBounds().contains(point);
	}

	void Button::onClick() {
		if (textures.empty()) return;
		startShake();
		state = (state + 1) % textures.size();
		

		sprite.setTexture(textures[state]);

		std::cout << "CLICK!!!"<<std::endl;
	}

	void Button::draw(sf::RenderWindow& window){
		window.draw(sprite);
	}

	sf::FloatRect Button::getBounds() {
		return sprite.getGlobalBounds();
	}

	void Button::setScale(float scale) {
		Button::sprite.setScale(scale, scale);
	}

	//причина ТРЯСКИ!

	void Button::startShake() {
		if (!isShaking) {
			isShaking = true;
			originalPos = sprite.getPosition();
			shakeTimer.restart();
		}
	}

	void Button::updateShake() {
		if (isShaking) {
			float elapsed = shakeTimer.getElapsedTime().asSeconds();
			if (elapsed < shakeDuration)
			{
				//rand
				static std::mt19937 gen(std::random_device{}());
				std::uniform_real_distribution<float> dis(-shakeIntensity, shakeIntensity);

				float offsetX = dis(gen);
				float offsetY = dis(gen);
				sprite.setPosition(originalPos.x + offsetX, originalPos.y + offsetY);
			}
			else
			{
				isShaking = false;
				sprite.setPosition(originalPos);
			}
		}
	}