#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color Color)
    : mRect{x, y, w, h}, mColor{Color}{}

void Rectangle::Render(SDL_Surface* Surface) {
    SDL_FillRect(Surface,
                 &mRect,
                 SDL_MapRGB(Surface->format, mColor.r, mColor.g, mColor.b));
}


bool Rectangle::IsWithinBounds(int x, int y){
    if (x < mRect.x) return false;
    if (x > mRect.x + mRect.w) return false;
    if (y < mRect.y) return false;
    if (y > mRect.y + mRect.h) return false;
    return true;
}

void Rectangle::ChangeRectangle(int x, int y, int w, int h){
    mRect.x = x;
    mRect.y = y;
    mRect.w = w;
    mRect.h = h;
}

void Rectangle::SetWidth(int NewWidth){
    mRect.w = NewWidth;
}

