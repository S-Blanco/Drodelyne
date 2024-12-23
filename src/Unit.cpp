#include <iostream>
#include <format>

#include "Events.h"

#include "Unit.h"

Unit::Unit(int x, int y, int Row, int Col):
    Rectangle{x,y,34,34}, mRow{Row}, mCol{Col}{}


void Unit::HandleEvent(const SDL_Event& E, int& MoveNbr){
    
    if (E.type == SDL_MOUSEMOTION){ HandleMouseMotion(E.motion); }
    if (E.type == SDL_MOUSEBUTTONDOWN) {HandleMouseClick(E.button, MoveNbr);}
    if (E.type == Events::HOVER_EVENT){mStatus=Empty;}
}

// Crappy name because it is the mouse that moved, not the Unit...
/*
 * Check if the mouse has moved since the last frame
 * The xrel and yrel variables have been repurposed
 * to store the position of the mouse during the previous frame
*/
bool Unit::HasMoved(const SDL_MouseMotionEvent& E){
    return (E.x == E.xrel && E.y == E.yrel);
}

void Unit::Render(SDL_Surface* Destination, bool* Moved){
    if      (mStatus==Player1) {SDL_BlitScaled(P1Unit(), nullptr, Destination, &mRect);}
    else if (mStatus==Player2) {SDL_BlitScaled(P2Unit(), nullptr, Destination, &mRect);}
    else if (mStatus==Forecast) {SDL_BlitScaled(ForecastUnit(), nullptr, Destination, &mRect);}
    else if (mStatus==Hover) {
        SDL_BlitScaled(HoverUnit(), nullptr, Destination, &mRect);
        SDL_Event Hovered{Events::HOVER_EVENT};
        Hovered.motion.x = mCol;
        Hovered.motion.y = mRow;
        Hovered.motion.xrel = mLastX;
        Hovered.motion.yrel = mLastY;
        SDL_PushEvent(&Hovered);
        *Moved = false;
        }
}


void Unit::HandleMouseMotion(const SDL_MouseMotionEvent& E){
    mLastX = E.x;
    mLastY = E.y;
    if (mStatus==Player1 || mStatus == Player2){return;}
    if (mStatus == Empty) { mStatus = Hover;}
    if (mStatus == Hover && E.type == Events::HOVER_EVENT) {mStatus = Empty;}
    
}

void Unit::HandleMouseClick(const SDL_MouseButtonEvent& E, int& MoveNbr){
    SDL_Event UnitPlayed{Events::UNIT_PLAYED};
    UnitPlayed.motion.x = mCol;
    UnitPlayed.motion.y = mRow;
    SDL_PushEvent(&UnitPlayed);
    (MoveNbr%2==0)? mStatus = Player1 : mStatus = Player2;
    ++MoveNbr;
}
