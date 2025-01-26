#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>


class Text{
    public:
        Text(int WrapSize = 0, SDL_Rect DestRect = {0,0,0,0}, std::string Content=" ");
        ~Text();
        Text(const Text&) = delete;
        Text& operator=(const Text&) = delete;

        void Render(SDL_Surface* Surface);
        void SetFontSize(int NewSize){TTF_SetFontSize(mFont, NewSize);};
        std::string mContent;
        void SetDestinationRectangle(const SDL_Rect& Rect);
 
        SDL_Rect mDestRectangle;
        
        int mWrapSize;
        
    
    protected:

        TTF_Font* mFont;
        SDL_Surface* mTextSurface{nullptr};

        void CreateSurface(std::string Content);
        
        TTF_Font* LoadFont(int FontSize);
};