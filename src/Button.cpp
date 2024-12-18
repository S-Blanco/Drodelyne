#include "Button.h"

Button::Button(int x, int y, int w, int h, SDL_Color Color)
    : Rectangle(x, y, w, h, Color){}

void Button::ResizeButton(int x, int y, int w, int h){
        mRect.x = x;
        mRect.y = y;
        mRect.w = w;
        mRect.h = h;
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

bool Button::IsWithinBounds(int x, int y){
    return !(   x < GetLeftX()
             || x > GetRightX()
             || y < GetTopY()
             || y > GetBottomY());
}


TextButton::TextButton(std::string Content, SDL_Rect DestRect, SDL_Color Color)
    :Button(DestRect.x, DestRect.y, DestRect.w, DestRect.h, Color),mText{DestRect.w, DestRect, Content}{}

void TextButton::PrintTextButtonInfo(){
    std::cout << "Text Button info :\n";
    std::cout << std::format("Content: {}\n" ,mText.mContent);
    std::cout << std::format("Position (x, y): {} , {}\n", mRect.x, mRect.y);
    std::cout << std::format("Width - Height: {} - {}\n", mRect.w, mRect.h);
    std::cout << std::format("Color: {} {} {}\n", mColor.r, mColor.g, mColor.b);
}

void TextButton::Render(SDL_Surface* Surface){
    Button::Render(Surface);
    mText.Render(Surface);
}