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

void Bird::moveBird(bool fly){
    //create garvity
    const float gravity = 5;
    sf::Vector2f velocity(sf::Vector2f(0,0));
    int groundHeight = 600;
    float moveSpeed = 90;

    if(fly) velocity.y = -moveSpeed; //make the bird go against gravity (fly)

    if(bird.getPosition().y + bird.getScale().y < groundHeight || velocity.y == 0) velocity.y += gravity;
    else {
        bird.setPosition(bird.getPosition().x, groundHeight - bird.getScale().y);
        velocity.y = 0;
    }

    bird.move(velocity.x, velocity.y);
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
