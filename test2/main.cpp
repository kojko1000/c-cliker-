#include <SFML/Graphics.hpp>
#include "components/Button.h"
#include "components/Lable.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "It's WIN!");
    //--------
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

    //-------
    Label text1;
    if (!text1.loadFont("fonts/USSR STENCIL WEBFONT.ttf")) return -1;
    text1.setString("0");
    text1.setPosition(50, 50);
    //-------
    //-------
    sf::CircleShape sph1 = sf::CircleShape(300.f);
    sph1.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        
        sf::Event event;
        //--------------------------------------
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) 
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (buttonRadio.contains(mousePos)) {
                        buttonRadio.onClick();
                        text1.setString(buttonRadio.getClickCount());
                    }
                }
            
        }//«¿ –€¬¿≈Ã—ﬂ
        //--------------------------------------
        
        buttonRadio.updateShake();
        
        window.clear(sf::Color(30,30,30));
        window.draw(sph1);
        text1.draw(window);
        buttonRadio.draw(window);
        
        window.display();
    }

    return 0;
}