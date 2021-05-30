#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <random>
#include <Math.h>
#include <SFML/Graphics.hpp>

struct Vec2
{
    float x;
    float y;
    float angle;
    float length;

    operator sf::Vector2f() const {return {x, y};}

    void setAngle(float a)
    {
        x = length * cos(degToRad(a));
        y = length * sin(degToRad(a));
    }
    
    void operator*= (sf::Vector2f vec2)
    {
        x *= vec2.x;
        y *= vec2.y;
    }

    void operator*= (float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    
    inline float degToRad(float deg)
    {
        return (deg * M_PI) / 180;
    }

    inline float radToDeg(float rad)
    {
        return (rad*180) / M_PI;
    }
};

class Ball : Paddle
{
public:
    Ball()
    {
        m_velocity.length = 10;
    }

    sf::RectangleShape generate()
    {
        m_ball.setFillColor(sf::Color::White);
        m_ball.setSize({16, 16});
        m_ball.setPosition(m_position);

        return m_ball;
    }

    void update(sf::Vector2f velocity, float dt)
    {
        m_position += velocity * dt * framemultiplier;
    }

    sf::Vector2f randomEmit(char direction)
    {
        emitangle = rand() % 25;
        if (rand() % 2)
        {
            emitangle *= -1;
        }

        if (direction == 'l')
        {
            emitangle += 180;
        }

        m_velocity.setAngle(emitangle);

        return sf::Vector2f(m_velocity);
    }

    sf::Vector2f ballBounce(sf::Vector2f paddlepos)
    {
        centreDistance = (m_position.y + 8) - (paddlepos.y + PADDLE_HEIGHT/2);

        normalisedDistance = centreDistance / (PADDLE_HEIGHT/2);
        
        if (paddlepos.x < 50) {bounceangle = normalisedDistance * MAXBOUNCEANGLE;}
        else {bounceangle = normalisedDistance * MAXBOUNCEANGLE + 180;}

        m_velocity.setAngle(bounceangle);

        return  sf::Vector2f(m_velocity);
    }

    void reset()
    {
        m_position = {500, 400};
    }

private:
    float degToRad(float deg)
    {
        return (deg * M_PI) / 180;
    }

    float radToDeg(float rad)
    {
        return (rad*180) / M_PI;
    }

    sf::RectangleShape m_ball;
    sf::Vector2f m_position={500, 400};

    float emitangle;
    Vec2 m_velocity;

    float framemultiplier = 60;

    float centreDistance;
    float normalisedDistance;
    float MAXBOUNCEANGLE = 45.f;
    float bounceangle;
};