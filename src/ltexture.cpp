#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "ltexture.hpp"
#include "SDL2/SDL_rect.h"

LTexture::LTexture(std::string filepath, SDL_Renderer *renderer) {
    if (!(loadFromFile(filepath, renderer)))
        std::cout << "Image failed to load: " << IMG_GetError() << std::endl;
}

LTexture::~LTexture() {
    SDL_DestroyTexture(m_texture);
}

bool LTexture::loadFromFile(std::string filepath, SDL_Renderer *renderer) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(filepath.c_str());

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    m_width = loadedSurface->w;
    m_height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    m_texture = newTexture;
    return m_texture != NULL;
}

void LTexture::render(int x, int y, SDL_Renderer *renderer) {
    SDL_Rect renderQuad{x, y, m_width, m_height};

    SDL_RenderCopy(renderer, m_texture, NULL, &renderQuad);
}
