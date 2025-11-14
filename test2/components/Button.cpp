#include "Button.h"

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

	bool Button::contains(sf::Vector2f point) {
		return sprite.getGlobalBounds().contains(point);
	}

	void Button::onClick() {
		if (textures.empty()) return;

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
