#pragma once

#include <SDL.h>

class Screen{
    public:
    virtual void Render(SDL_Surface* Surface) = 0;
    virtual void Update() = 0;
    virtual void HandleEvent(const SDL_Event& E) = 0;
    virtual ~Screen() = default;
};