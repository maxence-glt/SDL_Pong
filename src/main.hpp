#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>

#include "ball.hpp"
#include "paddle.hpp"

const struct GameVars {
    const std::string name = "SDLTutorial";
    constexpr static int SCREEN_WIDTH = 1280;
    constexpr static int SCREEN_HEIGHT = 800;

    const int BALL_X_DEFAULT = SCREEN_WIDTH / 2 - Ball::getWidth() / 2;
    const int BALL_Y_DEFAULT = SCREEN_HEIGHT / 2 - Ball::getHeight() / 2;


    const int RPADDLE_X_DEFAULT = 10;
    const int LPADDLE_X_DEFAULT = SCREEN_WIDTH - (10 + Paddle::getWidth());

    const int PADDLE_Y_DEFAULT = (SCREEN_HEIGHT / 2) - (Paddle::getHeight() / 2);
} gameVars;





#endif
