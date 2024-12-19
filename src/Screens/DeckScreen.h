#pragma once

#include <format>


#include "Screen.h"
#include "../Button.h"
#include "../Events.h"
#include "../Image.h"
#include "../Scene.h"
#include "../Text.h"


class DeckScreen : public Screen{
    public:
    DeckScreen(std::string File, std::string Content, SDL_Rect DestRect);
    Image mBackground;
    Text mMessage;
    TextButton mBackButton;

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};