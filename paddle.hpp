#pragma once

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

class Paddle
{
public:
    float PADDLE_HEIGHT=100;
    float PADDLE_WIDTH=15;

    Paddle() = default;

    Paddle(char c)
    {
        side = c;
        m_paddle.setFillColor(sf::Color::White);
        m_paddle.setSize({PADDLE_WIDTH, PADDLE_HEIGHT});
        c == 'l' ? m_paddle.setPosition(0, 350) : m_paddle.setPosition({1000-PADDLE_WIDTH, 350});
    }

    sf::RectangleShape getPaddle() const
    {
        return m_paddle;
    }

    void setPosition(sf::Vector2f pos)
    {
        m_paddle.setPosition(pos);
    }

    sf::Vector2f getPosition() const
    {
        return m_paddle.getPosition();
    }

    void moveUp(sf::RectangleShape& paddleref, float dt)
    {
        if (paddleref.getPosition().y - v > - 7)
        {
            paddleref.move(0, -v*dt * framemultiplier);
            m_paddle.move(0, -v*dt * framemultiplier);
        }
    }

    void moveDown(sf::RectangleShape& paddleref, float dt)
    {
        if (paddleref.getPosition().y + v < 705)
        {
            paddleref.move(0, v*dt * framemultiplier);
            m_paddle.move(0, v*dt * framemultiplier);
        }
    }

    bool registerCollision(sf::RectangleShape& ball)
    {
        if (side == 'l')
        {
            sf::Vector2f paddleCentre = {m_paddle.getPosition().x+PADDLE_WIDTH/2, m_paddle.getPosition().y+PADDLE_HEIGHT/2};
            sf::Vector2f ballCentre = {ball.getPosition().x+8, ball.getPosition().y+8};

            float x_offset = abs(ballCentre.x - paddleCentre.x);
            float y_offset = abs(ballCentre.y - paddleCentre.y) - errcorrect;

            if (sqrt(x_offset*x_offset + y_offset*y_offset) < 40)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        else
        {
            sf::Vector2f paddleCentre = {m_paddle.getPosition().x+PADDLE_WIDTH/2, m_paddle.getPosition().y+PADDLE_HEIGHT/2};
            sf::Vector2f ballCentre = {ball.getPosition().x+8, ball.getPosition().y+8};

            float x_offset = abs(ballCentre.x - paddleCentre.x);
            float y_offset = abs(ballCentre.y - paddleCentre.y) - errcorrect;

            if (sqrt(x_offset*x_offset + y_offset*y_offset) < 40)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

private:
    char side;

    sf::RectangleShape m_paddle;

    float v=20;
    float framemultiplier = 60;
    float errcorrect = 15.f;
};