#include "Box.h"


Box::Box(SDL_Rect OuterRect, int BorderSize, int Index, SDL_Color InsideColor, SDL_Color OutsideColor)
:mOuterBox{OuterRect}, mBorderSize{BorderSize},
 mInsideColor{InsideColor}, mOutsideColor{OutsideColor},
 mInnerBox{OuterRect.x + BorderSize, OuterRect.y + BorderSize, OuterRect.w - 2 * BorderSize, OuterRect.h - 2 * BorderSize}
{}

void Box::ComputeInnerBox(){
    mInnerBox.x = mOuterBox.x + mBorderSize;
    mInnerBox.y = mOuterBox.y + mBorderSize;
    mInnerBox.w = mOuterBox.w - 2 * mBorderSize;
    mInnerBox.h = mOuterBox.h - 2 * mBorderSize;
}

void Box::HandleEvent(const SDL_Event& Event){
    
}
void Box::Render(SDL_Surface* Surface){
    
    SDL_FillRect(Surface, &mOuterBox, SDL_MapRGB(Surface->format, mOutsideColor.r, mOutsideColor.g, mOutsideColor.b));
    SDL_FillRect(Surface, &mInnerBox, SDL_MapRGB(Surface->format, mInsideColor.r, mInsideColor.g, mInsideColor.b));

}
    