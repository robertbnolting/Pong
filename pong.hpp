#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "paddle.hpp"
#include "ball.hpp"

class Pong
{
public:
    Pong()
    {
        paddle_left_o = Paddle('l');
        paddle_right_o = Paddle('r');

        paddle_left = paddle_left_o.getPaddle();
        paddle_right = paddle_right_o.getPaddle();  
    }

    void player1move(int k, float dt)
    {
        if (k == 1)
        {
            paddle_left_o.moveUp(paddle_left, dt);
        }
        else if (k == -1)
        {
            paddle_left_o.moveDown(paddle_left, dt);
        }
    }

    void player2move(int k, float dt)
    {
        if (k == 1)
        {
            paddle_right_o.moveUp(paddle_right, dt);
        }
        else if (k == -1)
        {
            paddle_right_o.moveDown(paddle_right, dt);
        }
    }

    void computermove(float dt)
    {
        if (m_ball.getPosition().x < 500)
        {
            if (paddle_left.getPosition().y < m_ball.getPosition().y)
            {
                paddle_left_o.moveDown(paddle_left, dt);
            }
            else if (paddle_left.getPosition().y > m_ball.getPosition().y)
            {
                paddle_left_o.moveUp(paddle_left, dt);
            }
        }
    }

    std::vector <sf::RectangleShape> getPaddles()
    {
        return {paddle_left, paddle_right};
    }

    sf::RectangleShape getBall(float dt)
    {
        m_ball = ball.generate();
        if (reset)
        {
            rcollisioncounter = 0;
            lcollisioncounter = 0;
            ballv = ball.randomEmit(emitside);
            reset = false;
        }
        
        ball.update(ballv, dt);

        checkBallPos();
        checkPaddleCollision();
        checkBorderCollision();

        return m_ball;
    }

    inline void checkPaddleCollision()
    {
        if (paddle_left_o.registerCollision(m_ball))
        {
            rcollisioncounter = 0;
            lcollisioncounter += 1;
            if (lcollisioncounter == 1)
            {
                ballv = ball.ballBounce(paddle_left.getPosition());
            }
        }
        else if (paddle_right_o.registerCollision(m_ball))
        {
            lcollisioncounter = 0;
            rcollisioncounter += 1;
            if (rcollisioncounter == 1)
            {
                ballv = ball.ballBounce(paddle_right.getPosition());
            }
        }
    }

    inline void checkBorderCollision()
    {
        if (m_ball.getPosition().y<=5 || m_ball.getPosition().y>=795)
        {
            ccollisioncounter += 1;
            if (ccollisioncounter == 1)
            {
                ballv.y *= -1.f;
            }
        }
        else 
        {
            ccollisioncounter = 0;
        }
    }

    inline void checkBallPos()
    {
        if (m_ball.getPosition().x < 0)
        {
            ball.reset();
            emitside = 'l';
            reset = true;
            player2score += 1;
        }
        else if (m_ball.getPosition().x > 1000)
        {
            ball.reset();
            emitside = 'r';
            reset = true;
            player1score += 1;
        }
    }

    sf::Text getScore(int side)
    {
        font.loadFromFile("AtariSmall.ttf");
        
        scoredisplay.setFont(font);
        scoredisplay.setFillColor(sf::Color::White);
        scoredisplay.setCharacterSize(150);
        
        scoretext[0] = scoredisplay;
        scoretext[1] = scoredisplay;

        scoretext[0].setPosition({300, -25});
        scoretext[0].setString(toString(player1score));

        scoretext[1].setPosition({600, -25});
        scoretext[1].setString(toString(player2score));

        if (side) {return scoretext[1];}
        else {return scoretext[0];}
    }

    std::string toString(int num)
    {
        char numstr[10];
        sprintf(numstr, "%i", num);
        return numstr;
    }

private:
    Paddle paddle_right_o;
    Paddle paddle_left_o;

    sf::RectangleShape paddle_left;
    sf::RectangleShape paddle_right;

    Ball ball;
    sf::RectangleShape m_ball;
    sf::Vector2f ballv={-10.f, 0.f};

    int lcollisioncounter=0;
    int rcollisioncounter=0;
    int ccollisioncounter=0;

    int player1score=0;
    int player2score=0;
    bool reset=false;
    char emitside;

    sf::Text scoretext[2];
    sf::Text scoredisplay;
    sf::Font font;
};