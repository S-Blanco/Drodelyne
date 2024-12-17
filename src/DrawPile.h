#pragma once

#include <string>

#include "Image.h"
#include "Text.h"
#include "Layout.h"


class DrawPile{
    public:
        DrawPile() = default;
        DrawPile(std::string CardBackground, int DeckSize);
        void Render(SDL_Surface* Surface);
        void SetCurrentIndex(int idx);
    
    private:
        Image mCardBackground;
        Text mDeckSizeDisplay;
        int mDeckSize;
};