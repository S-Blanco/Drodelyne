#pragma once

#include "Rectangle.h"

class Box{
    public:

    Box(SDL_Rect OuterRect, int BorderSize, int Index, SDL_Color InsideColor, SDL_Color OutsideColor);
    void HandleEvent(const SDL_Event& Event);
    void Render(SDL_Surface* Surface);

    const int GetLeftX(){return mOuterBox.x;}
    const int GetTopY(){return mOuterBox.y;}
    const int GetRightX(){return mOuterBox.x + mOuterBox.w;}
    const int GetBottomY(){return mOuterBox.y + mOuterBox.h;}
    const int GetW(){return mOuterBox.w;}
    const int GetH(){return mOuterBox.h;}
    const int GetIndex(){return mIndex;}
    
    void ComputeInnerBox();

    void SetX(int NewX) {mOuterBox.x = NewX;}
    void SetY(int NewY) {mOuterBox.y = NewY;}
    void SetW(int NewW) {mOuterBox.w = NewW;}
    void SetH(int NewH) {mOuterBox.h = NewH;}
    
    protected:
    int mIndex;
    int mBorderSize;
    SDL_Rect mInnerBox;
    SDL_Rect mOuterBox;
    SDL_Color mInsideColor;
    SDL_Color mOutsideColor;

};