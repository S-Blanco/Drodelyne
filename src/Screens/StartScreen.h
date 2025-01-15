#pragma once

#include <format>

#include "../Scene.h"
#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Button.h"
#include "../Layout.h"
#include "../Text.h"

class StartScreen : public Screen{
    public:
    StartScreen(std::string File);
    Image mBackground;
        
    Text mGameTitle{800, {50,95,800,200}, "Drodelyne"};
    TextButton mStartButton{"Start",        {(2*Layout::ScreenWidth)/3,200,250,80}, {58,137,220}};
    TextButton mTutorialButton{"Tutorial",  {(2*Layout::ScreenWidth)/3,320,250,80}, {58,137,220}};
    TextButton mDeckButton{"Deck",          {(2*Layout::ScreenWidth)/3,440,250,80}, {58,137,220}};
    TextButton mSettings{"Settings",        {(2*Layout::ScreenWidth)/3,560,250,80}, {58,137,220}};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};