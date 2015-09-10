#ifndef BUTTONSPRITES_H
#define BUTTONSPRITES_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Buttons{
    private:
        sf::Sprite button;
        bool pressed;
        bool activated;
    public:
        Buttons(float xPos, float yPos, sf::Texture& bt);
        ~Buttons(){cout << "Buttons Gone" << endl;}

        void mouseClick(sf::RenderWindow& window);
        void setActivated(bool act){activated = act;}

        sf::Sprite getButton(){return button;}
        bool isPressed(){return pressed;}
};

#endif
