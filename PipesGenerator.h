#ifndef PIPESGENERATOR_H
#define PIPESGENERATOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Pipes{
    private:
        vector<sf::Sprite> pipes;
        float timeElapsed;
    public:
        Pipes(int xPos, int yPos, sf::Texture& pi);
        ~Pipes(){cout << "No more Pipes" << endl;}
        void resetPipes(int xPos, int yPos, sf::Texture& pi);
        void increaseTime(){timeElapsed++;}

        sf::Sprite getPipes(float speed, int index);
        unsigned getSize(){return pipes.size();}
        float getPipesX(int index){return pipes[index].getPosition().x;}
        float getPipesY(int index){return pipes[index].getPosition().y;}
        float getRotation(int index){return pipes[index].getRotation();}
};

#endif
