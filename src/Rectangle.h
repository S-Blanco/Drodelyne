#pragma once

#include <SDL.h>


class Rectangle{
    public:
        Rectangle(int x, int y, int w, int h, SDL_Color Color={0,0,0,255});
        Rectangle()=default;
        bool IsWithinBonds(int x, int y);
        void SetColor(SDL_Color C){mColor = C;};
        void ChangeRectangle(int x, int y, int w, int h);

        virtual void Render(SDL_Surface* Surface);
        virtual void HandleEvent(const SDL_Event& E){}

        const int GetLeftX(){return Rect.x;}
        const int GetTopY(){return Rect.y;}
        const int GetRightX(){return Rect.x + Rect.w;}
        const int GetBottomY(){return Rect.y + Rect.h;}
        
    protected:
        SDL_Rect    Rect   {0, 0, 0, 0};
        SDL_Color   mColor {0, 0, 0, 0};
        
        
};