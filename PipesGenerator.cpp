#include "PipesGenerator.h"

//return array of pipe sprites in generated function
vector<sf::Sprite> pipeGen(float xPos, float yPos, sf::Texture& pi){
    vector<sf::Sprite> pipes;
    //temp sprite set
    for(int i = 0; i < 999; i++) {
        sf::Sprite pipeTemp;
        pipeTemp.setTexture(pi);

        //to setup the different x positions
        if(i < 12) xPos += i;
        else xPos *= i;

        //to setup the diferent y positions
        if(i < 12 and i % 4 == 0 and yPos < 280 and yPos > -40) yPos += i;
        else yPos *= i;

        pipeTemp.setPosition(xPos, yPos);

        //if(i % 2 == 0) pipeTemp.rotate(180);

        pipes.push_back(pipeTemp);
    }
    return pipes;
}

//call generator here and just have the private object be the pipes sprite array not single sprite
Pipes::Pipes(float xPos, float yPos, sf::Texture& pi){
    pipes = pipeGen(xPos, yPos, pi);
}

void Pipes::resetPipes(float xPos, float yPos, sf::Texture& pi){
    pipes = pipeGen(xPos, yPos, pi);
}

//get the pipes so that they cab be drawn to the screen
vector<sf::Sprite> Pipes::getPipes(float speed){
    float ySpeed = 0;

    for(int i = 0; i < pipes.size(); i++) {
        if((i > 300 && i < 310) || (i < 115 && i > 110)) ySpeed = -(5 + ySpeed); //to make moving pipes
        else ySpeed = 0;

        pipes[i].setPosition( pipes[i].getPosition().x + speed, pipes[i].getPosition().y + ySpeed);
    }

    return pipes;
}

//fix the gravity/rise
//fix the scroll look make it smooth
//make the pipes actually exist
//fix the score incrementor and make it happen when bird goes past pipe not just at 250px
//change the bird sprite
//fix the back/scoreboard button switch
