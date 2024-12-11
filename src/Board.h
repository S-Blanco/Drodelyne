#pragma once
#include "Settings.h"
#include "Global.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

#include "Unit.h"
#include "Image.h"

/*
 * Handles the display of units and the legality of moves
*/
class Board {
    public:
        Board();
        Board(int UpperX, int UpperY, int ImgWidth=675, int ImgHeight=675);
        
        
        void HandleEvent(const SDL_Event& E);
        void Render(SDL_Surface* Surface);
        bool IsIntersectionValid(int X, int Y);
        void CheckHover();

        

    private:
        int mCellWidth{35}; //Note: box sprite = 33px but 2 px for edges
        int mCellHeight{35};
        int mUpperX{25};
        int mUpperY{54};
        int mEdgeWidth{5};
        static const int mSize{19};
        bool mHasMoved{true};

        int mLastCol{0};
        int mLastRow{0};

        bool IsMoveLegal(int row, int col);
        void Forecaster(int CardID, bool WasSacrificed=false);
        void ForecastResetter();

        Status mBoardState[mSize][mSize];
        
        Status mBoardForecast[GameSetting::HandSize][mSize][mSize];
        
        Status mPlayerThisTurn;
        Status mOpponent;
        Unit board[mSize][mSize];
        Image mEmptyBoard;
        int mMoveNbr{0};
};