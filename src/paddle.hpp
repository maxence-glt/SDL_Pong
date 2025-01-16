#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "SDL2/SDL_keycode.h"
#include <SDL2/SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Paddle {
public:
    Paddle(int x, int y, bool right);

    constexpr int getPosX() const { return m_PosX; }
    constexpr int getPosY() const { return m_PosY; }
    static constexpr int getWidth() { return PADDLE_WIDTH; }
    static constexpr int getHeight() { return PADDLE_HEIGHT; }

    void handleEvent(SDL_Event &event);
    void move();
    void render();
private:
    static constexpr int PADDLE_WIDTH = 15;
    static constexpr int PADDLE_HEIGHT = 100;
    static constexpr int PADDLE_VEL = 30;

    // Left paddle is 'w' and 's', right is 'up' and 'down'
    SDL_KeyCode keyUp;
    SDL_KeyCode keyDown;

    int m_PosX, m_PosY;
    int m_VelY;
};

#endif
