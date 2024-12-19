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
    TutorialScreen(std::string File[8], std::string Content[8], SDL_Rect DestRect[8]);
    Image mBackground[8];
    int mSlideIndex{0};
    Text mMessage[8];
    TextButton mPreviousButton{"<- Previous", {710,700, 300,60}, {82,178,170}}; // TODO: make this dynamic when multiple screen resolutions are available
    TextButton mNextButton{"Next ->", {1060,700, 300,60}, {82,178,170}};

    int mLastClickTime{0};
    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};