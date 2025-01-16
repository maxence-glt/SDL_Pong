#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>

class SDLApp {
public:
    SDLApp(std::string filepath, int w, int h);
    ~SDLApp();

    void gameLoop();

    void setEventCallback(std::function<void(void)> func);
    void setRenderCallback(std::function<void(void)> func);
    inline void quitApp() { m_quit = true; };

    constexpr SDL_Renderer* getRenderer() const { return m_renderer; };
    constexpr bool getSuccessInit() const { return m_successInit; }
    constexpr SDL_Window* getAppWindow() const { return m_window; }

    constexpr int getScore() const { return m_score; }
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    bool m_successInit;
    bool m_quit;

    int m_width;
    int m_height;

    int m_score;

    std::function<void(void)> m_eventCallback;
    std::function<void(void)> m_renderCallback;
};

#endif
