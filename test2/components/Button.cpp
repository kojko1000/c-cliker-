#include "Button.h"
#include "GlobalState.h"
#include <random>
 
	//________________INIT_______________
	//загрузка текстур
	bool Button::loadTextures(const std::vector<std::string>& paths) { 
	for (const std::string path : paths) {
		sf::Texture texture;
		if (!texture.loadFromFile(path)) {
			std::cout << "ne" << path << std::endl;
			return false;
		}
		textures.push_back(texture);
	}
	if (!textures.empty())
		sprite.setTexture(textures[0]);
	return true;
	}
	//
	void Button::draw(sf::RenderWindow& window) {
		window.draw(sprite);
	}
	//
	void Button::onClick() {
		if (textures.empty()) return;
		startShake();

		if ((int)state!= (int)(state+ GlobalState::clickCost)){std::cout<<"AAAAAAAAAAAA"; }
		state = state + GlobalState::clickCost;
		if (state >= textures.size()/texturePack) {
			state = 0;
			GlobalState::disassembledCount++;
		}
		
		sprite.setTexture(textures[(int)state*texturePack]);
		
		GlobalState::clickCount++;
		//std::cout << "CLICK!!!  " << state <<"     " << (int)state * texturePack << std::endl;
	}

	
	//_____________GETS__________________
	sf::FloatRect Button::getBounds()			{return sprite.getGlobalBounds();}

	bool Button::contains(sf::Vector2f point)	{return sprite.getGlobalBounds().contains(point);}

	sf::Vector2f Button::getPosition()			{return sprite.getPosition();}

	float Button::getState() { return state; }
	//_____________SETS__________________
	void Button::setScale(float scale)			{Button::sprite.setScale(scale, scale);}

	void Button::setPosition(float x, float y)	{sprite.setPosition(x, y);}
	//________причины_“–я— »!___________
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