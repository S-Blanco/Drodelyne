#define DEBUG
#pragma once

#include <SDL.h>

#include "Settings.h"

#include "Rectangle.h"
#include "Image.h"

enum Status {Empty, Player1 , Player2, Forecast};

class Unit : public Rectangle{
    public:
        Unit(int x, int y, int Row, int Col);

        Unit()=default;

        void HandleEvent(const SDL_Event& E, int& TurnNbr);
        
        void SetColor(SDL_Color NewColor){mColor = NewColor;};
        void SetCol(int Col){mCol = Col;};
        void SetRow(int Row){mRow = Row;};

        Status mStatus{Empty};
        bool mDEBUG_UseSprite{true}; // only used to debug

        void Render(SDL_Surface* Destination);

        void HandleMouseMotion(const SDL_MouseMotionEvent& E);
        void HandleMouseClick(const SDL_MouseButtonEvent& E, int& TurnNbr);


    private:
        int mCol{0}; // Column number in the goban's 2D array 
        int mRow{0}; // Row number in the goban's 2D array 
        
        static SDL_Surface* P1Unit() {
            static SDL_Surface* P1Unit = IMG_Load("../assets/img/units/P1_unit.png");
            #ifdef DEBUG
                if (!P1Unit){ std::cout << "[Error] Could not load P1Unit" << std::endl; }
            #endif
            return P1Unit; 
        };
        static SDL_Surface* P2Unit() {
            static SDL_Surface* P2Unit = IMG_Load("../assets/img/units/P2_unit.png");
            #ifdef DEBUG
                if (!P2Unit){ std::cout << "[Error] Could not load P2Unit" << std::endl; }
            #endif
            return P2Unit; 
        };

        static SDL_Surface* ForecastUnit() {
            static SDL_Surface* ForecastUnit = IMG_Load("../assets/img/units/forecast_move.png");
            #ifdef DEBUG
                if (!ForecastUnit){ std::cout << "[Error] Could not load ForecastUnit" << std::endl; }
            #endif
            return ForecastUnit; 
        };
};