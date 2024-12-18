#pragma once

#include <format>


#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Text.h"
#include "../Button.h"
#include "../Scene.h"

class TutorialScreen : public Screen{
    public:
    TutorialScreen(std::string File, std::string Content, SDL_Rect DestRect);
    Image mBackground;
    Text mMessage;
    TextButton mPreviousButton{"<- Previous", {15,650, 350,60}}; // TODO: make this dynamic when multiple screen resolutions are available
    TextButton mNextButton{"Next ->", {1001,650, 350,60}};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};