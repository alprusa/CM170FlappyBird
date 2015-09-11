#include <SFML/Graphics.hpp>
#include <sstream>
#include "Bird.h"
#include "ButtonSprites.h"
#include "PipesGenerator.h"

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

    //set background audio
    /*sf::SoundBuffer buf3;
    if(!buf3.loadFromFile("bird.wav")) return -1;
    sf::Sound sndAudioE;
    sndAudio.setBuffer(buf);
    sndAudioE.play();*/

    //Font for Start Screen and such
    sf::Font stdFont;
    if(!stdFont.loadFromFile("OpenSans-Regular.ttf")) return 1;

    //scrolling background texture
    sf::Texture backgroundText;
    if(!backgroundText.loadFromFile("fbbackground.png"))
        return -1;
    backgroundText.setSmooth(true);
    backgroundText.setRepeated(true);

    //scrolling background sprite
    sf::Sprite backgroundS;
    backgroundS.setTexture(backgroundText);
    backgroundS.setPosition(0,0);
    backgroundS.setTextureRect(sf::IntRect(0,0,screenSize.x,screenSize.y));
    backgroundS.setScale(1.0f, (float)screenSize.y/backgroundText.getSize().y);

    // Load a texture to display for bird sprite
    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile("FlappyBird.png"))
        return EXIT_FAILURE;
    Bird bird(150,200,birdTexture); //the flappy bird sprite

    //Making the pipes load texture
    sf::Texture pipeTexture;
    if (!pipeTexture.loadFromFile("FlappyPipe.png"))
        return EXIT_FAILURE;
    Pipes pi(350, 400, pipeTexture);

    // Load a texture to display for play button sprite
    sf::Texture playTexture;
    if (!playTexture.loadFromFile("PlaySprite.png"))
        return EXIT_FAILURE;
    Buttons play(150,300,playTexture);

    // Load a texture to display for score button sprite
    sf::Texture scoreTexture;
    if (!scoreTexture.loadFromFile("ScoreSprite.png"))
        return EXIT_FAILURE;
    Buttons scoreS(350,300,scoreTexture);

    // Load a texture to display for back button sprite
    sf::Texture backTexture;
    if (!backTexture.loadFromFile("BackSprite.png"))
        return EXIT_FAILURE;
    Buttons backS(350,300,backTexture);

    // Load a texture to display for scoreBoard screen sprite
    sf::Texture scoreBoardTexture;
    if (!scoreBoardTexture.loadFromFile("ScoreBoard.png"))
        return EXIT_FAILURE;
    Buttons scoreBoard(220,150,scoreBoardTexture);

    // Load a texture to display for instructions screen sprite
    sf::Texture instTexture;
    if (!instTexture.loadFromFile("Instructions.png"))
        return EXIT_FAILURE;
    Buttons instructions(230,200,instTexture);

    //scrolling timer
    sf::Clock backgroundClockSet;
    float moveSpeed = 20000.0f; //scroll speed
    int backScrollX = 0; //view scroller x direction
    int gameState = 0; //for checking if playing the game at the menu or game over states
    int tempScore = 0; //score that will be incremented as the bird flys through pipes
    bool tap = true; //make it so player must tap to up arrow

	// Start the game loop
    while (window.isOpen())
    {
        backgroundClockSet.restart();
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
                //set bird to stationary position
                bird.rotateBird("forward");

                //Draw the backgroud Sprite
                window.draw(backgroundS);
                // Draw the sprite
                window.draw(bird.getBird());

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
                else if(scoreS.isPressed()){
                    gameState = 1;
                    scoreS.setPressed(false);
                    play.mouseClick(window);
                    scoreS.mouseClick(window);
                    backS.mouseClick(window);
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

                //set bird to stationary position
                bird.rotateBird("forward");

                //Draw the backgroud Sprite
                window.draw(backgroundS);
                // Draw the sprite
                window.draw(bird.getBird());

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
                else if(backS.isPressed()){
                    backS.setPressed(false);
                    play.mouseClick(window);
                    backS.mouseClick(window);
                    scoreS.mouseClick(window);
                    gameState = 0;
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
                //making the screen scroll by moving the background image horizontally
                if(backScrollX < screenSize.x && !bird.getLifeDetector()) {
                    backScrollX += (moveSpeed * backgroundClockSet.getElapsedTime().asSeconds());
                }
                else{
                    backScrollX = 0;
                }

                if(!bird.getLifeDetector()) bird.rotateBird("forward");
                else bird.rotateBird("dead");

                //set the position of the background texture on the moving sprite
                backgroundS.setTextureRect(sf::IntRect(backScrollX,0,screenSize.x,screenSize.y));

                //making the bird move up
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && tap && !bird.getLifeDetector()){
                    bird.moveBird(0,-60);
                    bird.rotateBird("up");
                    tap = false;
                }
                //temp gravity
                else {

                    bird.moveBird(0,5);
                }

                //make it so player must repeatedly tap up
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up && !bird.getLifeDetector()) {
                    tap = true;
                    bird.rotateBird("down");
                }

                //Draw the backgroud Sprite
                window.draw(backgroundS);

                //draw the pipes
                for(unsigned i = 0; i < pi.getSize(); ++i){
                    //determine if the bird collided with the pipes
                    if(bird.getBird().getGlobalBounds().intersects(pi.getPipes(0)[i].getGlobalBounds())) {
                        bird.moveBird(0,40);
                        bird.rotateBird("dead");
                    }

                    if(bird.getBird().getGlobalBounds().contains(pi.getPipesX(i),250.0f)) tempScore++; //set y to be the y point of the gap between pipes

                    if(pi.getPipesX(i) > -500 && pi.getPipesX(i) < 1000 && !bird.getLifeDetector()) //make it so that pipes off screen aren't draw
                        window.draw(pi.getPipes(-1000 * backgroundClockSet.getElapsedTime().asSeconds())[i]); //both moves the pipes and draws the new positions
                    else if(pi.getPipesX(i) > 1000 && !bird.getLifeDetector()) //still move pipes that are still needing to be drawn once the bird has "move forward" enough
                        pi.getPipes(-1000 * backgroundClockSet.getElapsedTime().asSeconds())[i];
                    else if(bird.getLifeDetector() && pi.getPipesX(i) > -500 && pi.getPipesX(i) < 1000) window.draw(pi.getPipes(0)[i]);
                }

                // Draw the sprite
                window.draw(bird.getBird());

                //to reset the game conditions needs to be changed
                if(bird.getBird().getPosition().y > screenSize.y){
                    backgroundS.setTextureRect(sf::IntRect(0,0,screenSize.x,screenSize.y));
                    pi.resetPipes(350, 400, pipeTexture);
                    bird.resetBird(150,200,birdTexture);
                    bird.setScore(tempScore);
                    tap = false;
                    backScrollX = 0;
                    gameState = 1;
                }

                break;
            }
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

