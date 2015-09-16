#include "Background.h"

Background::Background(int x, int y, sf::Vector2i sSize){
    backScrollX = 0;
    screenSize = sSize;

    //scrolling background texture
    if(!backgroundTexture.loadFromFile("fbbackground.png"))
        return;
    backgroundTexture.setSmooth(true);
    backgroundTexture.setRepeated(true);

    //scrolling background sprite
    backgroundS.setTexture(backgroundTexture);
    backgroundS.setPosition(x, y);
    backgroundS.setTextureRect(sf::IntRect(0,0,screenSize.x,screenSize.y));
    backgroundS.setScale(1.0f, (float)screenSize.y / backgroundTexture.getSize().y);
}

void Background::reset(){
    backScrollX = 0;
    backgroundS.setTextureRect(sf::IntRect(0,0,screenSize.x,screenSize.y));
}

void Background::move(bool lifeDetector){
    float moveSpeed = 4.0f; //scroll speed

    //making the screen scroll by moving the background image horizontally
    if(backScrollX < screenSize.x && !lifeDetector) {
        backScrollX += moveSpeed;
    }
    else{
        backScrollX = 0;
    }

    //set the position of the background texture on the moving sprite
    backgroundS.setTextureRect(sf::IntRect(backScrollX,0,screenSize.x,screenSize.y));
}
