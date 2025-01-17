#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>

#include "ltexture.hpp"

class SDLApp {
public:
    SDLApp(std::string filepath, int w, int h);
    ~SDLApp();

    void splashLoop(LTexture*);
    void gameLoop();

    void setEventCallback(std::function<void(void)> func);
    void setRenderCallback(std::function<void(void)> func);
    inline void quitApp() { m_quit = true; };

    constexpr SDL_Renderer* getRenderer() const { return m_renderer; };
    constexpr bool getSuccessInit() const { return m_successInit; }
    constexpr SDL_Window* getAppWindow() const { return m_window; }
    constexpr bool getQuit() const { return m_quit; }

    constexpr int getLScore() const { return m_lscore; }
    constexpr int getRScore() const { return m_rscore; }
    void incLScore() { m_lscore++; }
    void incRScore() { m_rscore++; }
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    bool m_successInit;
    bool m_quit;

    int m_width, m_height;
    int m_lscore, m_rscore;

    std::function<void(void)> m_eventCallback;
    std::function<void(void)> m_renderCallback;
};

#endif
