#include "PipesGenerator.h"

//return array of pipe sprites in generated function
vector<sf::Sprite> pipeGen(int xPos, int yPos, sf::Texture& pi){
    vector<sf::Sprite> pipes;
    sf::FloatRect prevBoundingBox;

    //create the vector sprite set
    for(int i = 0; i < 999; i++) {
        sf::Sprite pipeTemp;
        pipeTemp.setTexture(pi);
        if(i % 3 == 0 || i % 5 == 0) pipeTemp.rotate(180);

        //to setup the different x positions
        if(i % 5 != 0){
            if(xPos % 3 == 0) xPos += (20+xPos/10); //set next yPos
            else if(xPos % 4 == 0) xPos += (5+xPos/10);
            else if(xPos % 5 == 0) xPos += (1+xPos/10);
            else if(xPos % 6 == 0) xPos += (12+xPos/10);
            else if(xPos > 300 && i < 400) xPos += (7+xPos/10);
            else if(xPos > 400 && i < 550) xPos += (18+xPos/10);
            else xPos += (25+xPos/10);
        }

        //make it so pipes so above one another/have different heights

        //to setup the diferent y positions
        if(pipeTemp.getRotation() == 0){
            if(yPos % 3 == 0) yPos = (300+yPos/10);
            else if(yPos % 4 == 0) yPos = (500+yPos/10); //set next yPos
            else if(yPos % 5 == 0) yPos = (400+yPos/10);
            else if(yPos % 6 == 0) yPos = (350+yPos/10);
            else if(yPos % 7 == 0) yPos = (465+yPos/10);
            else if(yPos % 8 == 0) yPos = (321+yPos/10);
            else if(yPos % 9 == 0) yPos = (444+yPos/10);
            else yPos = (389+yPos/10);
        }
        else{
            if(yPos % 3 == 0) yPos += (20+yPos/10);
            else if(yPos % 4 == 0) yPos = (280+yPos/10); //set next yPos
            else if(yPos % 5 == 0) yPos = (146+yPos/10);
            else if(yPos % 6 == 0) yPos = (40+yPos/10);
            else if(yPos % 7 == 0) yPos = (100+yPos/10);
            else if(yPos % 8 == 0) yPos = (70+yPos/10);
            else if(yPos % 9 == 0) yPos = (180+yPos/10);
            else yPos = (120+yPos/10);
        }

        //so that the pipe won't go to low
        if(yPos >= 600 && pipeTemp.getRotation() == 0) {
            float difference = yPos - 600;
            yPos -= difference;
        }

        //so that the pipe does not float
        else if(yPos <= 360 && pipeTemp.getRotation() == 0){
            float difference = yPos - 360;
            yPos += difference;
        }

        //so the pipe doesn't go too high
        if(yPos <= -280 && pipeTemp.getRotation() == 180){
            float difference = 280 + yPos;
            yPos -= difference;
            yPos = -yPos;
        }

        //so the pipe doesn't exceed the length of the pipe
        else if(yPos >= 280  && pipeTemp.getRotation() == 180){
            float difference = yPos - 280;
            yPos -= difference;
        }

        //force variance in pipes
        xPos++;
        yPos++;

        pipeTemp.setPosition(xPos, yPos);

        //check if pipes on above one another
        if(i != 0 && pipeTemp.getGlobalBounds().intersects(pipes[i-1].getGlobalBounds())){
            //for if intersection is on x axis
            if(pipeTemp.getGlobalBounds().left < pipes[i-1].getGlobalBounds().left || pipeTemp.getGlobalBounds().left > pipes[i-1].getGlobalBounds().left){
                xPos += 60;
                pipeTemp.move(+60,0);
            }
            //for if intersection is on y axis
            else if(pipeTemp.getRotation() == 0 && pipeTemp.getGlobalBounds().top == pipes[i-1].getGlobalBounds().top){
                yPos += 50;
                pipeTemp.move(0,50);
            }
            else{
                yPos -= 50;
                pipeTemp.move(0,-50);
            }
        }

        pipes.push_back(pipeTemp);

        prevBoundingBox = pipeTemp.getGlobalBounds(); //prevent collisions with past pipes
    }

    return pipes;
}

//call generator here and just have the private object be the pipes sprite array not single sprite
Pipes::Pipes(int xPos, int yPos, sf::Texture& pi){
    timeElapsed = 0;
    pipes = pipeGen(xPos, yPos, pi);
}

void Pipes::resetPipes(int xPos, int yPos, sf::Texture& pi){
    pipes = pipeGen(xPos, yPos, pi);
}

//get the pipes so that they cab be drawn to the screen
sf::Sprite Pipes::getPipes(float speed, int index){
    float ySpeed = 0;//-0.5f;

    /*if((index > 3 && index < 10) || (index < 115 && index > 110)) {
        //to make moving pipes
        cout<<speed<<endl;
        if(speed < -2){
            ySpeed = -ySpeed;
            timeElapsed = 0;
        }
    }
    else ySpeed = 0;*/

    pipes[index].move(speed, ySpeed);

    return pipes[index];
}

//fix the gravity/rise
//fix the scroll look make it smooth
//fix the score incrementor and make it happen when bird goes past pipe not just at 250px
//change the bird sprite
//fix the back/scoreboard button switch
//if player exceeds 999 then create knew vector pipe set and and give different start pints
//force a gap between each pipe by detecting the one sprite to the other and a 50 px gap must be between
