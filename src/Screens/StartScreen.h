#pragma once

#include <format>

#include "Screen.h"
#include "../Button.h"
#include "../Events.h"
#include "../Global.h"
#include "../Image.h"
#include "../Layout.h"
#include "../Scene.h"
#include "../Text.h"

class StartScreen : public Screen{
    public:
    StartScreen(std::string File);
    Image mBackground;
        
    Text mGameTitle{800, {50,95,800,200}, "Drodelyne"};
    TextButton mStartButton{"Start",        {(2*Layout::ScreenWidth)/3,250,250,80}, Colors::BlueButton};
    TextButton mTutorialButton{"Tutorial",  {(2*Layout::ScreenWidth)/3,370,250,80}, Colors::BlueButton};
    TextButton mSettings{"Settings",        {(2*Layout::ScreenWidth)/3,490,250,80}, Colors::BlueButton};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};