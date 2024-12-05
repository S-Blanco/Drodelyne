#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color Color)
    : Rect{x, y, w, h}, mColor{Color}{}

void Rectangle::Render(SDL_Surface* Surface) {
    SDL_FillRect(Surface,
                 &Rect,
                 SDL_MapRGB(Surface->format, mColor.r, mColor.g, mColor.b));
}


bool Rectangle::IsWithinBonds(int x, int y){
    if (x < Rect.x) return false;
    if (x > Rect.x + Rect.w) return false;
    if (y < Rect.y) return false;
    if (y > Rect.y + Rect.h) return false;
    return true;
}

void Rectangle::ChangeRectangle(int x, int y, int w, int h){
    Rect.x = x;
    Rect.y = y;
    Rect.w = w;
    Rect.h = h;
}

