#pragma once

#include <SDL.h>
#include <string>
#include <format>
#include <iostream>

#include "Rectangle.h"
#include "Text.h"

class Button: public Rectangle{
    public:
        Button() = default;
        Button(int x, int y, int w, int h, SDL_Color Color = {0,255,0,255});
        void HandleEvent(const SDL_Event& E);
        bool mIsActive {true};
        bool mIsVisible {true};

    protected:
        void ResizeButton(int x, int y, int w, int h);
        virtual void HandleMouseEnter(){};
        virtual void HandleMouseExit(){};
        virtual void HandleLeftClick(){};
        virtual void HandleRightClick(){};
        

    private:
        void HandleMouseMotion(const SDL_MouseMotionEvent& E);
        void HandleMouseButton(const SDL_MouseButtonEvent& E);
};

class TextButton : public Button{
    public:
    TextButton() = default;
    TextButton(std::string Content, SDL_Rect DestRect, SDL_Color Color = {250,125,10});

    void PrintTextButtonInfo();
    void Render(SDL_Surface* Surface);

    Text mText;

};