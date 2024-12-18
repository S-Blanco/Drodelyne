#pragma once

#include <format>


#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Text.h"
#include "../Button.h"

class DeckScreen : public Screen{
    public:
    DeckScreen(std::string File, std::string Content, SDL_Rect DestRect);
    Image mBackground;
    Text mMessage;

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};