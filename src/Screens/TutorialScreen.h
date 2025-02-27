#pragma once

#include "Screen.h"
#include "../Button.h"
#include "../Events.h"
#include "../Global.h"
#include "../Image.h"
#include "../Scene.h"
#include "../Text.h"

class TutorialScreen : public Screen{
    public:
    TutorialScreen(std::string File[8], std::string Content[8], SDL_Rect DestRect[8]);
    Image mBackground[8];
    int mSlideIndex{0};
    Text mMessage[8];
    TextButton mPreviousButton{"<- Previous", {710,700, 300,60},  Colors::BlueButton}; // TODO: make this dynamic when multiple screen resolutions are available
    TextButton mNextButton{"Next ->",         {1060,700, 300,60}, Colors::BlueButton};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(const SDL_Event& E);
};