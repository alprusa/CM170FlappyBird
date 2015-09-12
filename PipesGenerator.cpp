#include "PipesGenerator.h"

//return array of pipe sprites in generated function
vector<sf::Sprite> pipeGen(float xPos, float yPos, sf::Texture& pi){
    vector<sf::Sprite> pipes;
    //temp sprite set
    for(int i = 0; i < 999; i++) {
        sf::Sprite pipeTemp;
        pipeTemp.setTexture(pi);
        if(i % 3 == 0) pipeTemp.rotate(180);

         //to setup the different x positions
        if(i < 12) xPos += (i + 146);
        else xPos += (i+126);

        //to setup the diferent y positions
        if(i < 12 and i % 4 == 0) {
            yPos += (i+280%10); //set next yPos

            //so that the pipe won't go to low
            if(yPos > 280 && pipeTemp.getRotation() != 180) {
                float difference = yPos - 280;
                yPos -= difference;
            }

            //so that the pipe does not float
            if(yPos < 284 && pipeTemp.getRotation() != 180){
                float difference = yPos - 284;
                yPos += difference;
            }
            //so the pipe doesn't go too high
            if(yPos < -40 && pipeTemp.getRotation() == 180){
                float difference = yPos + 40;
                yPos -= difference;
            }

            //so the pipe doesn't exceed the length of the pipe
            if(yPos > 284  && pipeTemp.getRotation() == 180){
                float difference = yPos - 284;
                yPos -= difference;
            }
        }
        else if(yPos < 280 and yPos > -40) yPos += (i+146);

        pipeTemp.setPosition(xPos, yPos);
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
sf::Sprite Pipes::getPipes(float speed, int index){
    float ySpeed = 0;

    if((index > 300 && index < 310) || (index < 115 && index > 110)) ySpeed = -(5 + ySpeed); //to make moving pipes
    else ySpeed = 0;

    pipes[index].move(speed, ySpeed);

    return pipes[index];
}

//fix the gravity/rise
//fix the scroll look make it smooth
//make the pipes actually exist
//fix the score incrementor and make it happen when bird goes past pipe not just at 250px
//change the bird sprite
//fix the back/scoreboard button switch
//if player exceeds 999 then create knew vector pipe set and and give different start pints
//force a gap between each pipe by detecting the one sprite to the other and a 50 px gap must be between
//make there be a detection for going over or under the pipe location bound the top and bottom
