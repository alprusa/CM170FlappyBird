#include "PipesGenerator.h"
#include "CollisionDetection.h"

int determineYPos(int yPos, sf::Sprite& pipeTemp){
        //so that the pipe won't go to low
        if(yPos >= 600 && pipeTemp.getRotation() == 0) {
            int difference = yPos - 600;
            yPos -= difference;
        }

        //so that the pipe does not float
        else if(yPos <= 340 && pipeTemp.getRotation() == 0){
            int difference = yPos - 340;
            yPos += difference;
        }

        //so the pipe doesn't go too high
        if(yPos <= -280 && pipeTemp.getRotation() == 180){
            int difference = 280 + yPos;
            yPos -= difference;
            yPos = -yPos;
        }

        //so the pipe doesn't exceed the length of the pipe
        else if(yPos >= 280  && pipeTemp.getRotation() == 180){
            int difference = yPos - 280;
            yPos -= difference;
        }

        return yPos;
}

//return array of pipe sprites in generated function
vector<sf::Sprite> pipeGen(int xPos, int yPos, sf::Texture& pi){
    vector<sf::Sprite> pipes;
    int width = pi.getSize().x;
    int height = pi.getSize().y;

    //create the vector sprite set
    for(int i = 0; i < 2000; i++) {
        sf::Sprite pipeTemp;
        pipeTemp.setTexture(pi);
        if(i % 2 == 0) pipeTemp.rotate(180);

        //to setup the different x positions
        if(i % 2 == 0){
            if(xPos % 3 == 0) xPos += (120+xPos/10); //set next yPos
            else if(xPos % 4 == 0 && i >200) xPos += (50+xPos/10);
            else if(xPos % 5 == 0 && i > 400) xPos += (40+xPos/10);
            else if(xPos % 6 == 0) xPos += (212+xPos/10);
            else if(xPos % 7 == 0 && i > 100) xPos += (70+xPos/10);
            else if(xPos % 8 == 0) xPos += (180+xPos/10);
            else xPos += (240+xPos/10);
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

        //correct yPos
        yPos = determineYPos(yPos, pipeTemp);

        //force variance in pipes
        if(i % 2 == 0) xPos++;
        yPos++;

        pipeTemp.setPosition(xPos, yPos);

        //check if pipes are above one another
        sf::Sprite tempPipeCollision;
        tempPipeCollision.setTexture(pi);
        tempPipeCollision.setPosition(xPos, yPos);

        //change the positioning for the rotated pipes
        if(i > 2 && i % 2 == 0) tempPipeCollision.setPosition(pipes[i-2].getPosition().x - width, pipes[i-2].getPosition().y - height);
        else if(i > 2 && i % 2 != 0) tempPipeCollision.setPosition(pipes[i-2].getPosition().x, pipes[i-2].getPosition().y);

        if(i > 2 && i % 2 == 0 && collisionCheck(pipeTemp, width, height, tempPipeCollision, width, height)){
            //for if intersection is on x axis
            //if(pipeTemp.getGlobalBounds().left < pipes[i-2].getGlobalBounds().left || pipeTemp.getGlobalBounds().left > pipes[i-2].getGlobalBounds().left){
                xPos += 160;
                pipeTemp.move(160,0);
            //}
        }

        //for if intersection is on y axis correct y spacing
        float pipeDistance = 0;
        if(i != 0) pipeDistance = pipeTemp.getPosition().y - pipes[i-1].getPosition().y;
        if(pipeTemp.getRotation() == 0 && pipeDistance < 60){
            //if(pipeTemp.getGlobalBounds().top == pipes[i-1].getGlobalBounds().top)
            cout<<"stuff"<<endl;
            yPos += 50;
            float tempYpos = yPos;
            //determine yPos
            yPos = determineYPos(yPos, pipeTemp);
            float diff = 50;
            if(tempYpos != yPos) diff = tempYpos - yPos;
            pipeTemp.move(0,diff);
        }

        pipes.push_back(pipeTemp);
    }

    return pipes;
}

//call generator here and just have the private object be the pipes sprite array not single sprite
Pipes::Pipes(int xPos, int yPos){
    //load texture
    if (!pipeTexture.loadFromFile("FlappyPipe.png"))
        return;

    width = pipeTexture.getSize().x;
    height = pipeTexture.getSize().y;

    pipes = pipeGen(xPos, yPos, pipeTexture);

    for(int i = 0; i < pipes.size()/2; i++) passedThrough.push_back(false); //so that values are not counted twice
}

void Pipes::resetPipes(int xPos, int yPos){
    pipes = pipeGen(xPos, yPos, pipeTexture);

    for(int i = 0; i < pipes.size()/2; i++) passedThrough[i] = false; //so that values are not counted twice
}

//get the pipes so that they cab be drawn to the screen
sf::Sprite Pipes::getPipes(float speed, int index){
    float ySpeed = 0;//-0.5f;

    //to make moving pipes
    /*if((index > 3 && index < 10) || (index < 115 && index > 110)) {
        //so that the pipe won't go to low
        if(index % 2 != 0 && pipes[index].getPosition().y <= 360) {
            ySpeed = -ySpeed;
        }

        if(index % 2 != 0 && pipes[index].getPosition().y >= 600) {
            ySpeed = -ySpeed;
        }
    }
    else ySpeed = 0;*/


    pipes[index].move(speed, ySpeed);

    return pipes[index];
}

//fix the scroll look make it smooth
//fix moving pipes section
//get moving pipes working
//setOrigin for the sprites
