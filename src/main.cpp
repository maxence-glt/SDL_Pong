#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "SDL2/SDL_render.h"
#include "sdlapp.hpp"
#include "ltexture.hpp"
#include "main.hpp"

SDLApp *app = nullptr;
TTF_Font *font = nullptr;

SDL_Texture *fontTexture = nullptr;
LTexture *splashTexture = nullptr;
LTexture *ballTexture = nullptr;
LTexture *paddleTexture = nullptr;

Ball *ball = nullptr;
Paddle *leftPaddle = nullptr;
Paddle *rightPaddle = nullptr;

SDL_Color fontColor{255, 255, 255};

void handleEvents();
void handleRendering();

void init() {
    app = new SDLApp(gameVars.name, gameVars.SCREEN_WIDTH, gameVars.SCREEN_HEIGHT);
    SDL_Surface *icon = IMG_Load("../data/icon.png");
    SDL_SetWindowIcon(app->getAppWindow(), icon);

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

    font = TTF_OpenFont("../data/bit5x3.ttf", 30);

    for (int i = 0; i < gameVars.MAX_SCORE; i++) {
        std::string s = std::to_string(i);
        SDL_Surface* surfaceText = TTF_RenderText_Solid(font, s.c_str(), gameVars.FONT_COLOR);
        gameVars.numbers[i] = SDL_CreateTextureFromSurface(app->getRenderer(), surfaceText);
        SDL_FreeSurface(surfaceText);
    }
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
    if (ball->getCrossLeft()) {
        app->incRScore();
        ball->reset();
    } else if (ball->getCrossRight()) {
        app->incLScore();
        ball->reset();
    }

    leftPaddle->move();
    rightPaddle->move();
}

void handleRendering() {
    ballTexture->render(ball->getPosX(), ball->getPosY(), app->getRenderer());
    paddleTexture->render(leftPaddle->getPosX(), leftPaddle->getPosY(), app->getRenderer());
    paddleTexture->render(rightPaddle->getPosX(), rightPaddle->getPosY(), app->getRenderer());
    SDL_RenderCopy(app->getRenderer(), gameVars.numbers[app->getLScore()], NULL, &gameVars.LEFT_SCORE);
    SDL_RenderCopy(app->getRenderer(), gameVars.numbers[app->getRScore()], NULL, &gameVars.RIGHT_SCORE);
    std::cout << "Left: " << app->getLScore() << ' ' << "Right: " << app->getRScore() << '\n';
}

int main() {
    init();

    app->splashLoop(splashTexture);
    app->gameLoop();

    SDL_DestroyTexture(fontTexture);
    delete splashTexture;
    delete paddleTexture;
    delete ballTexture;

    delete app;

    return 0;
}
