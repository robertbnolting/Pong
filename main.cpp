#include <iostream>
#include <SFML/Graphics.hpp>

#include "pong.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000.f, 800.f), "Pong");
    window.setFramerateLimit(60);

    int player1_input=0;
    int player2_input=0;
    bool computercontrol=false;

    bool start=false;

    Pong pong;
    std::vector <sf::RectangleShape> paddles;

    sf::Texture backgroundtex;
    backgroundtex.loadFromFile("background.png");
    sf::Sprite background(backgroundtex);
    
    sf::RectangleShape paddle;
    sf::RectangleShape ball;

    sf::Text scoredisplay[2];

    sf::Event event;

    sf::Clock clock;
    float dt;

    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed)
            {
                window.close();
            }
            
            else if (event.type == event.KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    player1_input = 1;
                    start = true;
                }

                else if (event.key.code == sf::Keyboard::S)
                {
                    player1_input = -1;
                    start = true;
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    player2_input = 1;
                }

                else if (event.key.code == sf::Keyboard::Down)
                {
                    player2_input = -1;
                }

                else if (event.key.code == sf::Keyboard::C)
                {
                    computercontrol = true;
                }
            }

            else if (event.type == event.KeyReleased)
            {
                player1_input = 0;
                player2_input = 0;
            }
        }

        dt = clock.restart().asSeconds();

        paddles = pong.getPaddles();
        scoredisplay[0] = pong.getScore(0);
        scoredisplay[1] = pong.getScore(1);

        window.draw(background);

        if (computercontrol)
        {
            player1_input = 0;
            pong.computermove(dt);
        }

        if (player1_input)
        {
            pong.player1move(player1_input, dt);
        }

        else if (player2_input)
        {
            pong.player2move(player2_input, dt);
        }

        if (start)
        {
            ball = pong.getBall(dt);
        }
        
        for (int i=0; i<paddles.size(); i++)
        {
            window.draw(paddles[i]);
        }
    
        window.draw(ball);

        for (int i=0; i<2; i++)
        {
            window.draw(scoredisplay[i]);
        }

        window.display();
    }

    return 0;
}