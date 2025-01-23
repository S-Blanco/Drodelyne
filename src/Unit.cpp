#include <iostream>
#include <format>

#include "Events.h"

#include "Unit.h"

Unit::Unit(int x, int y, int Row, int Col):
    Rectangle{x,y,34,34}, mRow{Row}, mCol{Col}{}


void Unit::HandleEvent(const SDL_Event& E, int& MoveNbr){
    if (E.type == SDL_MOUSEBUTTONDOWN) {HandleMouseClick(E.button, MoveNbr);}
}


void Unit::Render(SDL_Surface* Destination){
    if (mDEBUG_UseSprite){
        if      (mStatus==Player1) {SDL_BlitScaled(P1Unit(), nullptr, Destination, &mRect);}
        else if (mStatus==Player2) {SDL_BlitScaled(P2Unit(), nullptr, Destination, &mRect);}
        else if (mStatus==Forecast) {SDL_BlitScaled(ForecastUnit(), nullptr, Destination, &mRect);}
    } else{
        SDL_FillRect(Destination,
                     &mRect,
                     SDL_MapRGB(Destination->format, mColor.r, mColor.g, mColor.b));
    }
    
}

void Unit::HandleMouseClick(const SDL_MouseButtonEvent& E, int& CurrentMove){
    SDL_Event UnitPlayed{Events::UNIT_PLAYED};
    UnitPlayed.motion.x = mCol;
    UnitPlayed.motion.y = mRow;
    SDL_PushEvent(&UnitPlayed);
    (CurrentMove%2==0)? mStatus = Player1 : mStatus = Player2;
}
