#ifndef LTEXTURE_HPP
#define LTEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using RGB = Uint8;

// LTexture == Loaded Texture
class LTexture {
public:
    LTexture(const std::string &filepath, SDL_Renderer *renderer);
    ~LTexture();

    bool loadFromFile(const std::string &filepath, SDL_Renderer *renderer);
    void render(int x, int y, SDL_Renderer *renderer);

    constexpr void setRect(const int &w, const int &h) { 
        m_width = w; m_height = h;
    }
private:
    inline const SDL_Rect getRect() const { return m_rect; }

    SDL_Rect m_rect;
    SDL_Texture* m_texture;

    int m_width, m_height;
};

#endif
