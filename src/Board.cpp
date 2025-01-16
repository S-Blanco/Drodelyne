#include "Board.h"
#include "Events.h"

# ifdef DEBUG
    #include <format>
#endif


Board::Board():mPlayerThisTurn{Player1},mOpponent{Player2}{}

Board::Board(int UpperX, int UpperY, int ImgWidth, int ImgHeight)
    :mUpperX{UpperX}, mUpperY{UpperY}, mPlayerThisTurn{Player1},mOpponent{Player2},
    mEmptyBoard("../assets/img/board/03_board.png",
                SDL_Rect{0,0,ImgWidth,ImgHeight},
                SDL_Rect{mUpperX,mUpperY,ImgWidth,ImgHeight},
                ScalingMode::Fill)
    {
    for (int i=0; i<mSize; ++i){
        for (int j=0; j<mSize; ++j){
            board[i][j].ChangeRectangle((mUpperX+mEdgeWidth+j*mCellWidth),(mUpperY+mEdgeWidth+i*mCellHeight),
                                        mCellWidth, mCellHeight);
            board[i][j].SetRow(i);
            board[i][j].SetCol(j);
        }
    }
}

void Board::HandleEvent(const SDL_Event& E, int& CurrentMove){
    //TODO : Improve use of mBoardState. Should not need to pass it back and forth to Unit

    // Contains the intersection currently under the mouse cursor
    int MouseCol; 
    int MouseRow;
    switch (E.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (E.button.button == SDL_BUTTON_LEFT){
            // Compute which cell was clicked
            MouseCol = (E.motion.x - mUpperX) / mCellWidth;
            MouseRow = (E.motion.y - mUpperY) / mCellHeight;
            
            if(IsMoveLegal(MouseRow, MouseCol)){ // check that mouse is within bounds
                if (board[MouseRow][MouseCol].mStatus == Forecast){
                    board[MouseRow][MouseCol].HandleMouseClick(E.button, CurrentMove);
                };
            }
        }
        break;
    default:
        if (E.type == Events::UNIT_PLAYED){
            // check player of previous move and fill the board with their unit
                (CurrentMove-1)%2==0 ? board[E.motion.y][E.motion.x].mStatus = Player1
                                     : board[E.motion.y][E.motion.x].mStatus = Player2;
                Status temp = mPlayerThisTurn;
                mPlayerThisTurn = mOpponent;
                mOpponent = temp;
                ForecastResetter();

        } else if (E.type == Events::P1_PASSED || E.type == Events::P2_PASSED){
            Status temp = mPlayerThisTurn;
            mPlayerThisTurn = mOpponent;
            mOpponent = temp;
        } else if (E.type==Events::CARD_SELECTED){
            Forecaster(E.button.button);
        } else if(E.type == Events::CARD_UNSELECTED){
            ForecastResetter();
        }
    }
}

void Board::Render(SDL_Surface* Surface){
    mEmptyBoard.Render(Surface);
    for (int i=0; i<mSize; ++i){
        for (int j=0; j<mSize; ++j){
            if (board[i][j].mStatus!=Empty){
                board[i][j].Render(Surface);
            }
        }
    }
}

bool Board::IsIntersectionValid(int row, int col){ return (row >= 0 && row < mSize && col >= 0 && col < mSize); }


bool Board::IsMoveLegal(int row, int col){
    if(!IsIntersectionValid(row, col)) { return false;}
    
    if (board[row][col].mStatus == Player1
    ||  board[row][col].mStatus == Player2) {return false;}
    
    if ((row > 18 && board[row+1][col].mStatus == mOpponent) &&
        (row < 0  && board[row-1][col].mStatus == mOpponent) &&
        (col < 18 && board[row][col+1].mStatus == mOpponent) &&
        (col > 0  && board[row][col-1].mStatus == mOpponent)){ 
        // TODO: add illegal move sound event here
        return false; }
    return true;
}

/*
 * Forecast which zone of the board will be playable with the selected card
*/
void Board::Forecaster(int CardID, bool WasSacrificed){
    if (WasSacrificed){
        CardID = 5; // fall back to free placement
    }
    if (CardID == 0){ //bigJump
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(board[i][j].mStatus == mPlayerThisTurn){
                    if (IsMoveLegal(i-3,j)){
                        board[i-3][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+3,j)){
                        board[i+3][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j-3)){
                        board[i][j-3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j+3)){
                        board[i][j+3].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 1){ // bigKnight
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(board[i][j].mStatus == mPlayerThisTurn){
                    if (IsMoveLegal(i-3,j+1)){
                        board[i-3][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-3,j-1)){
                        board[i-3][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+3,j+1)){
                        board[i+3][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+3,j-1)){
                        board[i+3][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j-3)){
                        board[i+1][j-3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j-3)){
                        board[i-1][j-3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j+3)){
                        board[i+1][j+3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j+3)){
                        board[i-1][j+3].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 2){ // center
        for (int i=0; i<mSize; ++i){
            for (int j=0; j<mSize; ++j){
                if (IsMoveLegal(i,j)
                &&  i>2 && i<mSize-3
                &&  j>2 && j<mSize-3){
                    board[i][j].mStatus = Forecast;
                }
            }
        }
    } else if(CardID == 3){ // corner
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if ((i < 4 || i > mSize-5)
                &&  (j < 4 || j > mSize-5)
                &&  IsMoveLegal(i,j)){
                    board[i][j].mStatus = Forecast;
                }
            }
        }
    } else if(CardID == 4){ // diagonal moves
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(board[i][j].mStatus == mPlayerThisTurn){
                    if (IsMoveLegal(i-1, j-1)){
                        board[i-1][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1, j+1)){
                        board[i+1][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1, j+1)){
                        board[i-1][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1, j-1)){
                        board[i+1][j-1].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 5){ // free
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if (IsMoveLegal(i,j)){
                    board[i][j].mStatus = Forecast;
                }
                
            }
        }
    } else if(CardID == 6){ // jump
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(board[i][j].mStatus == mPlayerThisTurn){
                    if (IsMoveLegal(i-2,j)){
                        board[i-2][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+2,j)){
                        board[i+2][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j-2)){
                        board[i][j-2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j+2)){
                        board[i][j+2].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 7){ // knight
                for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(board[i][j].mStatus == mPlayerThisTurn){
                    if (IsMoveLegal(i-2,j+1)){
                        board[i-2][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-2,j-1)){
                        board[i-2][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+2,j+1)){
                        board[i+2][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+2,j-1)){
                        board[i+2][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j-2)){
                        board[i+1][j-2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j-2)){
                        board[i-1][j-2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j+2)){
                        board[i+1][j+2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j+2)){
                        board[i-1][j+2].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 8){ // neighbour
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(board[i][j].mStatus == mPlayerThisTurn){
                    if (IsMoveLegal(i-1,j)){
                        board[i-1][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j)){
                        board[i+1][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j-1)){
                        board[i][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j+1)){
                        board[i][j+1].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 9){ // side
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if (
                    ((i < 4 || i > mSize-5) && j > 3 && j < mSize-4)
                ||  ((j < 4 || j > mSize-5) && i > 3 && i < mSize-4)
                ){
                    if (IsMoveLegal(i,j)){
                        board[i][j].mStatus = Forecast;
                    }
                }
            }
        }
    }
    return;
}

/*
 * Reset the forecast for playable move
*/
void Board::ForecastResetter(){
    for (int i = 0; i < mSize; ++i){
        for (int j = 0; j < mSize; ++j){
            if (board[i][j].mStatus == Forecast){
                board[i][j].mStatus = Empty;
                }
        }
    }
    
    
                    
    return;
}