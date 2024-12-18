#pragma once

#include <format>


#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Text.h"
#include "../Scene.h"

class TransitionScreen : public Screen{
    public:
    TransitionScreen(std::string File, std::string Content, SDL_Rect DestRect, Scenes TransitionTo);
    Image mBackground;
    Text mMessage;
    Scenes mTransitionTo;
    
    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
    
};