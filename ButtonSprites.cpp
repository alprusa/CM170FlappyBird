#include "ButtonSprites.h"

Buttons::Buttons(float xPos, float yPos, string btTexture){
    pressed = false;

    if(btTexture == "play"){
        // Load a texture to display for play button sprite
        if (!buttonTexture.loadFromFile("PlaySprite.png"))
            return;
    }
    else if(btTexture == "score"){
        // Load a texture to display for score button sprite
        if (!buttonTexture.loadFromFile("ScoreSprite.png"))
            return;
    }
    else if(btTexture == "back"){
        // Load a texture to display for back button sprite
        if (!buttonTexture.loadFromFile("BackSprite.png"))
            return;
    }
    else if(btTexture == "scoreBoard"){
        // Load a texture to display for scoreBoard screen sprite
        if (!buttonTexture.loadFromFile("ScoreBoard.png"))
            return;
    }
    else if(btTexture == "instructions"){
        // Load a texture to display for instructions screen sprite
        if (!buttonTexture.loadFromFile("Instructions.png"))
            return;
    }

    button.setTexture(buttonTexture);
    button.setPosition(xPos,yPos);
    button.setScale(0.5f,0.5f);
}

void Buttons::mouseClick(sf::RenderWindow& window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) && button.getGlobalBounds().contains(mousePosition.x,mousePosition.y);
}
