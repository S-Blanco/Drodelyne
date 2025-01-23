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

        void HandleEvent(const SDL_Event& E, int& mCurrentMove);
        void Render(SDL_Surface* Surface);
        static const int mSize{19};

        

    private:
        int mCellWidth{35}; //Note: box sprite = 33px but 2 px for edges
        int mCellHeight{35};
        int mUpperX{25};
        int mUpperY{54};
        int mEdgeWidth{5};

        bool IsMoveLegal(int row, int col);
        void PlaceUnit(int row, int col, Status Player);
        void Forecaster(int CardID, bool WasSacrificed=false);
        void ForecastResetter();
        int GetGroupLiberties(int (&arr)[19][19], int GroupId);
        void RemoveGroup(int GroupId);
        void ReplaceGroupIndex(int (&arr)[19][19], int OldIndex, int NewIndex);

        /*  
            Status mBoardForecast[GameSetting::HandSize][mSize][mSize];
            Curently unused
            Will be used later to keep tab of every places accessible with the current hand.
            If no space is accessible, ony then do we allow card sacrifice
        */
        
        Status mPlayerThisTurn;
        Status mOpponent;
        Unit board[mSize][mSize];
        
        std::vector<int> GroupIndex;
        std::vector<int> GroupLiberties;
        int mCurrentGroupIndex{1};
        int mTemp_GroupsOnBoard[mSize][mSize]{0}; // used to check if a move is valid before actually changing the Group numbering
        int mGroupsOnBoard[mSize][mSize]{0};
        Image mEmptyBoard;
};