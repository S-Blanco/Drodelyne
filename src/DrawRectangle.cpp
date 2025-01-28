#include "DrawRectangle.h"
#include <iostream>
#include <format>

DrawRectangle::DrawRectangle(int OuterRect_x, int OuterRect_y, int OuterRect_w, int OuterRect_h,
                             int BorderSize, int Index, SDL_Color InsideColor, SDL_Color OutsideColor)
:Zone{{OuterRect_x, OuterRect_y, OuterRect_w, OuterRect_h}, BorderSize, Index, InsideColor, OutsideColor}, mIndex{Index}
{}


bool DrawRectangle::IsWithinBounds(int x, int y){
    if (Zone.GetLeftX() <= x && Zone.GetRightX() >= x
        && Zone.GetTopY() <= y && Zone.GetBottomY() >= y){
            return true;
        }
    return false;
}

void DrawRectangle::Render(SDL_Surface* Surface){
    Zone.Render(Surface);
}

void DrawRectangle::HandleEvent(SDL_Event E){
    if (E.type == SDL_MOUSEBUTTONDOWN
        && E.button.button == SDL_BUTTON_RIGHT){
            if(IsWithinBounds(E.button.x, E.button.y)){
                SDL_Event Delete{Events::DELETE_ZONE};
                Delete.motion.x = mIndex;
                SDL_PushEvent(&Delete);
            }
    } else if (E.type == SDL_MOUSEBUTTONDOWN && E.button.button == SDL_BUTTON_LEFT){
        IsPressed = true;
        if (E.button.x >= Layout::GobanTopX && E.button.x <= Layout::GobanTopX + Layout::GobanWidth
         && E.button.y >= Layout::GobanTopY && E.button.y <= Layout::GobanTopY + Layout::GobanHeight){
            x0 = Layout::EdgeWidth
               + Layout::GobanTopX
               + ((E.button.x - Layout::GobanTopX) / Layout::CellWidth) * Layout::CellWidth;
            y0 = Layout::EdgeWidth
               + Layout::GobanTopY
               + ((E.button.y - Layout::GobanTopY) / Layout::CellHeight) * Layout::CellHeight;
            x1 = E.button.x;
            y1 = E.button.y;
            Zone.SetX(E.button.x);
            Zone.SetY(E.button.y);
            Zone.ComputeInnerBox();
        }
        
    } else if(E.type == SDL_MOUSEMOTION && IsPressed){
        if (E.button.x > Layout::GobanTopX && E.button.x < Layout::GobanTopX + Layout::GobanWidth){
            x1 = Layout::EdgeWidth
               + Layout::GobanTopX
               + ((E.button.x - Layout::GobanTopX) / Layout::CellWidth) * Layout::CellWidth;
        }
        if (E.button.y > Layout::GobanTopY && E.button.y < Layout::GobanTopY + Layout::GobanHeight){
            y1 = Layout::EdgeWidth
               + Layout::GobanTopY
               + ((E.button.y - Layout::GobanTopY) / Layout::CellHeight) * Layout::CellHeight;
        }
        if (x0 < x1){
            Zone.SetX(x0);
            Zone.SetW(x1 - x0);
        } else{
            Zone.SetX(x1);
            Zone.SetW(x0 - x1);
        }
        if (y0 < y1){
            Zone.SetY(y0);
            Zone.SetH(y1 - y0);
        } else{
            Zone.SetY(y1);
            Zone.SetH(y0 - y1);
        }
        Zone.ComputeInnerBox();
    } else if (E.type == SDL_MOUSEBUTTONUP){
        IsPressed = false;
        mScore = (Zone.GetW() / Layout::CellWidth) * (Zone.GetH() / Layout::CellHeight);
    }
}