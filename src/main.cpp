#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "sdlapp.hpp"
#include "ltexture.hpp"
#include "main.hpp"

SDLApp *app;
LTexture *splashTexture;
LTexture *ballTexture;
LTexture *paddleTexture;

Ball *ball;
Paddle *leftPaddle;
Paddle *rightPaddle;

void handleEvents();
void handleRendering();

void init() {
    app = new SDLApp(gameVars.name, gameVars.SCREEN_WIDTH, gameVars.SCREEN_HEIGHT);

    app->setEventCallback(handleEvents);
    app->setRenderCallback(handleRendering);

    ball = new Ball(gameVars.BALL_X_DEFAULT, gameVars.BALL_Y_DEFAULT);
    leftPaddle = new Paddle(gameVars.LPADDLE_X_DEFAULT, gameVars.PADDLE_Y_DEFAULT, false);
    rightPaddle = new Paddle(gameVars.RPADDLE_X_DEFAULT, gameVars.PADDLE_Y_DEFAULT, true);

    splashTexture = new LTexture("../data/splashback.png", app->getRenderer());
    splashTexture->setRect(gameVars.SCREEN_WIDTH, gameVars.SCREEN_HEIGHT);

    ballTexture = new LTexture("../data/ball.png", app->getRenderer());
    ballTexture->setRect(Ball::getWidth(), Ball::getHeight());

    paddleTexture = new LTexture("../data/paddle.png", app->getRenderer());
    paddleTexture->setRect(Paddle::getWidth(), Paddle::getHeight());
}

void handleEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            app->quitApp();
        leftPaddle->handleEvent(e);
        rightPaddle->handleEvent(e);
    }

    ball->move(leftPaddle->getRect(), rightPaddle->getRect());
    leftPaddle->move();
    rightPaddle->move();
}

void handleRendering() {
    ballTexture->render(ball->getPosX(), ball->getPosY(), app->getRenderer());
    paddleTexture->render(leftPaddle->getPosX(), leftPaddle->getPosY(), app->getRenderer());
    paddleTexture->render(rightPaddle->getPosX(), rightPaddle->getPosY(), app->getRenderer());
}

int main() {
    init();

    app->splashLoop(splashTexture);
    app->gameLoop();

    delete splashTexture;
    delete paddleTexture;
    delete ballTexture;
    delete app;

    return 0;
}
