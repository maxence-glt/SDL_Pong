#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>

class Ball {
public:
    Ball(int x, int y);

    constexpr int getPosX() const { return m_PosX; }
    constexpr int getPosY() const { return m_PosY; }
    constexpr bool getCrossLeft() const { return m_crossLeft; }
    constexpr bool getCrossRight() const { return m_crossRight; }

    static constexpr int getWidth() { return BALL_WIDTH; }
    static constexpr int getHeight() { return BALL_HEIGHT; }

    // void handleEvent(SDL_Event &event);
    void move(const SDL_Rect &left, const SDL_Rect &right);
    void reset();
private:
    static constexpr int BALL_WIDTH = 20;
    static constexpr int BALL_HEIGHT = 20;
    const int DEFAULT_X;
    const int DEFAULT_Y;

    bool m_crossLeft, m_crossRight;

    int m_BallVel = 30;
    int m_PosX, m_PosY;
    int m_VelX, m_VelY;
};

#endif
