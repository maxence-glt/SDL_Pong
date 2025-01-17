#include <SDL2/SDL.h>
#include <iostream>

#include "ball.hpp"
#include "main.hpp"

unsigned long randomNum();

Ball::Ball(int x, int y): DEFAULT_X(x), DEFAULT_Y(y) {
    reset();
}

/*
void Ball::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: m_VelY -= BALL_VEL; break;
            case SDLK_DOWN: m_VelY += BALL_VEL; break;
            case SDLK_LEFT: m_VelX -= BALL_VEL; break;
            case SDLK_RIGHT: m_VelX += BALL_VEL; break;
        }
    }

    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: m_VelY += BALL_VEL; break;
            case SDLK_DOWN: m_VelY -= BALL_VEL; break;
            case SDLK_LEFT: m_VelX += BALL_VEL; break;
            case SDLK_RIGHT: m_VelX -= BALL_VEL; break;
        }
    }
}
*/

void Ball::move(const SDL_Rect &left, const SDL_Rect &right) {
    if(m_PosX < 0 || m_PosX + BALL_WIDTH >= gameVars.SCREEN_WIDTH)
        reset();

    if (m_PosY <= 0 || m_PosY >= gameVars.SCREEN_HEIGHT - BALL_HEIGHT)
        m_VelY *= -1;

    m_PosY += m_VelY;

    const SDL_Rect temp{m_PosX, m_PosY, BALL_WIDTH, BALL_HEIGHT};
    if (SDL_HasIntersection(&temp, &left) || SDL_HasIntersection(&temp, &right)) {
        m_VelX *= -1;
    }

    m_PosX += m_VelX;
}

void Ball::reset() {
    m_PosX = DEFAULT_X;
    m_PosY = DEFAULT_Y;
    m_VelY = randomNum() % 5;
    m_VelX = randomNum() % 20;

    if (m_VelY < 1) m_VelY = 1;
    if (m_VelX < 10) m_VelX = 10;
}

// Random Number Generator
// https://stackoverflow.com/questions/1046714/what-is-a-good-random-number-generator-for-a-game
static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long randomNum() {          //period 2^96-1
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}
