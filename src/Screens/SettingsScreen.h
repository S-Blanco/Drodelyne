#pragma once

#include <format>


#include "Screen.h"
#include "../Events.h"
#include "../Image.h"
#include "../Button.h"

class SettingsScreen : public Screen{
    public:
    SettingsScreen(std::string File);
    Image mBackground;
    TextButton mStartButton{"Sound", {650,200,250,120}, {10,50,100}};
    TextButton mQuitButton{"Quit", {650,350,250,120}, {20,100,200}};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};