#include "Bird.h"

Bird::Bird(float xPos, float yPos, sf::Texture& bd){
    bestScore = 0;
    bird = sf::Sprite(bd);
    bird.setScale(0.1f,0.1f);
    bird.setPosition(xPos,yPos);
}

void Bird::resetBird(float xPos, float yPos, sf::Texture& bd){
    bird = sf::Sprite(bd);
    bird.setScale(0.1f,0.1f);
    bird.setPosition(xPos,yPos);
    dead = false;
}

void Bird::rotateBird(string degree){
    float rotation = bird.getRotation();
    if(degree == "up" && rotation != -45)
        bird.rotate(-45);
    else if(degree == "down" && rotation != 45)
        bird.rotate(45);
    else if(degree == "dead" && rotation != 90){
        bird.rotate(90);
        dead = true;
    }
    else if(rotation != 0)
        bird.rotate(-rotation);
}
