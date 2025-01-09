#include "Window.h"

Window::Window(){
    mSDLWindow = SDL_CreateWindow("Drodelyne",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                   600,300,
                                   0);
}

Window::Window(int Width, int Height){
    mSDLWindow = SDL_CreateWindow("Drodelyne",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                   Width, Height,
                                   SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
}

Window::~Window(){SDL_DestroyWindow(mSDLWindow);}

SDL_Surface* Window::GetSurface(){ return SDL_GetWindowSurface(mSDLWindow); }

void Window::Update() { SDL_UpdateWindowSurface(mSDLWindow); }

void Window::Render(){
    SDL_FillRect(GetSurface(),nullptr,
                SDL_MapRGB(GetSurface()->format,125,125,125));
}

SDL_Window* Window::GetWindow(){
    return mSDLWindow;
}