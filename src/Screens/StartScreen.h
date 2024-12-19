#pragma once

#include <format>

#include "../Scene.h"
#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Button.h"
#include "../Layout.h"

class StartScreen : public Screen{
    public:
    StartScreen(std::string File);
    Image mBackground;
    TextButton mStartButton{"Start",        {(Layout::ScreenWidth-250)/2,100,250,80}, {10,50,100}};
    TextButton mTutorialButton{"Tutorial",  {(Layout::ScreenWidth-250)/2,220,250,80}, {20,100,200}};
    TextButton mDeckButton{"Deck",          {(Layout::ScreenWidth-250)/2,340,250,80}, {30,150,255}};
    TextButton mSettings{"Settings",        {(Layout::ScreenWidth-250)/2,460,250,80}, {30,150,255}};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};