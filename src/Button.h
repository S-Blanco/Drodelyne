#pragma once

#include <SDL.h>

#include "Rectangle.h"

class Button: public Rectangle{
    public:
        Button() = default;
        Button(int x, int y, int w, int h, SDL_Color Color = {0,255,0,255});
        void HandleEvent(const SDL_Event& E);
        bool mIsActive {true};

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

class QuitButton : public Button{
    public:
        QuitButton(int x, int y, int w, int h);
        
    protected:
        void HandleLeftClick();
};