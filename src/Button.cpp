#include "Button.h"

Button::Button(int x, int y, int w, int h, SDL_Color Color)
    : Rectangle(x, y, w, h, Color){}

void Button::ResizeButton(int x, int y, int w, int h){
        Rect.x = x;
        Rect.y = y;
        Rect.w = w;
        Rect.h = h;
};

void Button::HandleEvent(const SDL_Event& E){
    if (!mIsActive) return;
    if (E.type == SDL_MOUSEMOTION) HandleMouseMotion(E.motion);
    if (E.type == SDL_MOUSEBUTTONDOWN) HandleMouseButton(E.button);
};

void Button::HandleMouseMotion(const SDL_MouseMotionEvent& E){
    if (IsWithinBonds(E.x, E.y)){
        HandleMouseEnter();
    }else {
        HandleMouseExit();
    }
}

void Button::HandleMouseButton(const SDL_MouseButtonEvent& E){
    if (IsWithinBonds(E.x, E.y)){
        if (E.button == SDL_BUTTON_LEFT) HandleLeftClick();
        else if (E.button == SDL_BUTTON_RIGHT) HandleRightClick();
    }
}  


QuitButton::QuitButton(int x, int y, int w, int h)
    :Button{x, y, w, h, SDL_Color{255, 126, 126, 255}}{}
        
void QuitButton::HandleLeftClick(){
    SDL_Event Quit{SDL_QUIT};
    SDL_PushEvent(&Quit);
}