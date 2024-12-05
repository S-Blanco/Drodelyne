#pragma once

#include <SDL.h>

class Window {
    public:
        Window();
        Window(int Width, int Height);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        SDL_Surface* GetSurface();
        void Update();
        void Render();

    private:
        SDL_Window* mSDLWindow;
};