#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>


class Text{
    public:
        Text(std::string Content=" ");
        ~Text();
        Text(const Text&) = delete;
        Text& operator=(const Text&) = delete;

        void Render(SDL_Surface* DestSurface);
        void SetFontSize(int NewSize){TTF_SetFontSize(mFont, NewSize);};
        std::string mContent;
    
    protected:

        Text(int FontSize);
    
        TTF_Font* mFont;
        SDL_Surface* mTextSurface{nullptr};
        SDL_Rect mDestRectangle{50,100,200,200};

        void CreateSurface(std::string Content);
        
        TTF_Font* LoadFont(int FontSize);
};