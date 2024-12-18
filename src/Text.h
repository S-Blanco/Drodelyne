#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>


class Text{
    public:
        Text(int WrapSize = 0, std::string Content = " ");
        Text(int WrapSize, SDL_Rect DestRect, std::string Content=" ");
        ~Text();
        Text(const Text&) = delete;
        Text& operator=(const Text&) = delete;

        void Render(SDL_Surface* DestSurface);
        void SetFontSize(int NewSize){TTF_SetFontSize(mFont, NewSize);};
        std::string mContent;
        void SetDestinationRectangle(const SDL_Rect& Rect);
 
        SDL_Rect mDestRectangle{50,100,200,200};
        
        int mWrapSize;
        
    
    protected:

        TTF_Font* mFont;
        SDL_Surface* mTextSurface{nullptr};

        void CreateSurface(std::string Content);
        
        TTF_Font* LoadFont(int FontSize);
};