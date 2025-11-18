#include <SFML/Graphics.hpp>
#include "components/Button.h"
#include "components/Lable.h"
#include "components/GlobalState.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "It's WIN!");
    //----MAIN_BUTTON----
    Button buttonRadio;

    float spriteSize = 5;
    std::vector<std::string> texturesPath = {
        "assets/Radio1.png",
        "assets/Radio2.png",
        "assets/Radio3.png",
        "assets/Radio4.png"};
    
    if (!buttonRadio.loadTextures(texturesPath)) return -1;
    buttonRadio.setPosition((window.getSize().x/2) - (32 * spriteSize) / 2, (window.getSize().y / 2) - (32 * spriteSize) / 2);
    buttonRadio.setScale(spriteSize);
    //--------

    //-----TEXT_COUNTER----
    Label text1;
    if (!text1.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    text1.setColor(sf::Color::Green);
    text1.setString("0");
    text1.setPosition(0, 0);
    text1.startBlinking();

    Label text2;
    if (!text2.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    text2.setColor(sf::Color::Green);
    text2.setString("0");
    text2.setPosition(0, 50);
    text2.startBlinking();
    //-------
 
    //----shit---
    sf::CircleShape sph1 = sf::CircleShape(300.f);
    sph1.setFillColor(sf::Color::Green);
    //----------

    //--------GAME_CUCLE---------
    while (window.isOpen())
    {
        
        sf::Event event;
        //--------------------------------------
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) //«¿ –€¬¿≈Ã—ﬂ
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords( sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (buttonRadio.contains(mousePos)) {
                        buttonRadio.onClick();
                        text1.setString("" + std::to_string(GlobalState::clickCount));//!!!!
                    }
                }
        }
        //--------------------------------------
        
        //------DRAWS-------
        buttonRadio.updateShake();
        text1.update();
        window.clear(sf::Color(30,30,30));
       // window.draw(sph1);
        text1.draw(window);
        text2.draw(window);
        buttonRadio.draw(window);
        //------------------

        window.display();
    }
    //-------------------------------------
    return 0;
}