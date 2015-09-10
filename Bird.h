#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Bird{
    private:
        sf::Sprite bird;
    public:
        Bird(float xPos, float yPos, sf::Texture& bd);
        ~Bird(){cout << "The Bird is down" << endl;}
        void moveBird(float xP, float yP){bird.move(xP,yP);}
        void rotateBird(string degree);

        sf::Sprite getBird(){return bird;}
        float getX(){return bird.getPosition().x;}
        float getY(){return bird.getPosition().y;}
};

#endif
