#include "Bird.h"

Bird::Bird(float xPos, float yPos, sf::Texture& bd){
    bird = sf::Sprite(bd);
    bird.setScale(0.1f,0.1f);
    bird.setPosition(xPos,yPos);
}

void Bird::rotateBird(string degree){
    float rotation = bird.getRotation();
    if(degree == "up" && rotation != -45)
        bird.rotate(-45);
    else if(degree == "down" && rotation != 45)
        bird.rotate(45);
    else if(degree == "dead" && rotation != 90)
        bird.rotate(90);
    else if(rotation != 0)
        bird.rotate(-rotation);
}
