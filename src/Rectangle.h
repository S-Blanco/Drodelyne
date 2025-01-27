#pragma once

#include <SDL.h>


class Rectangle{
    public:
        Rectangle(int x, int y, int w, int h, SDL_Color Color={0,0,0,255});
        Rectangle()=default;
        bool IsWithinBounds(int x, int y);
        void SetColor(SDL_Color C){mColor = C;};
        SDL_Color GetColor(){return mColor;};
        void ChangeRectangle(int x, int y, int w, int h);
        void SetWidth(int NewWidth);

        virtual void Render(SDL_Surface* Surface);
        virtual void HandleEvent(const SDL_Event& E){}

        const int GetLeftX(){return mRect.x;}
        const int GetTopY(){return mRect.y;}
        const int GetRightX(){return mRect.x + mRect.w;}
        const int GetBottomY(){return mRect.y + mRect.h;}
        const int GetW(){return mRect.w;}
        const int GetH(){return mRect.h;}
        
    
        void SetX(int NewX) {mRect.x = NewX;}
        void SetY(int NewY) {mRect.y = NewY;}
        void SetW(int NewW) {mRect.w = NewW;}
        void SetH(int NewH) {mRect.h = NewH;}

        SDL_Rect mRect {0, 0, 0, 0}; // Should be protected but first need to fix DrawRectangle.Render
        
    protected:
        
        SDL_Color mColor {0, 0, 0, 0};
        
        
};