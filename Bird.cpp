#include "Bird.h"

Bird::Bird(float xPos, float yPos, sf::Texture& bd){
    bird = sf::Sprite(bd);
    bird.setScale(0.1f,0.1f);
    bird.setPosition(xPos,yPos);
}
