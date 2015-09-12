#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Bird{
    private:
        sf::Sprite bird;
        int bestScore;
        bool dead;
    public:
        Bird(float xPos, float yPos, sf::Texture& bd); //constructor
        ~Bird(){cout << "The Bird is down" << endl;} //destructor
        void moveBird(bool fly); //make movements to the bird sprite
        void rotateBird(string degree); //rotate the bird sprite mainly just for visual purposes
        void resetBird(float xPos, float yPos, sf::Texture& bd); //make the bird go back to how it started
        void setScore(int score){if(score > bestScore) bestScore = score;} //this is the set best score saved for the user in the game loop a temp score variable is used

        sf::Sprite getBird(){return bird;} //get the bird sprite to draw or get data
        float getX(){return bird.getPosition().x;} //get the current x position of the bird
        float getY(){return bird.getPosition().y;} //get the current y position of the bird
        bool getLifeDetector(){return dead;}
        int getScore(){return bestScore;}
};

#endif
