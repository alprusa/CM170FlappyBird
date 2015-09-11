#include "ButtonSprites.h"

Buttons::Buttons(float xPos, float yPos, sf::Texture& bt){
    pressed = false;
    button.setTexture(bt);
    button.setPosition(xPos,yPos);
    button.setScale(0.5f,0.5f);
}

void Buttons::mouseClick(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) && button.getGlobalBounds().contains(mousePosition.x,mousePosition.y);
}
