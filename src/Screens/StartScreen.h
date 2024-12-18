#pragma once

#include <format>

#include "../Scene.h"
#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Button.h"

class StartScreen : public Screen{
    public:
    StartScreen(std::string File);
    Image mBackground;
    TextButton mStartButton{"Start", {650,200,250,120}, {10,50,100}};
    TextButton mTutorialButton{"Tutorial", {650,350,250,120}, {20,100,200}};
    TextButton mDeckButton{"Deck", {650,500,250,120}, {30,150,255}};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};