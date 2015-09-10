#include <SFML/Graphics.hpp>
#include "Bird.h"

using namespace std;

int main()
{
    sf::Vector2i screenSize(640,600);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "SFML window");

    //set background audio
    /*sf::SoundBuffer buf3;
    if(!buf3.loadFromFile("bird.wav")) return -1;
    sf::Sound sndAudioE;
    sndAudio.setBuffer(buf);
    sndAudioE.play();*/

    //scrolling background sprite
    sf::Texture backgroundText;
    if(!backgroundText.loadFromFile("fbbackground.png"))
        return -1;
    backgroundText.setRepeated(true);

    sf::Sprite backgroundS;
    backgroundS.setTexture(backgroundText);
    backgroundS.setPosition(0,0);
    //backgroundS.setTextureRect(sf::IntRect(0,0,screenSize.x,screenSize.y));
    backgroundS.setScale(1.0f, (float)screenSize.y/backgroundText.getSize().y);

    //scrolling timer
    sf::Clock backgroundClockSet;
    float moveSpeed = 10000.0f;

    //view scroller
    int backScrollX = 0;
    sf::View backView;
    backView.reset(sf::FloatRect(0,0,screenSize.x,screenSize.y));
    backView.setViewport(sf::FloatRect(0,0,1.0f,1.0f));

    sf::Vector2f birdPosition(0,0);

    // Load a sprite to display
    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile("FlappyBird.png"))
        return EXIT_FAILURE;

    Bird bird(150,200,birdTexture);

    //Font for Start Screen and such
    sf::Font stdFont;
    if(!stdFont.loadFromFile("OpenSans-Regular.ttf")) return 1;

    string textString = "Play\nLeaderboard\nOptions";

    sf::Text optionText;
    optionText.setFont(stdFont);
    optionText.setString(textString);
    optionText.setCharacterSize(30);
    optionText.setStyle(sf::Text::Bold);
    optionText.setColor(sf::Color::Red);
    optionText.setPosition(100, 200);

    int gameState = 1;

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
            case 0:
                //start text
                window.draw(optionText);
                window.setView(window.getDefaultView());
                break;
            default:
                birdPosition.x = bird.getX() + 10 - (screenSize.x / 2);
                birdPosition.y = bird.getY() + 10 - (screenSize.y / 2);

                if(birdPosition.x < 0) birdPosition.x = 0;
                if(birdPosition.y < 0) birdPosition.y = 0;

                backView.reset(sf::FloatRect(birdPosition.x, birdPosition.y, screenSize.x, screenSize.y));

                if(backScrollX > screenSize.x) {
                    backView.reset(sf::FloatRect(0,0,screenSize.x,screenSize.y));
                    //birdPosition.x = 0;
                    backScrollX = 0;
                }
                backScrollX += birdPosition.x;

                window.setView(backView);

                //temporary way to make the screen scroll
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    bird.moveBird(moveSpeed * backgroundClockSet.getElapsedTime().asSeconds(),0);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    bird.moveBird(-moveSpeed * backgroundClockSet.getElapsedTime().asSeconds(),0);

                window.draw(backgroundS);
               // window.draw(backgroundRect);

                // Draw the sprite
                window.draw(bird.getBird());
                break;
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

