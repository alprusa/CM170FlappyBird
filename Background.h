#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Background{
    private:
        sf::Sprite backgroundS;
        sf::Texture backgroundTexture;
        int backScrollX; //view scroller x direction
        sf::Vector2i screenSize;
    public:
        Background(int x, int y, sf::Vector2i sSize);
        void move(bool lifeDetector);
        void reset();

        sf::Sprite getBackground(){return backgroundS;}
};

#endif
