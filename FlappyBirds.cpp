#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Bird.h"
#include "ButtonSprites.h"
#include "PipesGenerator.h"
#include "CollisionDetection.h"
#include "Background.h"

using namespace std;

void createText(float xPos, float yPos, bool rightAligned, sf::Font stdFont, sf::RenderWindow& window, string strText){
    sf::Text createdText;
    createdText.setFont(stdFont);
    createdText.setString(strText);
    createdText.setCharacterSize(30);
    createdText.setStyle(sf::Text::Bold);
    if(rightAligned)
        createdText.setOrigin(createdText.getLocalBounds().width,0);
    createdText.setColor(sf::Color::Red);
    createdText.setPosition(xPos, yPos);

    window.draw(createdText);
}

string convertInt(int value){
    stringstream convertStream;
    convertStream << value;
    string convertString;
    convertStream >> convertString;
    return convertString;
}

int main()
{
    //screen dimensions variable
    sf::Vector2i screenSize(640,600);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "SFML window");

    //set bird flap audio audio
    sf::SoundBuffer flapBuf;
    if(!flapBuf.loadFromFile("paper-sheet-pick-up-01.wav")) return -1;
    sf::Sound flapAudio;
    flapAudio.setBuffer(flapBuf);
    flapAudio.setLoop(false);

    //Font for Start Screen and such
    sf::Font stdFont;
    if(!stdFont.loadFromFile("OpenSans-Regular.ttf")) return 1;

    //background sprite object
    Background backG(0,0, screenSize);

    //the flappy bird sprite
    Bird bird(150,200);
    //set bird to stationary position
    bird.rotateBird("forward");

    //Making the pipes
    Pipes pi(650, 401);

    //sprite button to start playing
    Buttons play(150,300,"play");

    //sprite button to check scores
    Buttons scoreS(350,300,"score");

    //sprite button to go back from score menu
    Buttons backS(350,300,"back");

    //sprite for the score board menu screen
    Buttons scoreBoard(220,150,"scoreBoard");

    //sprite for the instructions screen
    Buttons instructions(230,200,"instructions");

    //scrolling timer
    sf::Clock buttonToggleTimer; //for correct toggle for back/score buttons
    float moveSpeed = 4.0f; //scroll speed
    int gameState = 0; //for checking if playing the game at the menu or game over states
    int tempScore = 0; //score that will be incremented as the bird flys through pipes
    bool tap = true; //make it so player must tap to up arrow

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        switch(gameState){
            case 0:{
                //Draw the backgroud Sprite
                window.draw(backG.getBackground());

                // Draw the sprite
                window.draw(bird.getBird());
                bird.animate();

                //determine if player is clicking on play sprite
                if(play.isPressed()) {
                    window.draw(instructions.getButton());
                    //draw text
                    createText(250, 100, false, stdFont, window, "Get Ready"); //title text

                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                        gameState = 2;
                        tempScore = 0;
                        play.setPressed(false);
                    }
                }
                else if(scoreS.isPressed() && buttonToggleTimer.getElapsedTime().asSeconds() * 1000 > 100){
                    gameState = 1;
                    scoreS.setPressed(false);
                    play.mouseClick(window);
                    scoreS.mouseClick(window);
                    backS.mouseClick(window);
                    buttonToggleTimer.restart();
                }
                else{
                    //draw text
                    //title text
                    createText(250, 100, false, stdFont, window, "Flappy Bird");
                    //draw button sprites
                    window.draw(play.getButton());
                    window.draw(scoreS.getButton());

                    play.mouseClick(window);
                    scoreS.mouseClick(window);
                }

                break;
            }
            case 1:{
                //convert score to string for temp
                string scoreStr = convertInt(tempScore);

                //for best score
                string scoreBestStr = convertInt(bird.getScore());

                //Draw the backgroud Sprite
                window.draw(backG.getBackground());

                // Draw the sprite
                window.draw(bird.getBird());
                bird.animate();

                //determine if player is clicking on play sprite
                if(play.isPressed()) {
                    window.draw(instructions.getButton());
                    createText(250, 100, false, stdFont, window, "Get Ready"); //title text

                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
                        gameState = 2;
                        tempScore = 0;
                        play.setPressed(false);
                    }
                }
                else if(backS.isPressed() && buttonToggleTimer.getElapsedTime().asSeconds() * 1000 > 100){
                    backS.setPressed(false);
                    play.mouseClick(window);
                    backS.mouseClick(window);
                    scoreS.mouseClick(window);
                    gameState = 0;
                    buttonToggleTimer.restart();
                }
                else{
                    //draw scoreBoard
                    window.draw(scoreBoard.getButton());
                    //draw text
                    createText(250, 100, false, stdFont, window, "Game Over"); //title text
                    createText(425, 175, true, stdFont, window, scoreStr); //text for score
                    createText(425, 225, true, stdFont, window, scoreBestStr); //text for best score
                    //draw button sprites
                    window.draw(play.getButton());
                    window.draw(backS.getButton());

                    play.mouseClick(window);
                    backS.mouseClick(window);
                }

                break;
            }
            default:{
                //move background
                backG.move(bird.getLifeDetector());

                if(bird.getLifeDetector())
                    bird.moveBird(false, "dead");
                //making the bird move up
                else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && tap && !bird.getLifeDetector() && bird.getY() > 0){
                    bird.moveBird(true, "up");
                    flapAudio.play();
                    tap = false;
                }
                //temp gravity
                else if(bird.getY() <= screenSize.y && tap && !bird.getLifeDetector()){
                    bird.moveBird(false, "down");
                }

                //make it so player must repeatedly tap up
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up && !bird.getLifeDetector() && !tap) tap = true;

                //Draw the backgroud Sprite
                window.draw(backG.getBackground());

                //draw the pipes
                for(unsigned i = 0; i < pi.getSize(); ++i){
                    //determine if the bird collided with the pipes using a tempPipe for proper sizing
                    sf::Sprite tempPipe;
                    tempPipe.setScale(pi.getWidth(), pi.getHeight());

                    //change the positioning for the rotated pipes
                    if(i % 2 == 0) tempPipe.setPosition(pi.getPipesX(i) - pi.getWidth(), pi.getPipesY(i) - pi.getHeight());
                    else tempPipe.setPosition(pi.getPipesX(i), pi.getPipesY(i));

                    if(collisionCheck(bird.getBird(), bird.getWidth(), bird.getHeight(), tempPipe, pi.getWidth(), pi.getHeight()) && !bird.getLifeDetector())
                        bird.rotateBird("dead"); //fix collision then game it good enough for submission

                    //get the center y position for where bird needs to hit
                    sf::Vector2f yPasses(0,0);
                    int tempWidth = 0;
                    int tempHeight = 0;

                    //for if the pipe faces up
                    if(pi.getRotation(i) == 0) {
                        yPasses.x = pi.getPipesY(i) - 10;
                        yPasses.y = 0;
                        tempPipe.setPosition(pi.getPipesX(i), yPasses.y);
                        tempWidth = pi.getWidth();
                        tempHeight = yPasses.x;
                    }
                    else { //for the pipe that faces down
                        yPasses.x = pi.getPipesY(i) + 10;
                        yPasses.y = screenSize.y;
                        tempPipe.setPosition(pi.getPipesX(i), yPasses.x);
                        tempWidth = pi.getWidth();
                        tempHeight = yPasses.y;
                    }

                    //to set the score when player passes the pipes
                    if(collisionCheck(bird.getBird(), bird.getWidth(), bird.getHeight(), tempPipe, tempWidth, tempHeight) && !pi.getPassedStats(i) &&
                            !bird.getLifeDetector() && i % 2 == 0) {
                        pi.setPassedStats(i);
                        tempScore++; //set y to be the y point of the gap between pipes
                    }

                    //make it so that pipes off screen aren't drawn
                    if(pi.getPipesX(i) > -500 && pi.getPipesX(i) < 1000 && !bird.getLifeDetector()){
                        window.draw(pi.getPipes(-moveSpeed,i)); //both moves the pipes and draws the new positions
                        //window.draw(pi.getPipes(0,i).y);//draw bottom pipe so there are two pipes per score zone
                    }
                    //still move pipes that are still needing to be drawn once the bird has "move forward" enough
                    else if(pi.getPipesX(i) >= 1000 && !bird.getLifeDetector())
                        pi.getPipes(-moveSpeed,i);
                    //bird is dead andd for transition
                    else {
                        window.draw(pi.getPipes(0,i));
                        //window.draw(pi.getPipes(0,i).y);
                    }
                }

                // Draw the sprite
                window.draw(bird.getBird());
                bird.animate();

                //draw score
                //convert score to string for temp
                string scoreStr = convertInt(tempScore);
                createText(300,50, true, stdFont, window, scoreStr); //text for score

                //to reset the game conditions may need to be changed
                if(bird.getBird().getPosition().y >= screenSize.y){
                    backG.reset();
                    pi.resetPipes(650, 401);
                    bird.resetBird(150,200);
                    bird.setScore(tempScore);
                    bird.rotateBird("forward");
                    tap = false;
                    gameState = 1;
                }

                //to generate more pipes when player gets farther
                //if(tempScore % 1000 == 0) pi.resetPipes(pi.getPipesX(tempScore)+50, 575, pipeTexture);

                break;
            }
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

