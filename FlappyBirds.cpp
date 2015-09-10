#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "ButtonSprites.h"

using namespace std;

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

    //Font for Start Screen and such
    sf::Font stdFont;
    if(!stdFont.loadFromFile("OpenSans-Regular.ttf")) return 1;

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
    bool tap = true; //make it so player must tap to up arrow
    bool playerStart = false;

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
                //title text
                sf::Text titleText;
                titleText.setFont(stdFont);
                titleText.setString("Flappy Bird");
                titleText.setCharacterSize(30);
                titleText.setStyle(sf::Text::Bold);
                titleText.setColor(sf::Color::Red);
                titleText.setPosition(250, 100);

                //set bird to stationary position
                bird.rotateBird("forward");

                //Draw the backgroud Sprite
                window.draw(backgroundS);
                // Draw the sprite
                window.draw(bird.getBird());

                //determine if player is clicking on play sprite
                if(play.isPressed()) {
                    window.draw(instructions.getButton());
                    playerStart = true;
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) gameState = 2;
                }
                else if(scoreS.isPressed()){
                    gameState = 1;
                    scoreS.setActivated(false);
                    play.mouseClick(window);
                    scoreS.mouseClick(window);
                    backS.mouseClick(window);
                }
                else{
                    //draw text
                    window.draw(titleText);
                    //draw button sprites
                    window.draw(play.getButton());
                    window.draw(scoreS.getButton());

                    play.mouseClick(window);
                    scoreS.mouseClick(window);
                }

                //set to be activated so click doesn't trigger when screen changes
                play.setActivated(true);
                scoreS.setActivated(true);
                backS.setActivated(false);

                break;
            }
            case 1:{
                //title text
                sf::Text gameOverText;
                gameOverText.setFont(stdFont);
                gameOverText.setString("Game Over");
                gameOverText.setCharacterSize(30);
                gameOverText.setStyle(sf::Text::Bold);
                gameOverText.setColor(sf::Color::Red);
                gameOverText.setPosition(250, 100);

                //set bird to stationary position
                bird.rotateBird("forward");

                //Draw the backgroud Sprite
                window.draw(backgroundS);
                // Draw the sprite
                window.draw(bird.getBird());

                //determine if player is clicking on play sprite
                if(play.isPressed()) {
                    window.draw(instructions.getButton());
                    playerStart = true;
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) gameState = 2;
                }
                else if(backS.isPressed()){
                    backS.setActivated(false);
                    play.mouseClick(window);
                    backS.mouseClick(window);
                    scoreS.mouseClick(window);
                    gameState = 0;
                }
                else{
                    //draw scoreBoard
                    window.draw(scoreBoard.getButton());
                    //draw text
                    window.draw(gameOverText);
                    //draw button sprites
                    window.draw(play.getButton());
                    window.draw(backS.getButton());

                    play.mouseClick(window);
                    backS.mouseClick(window);
                }

                //set to be activated so click doesn't trigger when screen changes
                play.setActivated(true);
                scoreS.setActivated(false);
                backS.setActivated(true);

                break;
            }
            default:{
                //making the screen scroll by moving the background image horizontally
                if(backScrollX < screenSize.x) {
                    backScrollX += (moveSpeed * backgroundClockSet.getElapsedTime().asSeconds());
                }
                else{
                    backScrollX = 0;
                }
                bird.rotateBird("forward");

                //set the position of the background texture on the moving sprite
                backgroundS.setTextureRect(sf::IntRect(backScrollX,0,screenSize.x,screenSize.y));

                //making the bird move up
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && tap){
                    bird.moveBird(0,-60);
                    bird.rotateBird("up");
                    tap = false;
                }
                //temp gravity
                else {

                    bird.moveBird(0,5);
                }

                //make it so player must repeatedly tap up
                if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) {
                    tap = true;
                    bird.rotateBird("down");
                }

                //Draw the backgroud Sprite
                window.draw(backgroundS);

                // Draw the sprite
                window.draw(bird.getBird());

                break;
            }
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

