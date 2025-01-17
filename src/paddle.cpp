#include "paddle.hpp"
#include "main.hpp"

Paddle::Paddle(int x, int y, bool right): DEFAULT_X(x), DEFAULT_Y(y) {
    if (right) {
        keyUp = SDLK_w; keyDown = SDLK_s;
    } else {
        keyUp = SDLK_UP; keyDown = SDLK_DOWN;
    }

    reset();
}

void Paddle::handleEvent(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == keyUp) m_VelY -= PADDLE_VEL;
        else if (e.key.keysym.sym == keyDown) m_VelY += PADDLE_VEL;
    }

    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        if (e.key.keysym.sym == keyUp) m_VelY += PADDLE_VEL;
        else if (e.key.keysym.sym == keyDown) m_VelY -= PADDLE_VEL;
    }
}

constexpr void Paddle::move() {
    m_PosY += m_VelY;

    if((m_PosY < 0) || (m_PosY + PADDLE_HEIGHT > gameVars.SCREEN_HEIGHT))
        m_PosY -= m_VelY;
}

constexpr void Paddle::reset() {
    m_PosX = DEFAULT_X;
    m_PosY = DEFAULT_Y;
}
