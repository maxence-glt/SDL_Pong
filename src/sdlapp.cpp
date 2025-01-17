#include <SDL2/SDL_image.h>
#include <iostream>

#include "sdlapp.hpp"
#include "ltexture.hpp"

SDLApp::SDLApp(std::string filepath, int width, int height): m_width(width), m_height(height), m_lscore(0), m_rscore(0), m_quit(false) {
    m_successInit = true;

    if	(SDL_Init( SDL_INIT_VIDEO) < 0)	{
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        m_successInit = false;
    } else {
        m_window = SDL_CreateWindow(filepath.c_str(),
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width,
                                    height,
                                    SDL_WINDOW_SHOWN);

        if (!m_window) {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            m_successInit = false;
        } else {
            // VSync on since I don't want to mess with FPS
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (!m_renderer) {
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                m_successInit = false;
            } else {
                if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                    std::cout << "SDL_image could not initialize! SDL_Error: " << IMG_GetError() << std::endl;
                    m_successInit = false;
                }
                if( TTF_Init() == -1 ) {
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        m_successInit = false;
                }
            }
        }

        if (m_successInit) std::cout << "Initialized\n";
    }
}

SDLApp::~SDLApp() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    IMG_Quit();
    SDL_Quit();
}

void SDLApp::splashLoop(LTexture *splash) {
    while (!m_quit) {
        SDL_Event e;
        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(m_renderer);
        splash->render(0, 0, m_renderer);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                m_quit = true;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                return;
            }
        }

        SDL_RenderPresent(m_renderer);
    }
}

void SDLApp::gameLoop() {
    while (!m_quit) {
        m_eventCallback();

        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(m_renderer);

        m_renderCallback();

        SDL_RenderPresent(m_renderer);
    }
}

void SDLApp::setEventCallback(std::function<void(void)> func) {
    m_eventCallback = func;
}

void SDLApp::setRenderCallback(std::function<void(void)> func) {
    m_renderCallback = func;
}
