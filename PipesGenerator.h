#ifndef PIPESGENERATOR_H
#define PIPESGENERATOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Pipes{
    private:
        vector<sf::Sprite> pipes;
        vector<bool> passedThrough;
        sf::Texture pipeTexture;
        int width;
        int height;
    public:
        Pipes(int xPos, int yPos);
        ~Pipes(){cout << "No more Pipes" << endl;}
        void resetPipes(int xPos, int yPos);
        void setPassedStats(int index){passedThrough[index] = true;}

        sf::Vector2<sf::Sprite> getPipes(float speed, int index);
        unsigned getSize(){return pipes.size();}
        float getPipesX(int index){return pipes[index].getPosition().x;}
        float getPipesY(int index){return pipes[index].getPosition().y;}
        float getRotation(int index){return pipes[index].getRotation();}
        bool getPassedStats(int index){return passedThrough[index];}
        int getWidth(){return width;}
        int getHeight(){return height;}
};

#endif
