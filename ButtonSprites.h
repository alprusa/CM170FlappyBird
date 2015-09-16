#ifndef BUTTONSPRITES_H
#define BUTTONSPRITES_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Buttons{
    private:
        sf::Sprite button;
        sf::Texture buttonTexture;
        bool pressed;
    public:
        Buttons(float xPos, float yPos, string btTexture);
        ~Buttons(){cout << "Buttons Gone" << endl;}

        void mouseClick(sf::RenderWindow& window);
        void setPressed(bool press){pressed = press;}

        sf::Sprite getButton(){return button;}
        bool isPressed(){return pressed;}
};

#endif
