#include "Board.h"
#include "Events.h"

# ifdef DEBUG
    #include <format>
#endif


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
            mBoardState[i][j] = Empty;
        }
    }

}

void Board::HandleEvent(const SDL_Event& E){
    //TODO : Improve use of mBoardState. Should not need to pass it back and forth to Unit

    // Contains the intersection currently under the mouse cursor
    int MouseCol; 
    int MouseRow;
    switch (E.type)
    {
    case SDL_MOUSEMOTION: //only used for hover? if so, not needed anymore?
        mHasMoved = true;
        MouseCol = (E.motion.x - Config::MOUSE_X_SHIFT - mUpperX) / mCellWidth; 
        MouseRow = (E.motion.y - Config::MOUSE_Y_SHIFT - mUpperY) / mCellHeight;
        if (IsIntersectionValid(MouseRow, MouseCol)){
            board[MouseRow][MouseCol].HandleMouseMotion(E.motion);
            mLastCol = MouseCol;
            mLastRow = MouseRow;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (E.button.button == SDL_BUTTON_LEFT){
            MouseCol = (E.motion.x - mUpperX) / mCellWidth;
            MouseRow = (E.motion.y - mUpperY) / mCellHeight;
            
            if(IsMoveLegal(MouseRow, MouseCol)){ // check that mouse is within bounds
                if (mBoardState[MouseRow][MouseCol] == Forecast){
                    board[MouseRow][MouseCol].HandleMouseClick(E.button, mMoveNbr);
                };
            }
        }
        break;
    default:
        if (E.type == Events::HOVER_EVENT){
            if (mBoardState[E.motion.y][E.motion.x] == Hover){
                mBoardState[E.motion.y][E.motion.x] = Empty;
            }
            board[E.motion.y][E.motion.x].HandleMouseMotion(E.motion);
        }else if (E.type == Events::UNIT_PLAYED){
            // check player of previous move and fill the board with their unit
                (mMoveNbr-1)%2==0 ? mBoardState[E.motion.y][E.motion.x]=Player1
                            : mBoardState[E.motion.y][E.motion.x]=Player2;
                Status temp = mPlayerThisTurn;
                mPlayerThisTurn = mOpponent;
                mOpponent = temp;
                ForecastResetter();

        }else if (E.type==Events::CARD_SELECTED){
        Forecaster(E.button.button);
        }else if(E.type == Events::CARD_UNSELECTED){
            ForecastResetter();
        }
    }
}

void Board::Render(SDL_Surface* Surface){
    mEmptyBoard.Render(Surface);
    for (int i=0; i<mSize; ++i){
        for (int j=0; j<mSize; ++j){
            if (mBoardState[i][j]!=Empty){
                board[i][j].Render(Surface, &mHasMoved);
            }
        }
    }
}

bool Board::IsIntersectionValid(int row, int col){ return (row >= 0 && row < mSize && col >= 0 && col < mSize); }

/*
    * Ensure that the hover image stays in place even if the mouse hasn't move this frame
*/
void Board::CheckHover(){
    if (!mHasMoved && board[mLastRow][mLastCol].mStatus==Empty)
        board[mLastRow][mLastCol].mStatus = Hover;
}

bool Board::IsMoveLegal(int row, int col){
    if(!IsIntersectionValid(row, col)) { return false;}
    
    if (mBoardState[row][col] == Player1
    ||  mBoardState[row][col] == Player2) {return false;}
    
    if (   mBoardState[row+1][col] == mOpponent
        && mBoardState[row-1][col] == mOpponent
        && mBoardState[row][col+1] == mOpponent
        && mBoardState[row][col-1] == mOpponent){ 
        // TODO: add illegal move sound event here
        return false; }
    return true;
}

/*
 * Forecast which zone of the board will be playable with the selected card
*/
void Board::Forecaster(int CardID, bool WasSacrificed){
    // TODO : Use correct values of cardID once we are assured that the system works
    if (WasSacrificed){
        CardID = 5; // fall back to free placement
    }
    if (CardID == 0){ //bigJump
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (IsMoveLegal(i-3,j)){
                        mBoardState[i-3][j] = Forecast;
                        board[i-3][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+3,j)){
                        mBoardState[i+3][j] = Forecast;
                        board[i+3][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j-3)){
                        mBoardState[i][j-3] = Forecast;
                        board[i][j-3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j+3)){
                        mBoardState[i][j+3] = Forecast;
                        board[i][j+3].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 1){ // bigKnight
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (IsMoveLegal(i-3,j+1)){
                        mBoardState[i-3][j+1] = Forecast;
                        board[i-3][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-3,j-1)){
                        mBoardState[i-3][j-1] = Forecast;
                        board[i-3][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+3,j+1)){
                        mBoardState[i+3][j+1] = Forecast;
                        board[i+3][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+3,j-1)){
                        mBoardState[i+3][j-1] = Forecast;
                        board[i+3][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j-3)){
                        mBoardState[i+1][j-3] = Forecast;
                        board[i+1][j-3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j-3)){
                        mBoardState[i-1][j-3] = Forecast;
                        board[i-1][j-3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j+3)){
                        mBoardState[i+1][j+3] = Forecast;
                        board[i+1][j+3].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j+3)){
                        mBoardState[i-1][j+3] = Forecast;
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
                    mBoardState[i][j] = Forecast;
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
                    mBoardState[i][j] = Forecast;
                    board[i][j].mStatus = Forecast;
                }
            }
        }
    } else if(CardID == 4){ // diagonal moves
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (IsMoveLegal(i-1, j-1)){
                        mBoardState[i-1][j-1] = Forecast;
                        board[i-1][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1, j+1)){
                        mBoardState[i+1][j+1] = Forecast;
                        board[i+1][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1, j+1)){
                        mBoardState[i-1][j+1] = Forecast;
                        board[i-1][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1, j-1)){
                        mBoardState[i+1][j-1] = Forecast;
                        board[i+1][j-1].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 5){ // free
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if (IsMoveLegal(i,j)){
                    mBoardState[i][j] = Forecast;
                    board[i][j].mStatus = Forecast;
                }
                
            }
        }
    } else if(CardID == 6){ // jump
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (IsMoveLegal(i-2,j)){
                        mBoardState[i-2][j] = Forecast;
                        board[i-2][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+2,j)){
                        mBoardState[i+2][j] = Forecast;
                        board[i+2][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j-2)){
                        mBoardState[i][j-2] = Forecast;
                        board[i][j-2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j+2)){
                        mBoardState[i][j+2] = Forecast;
                        board[i][j+2].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 7){ // knight
                for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (IsMoveLegal(i-2,j+1)){
                        mBoardState[i-2][j+1] = Forecast;
                        board[i-2][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-2,j-1)){
                        mBoardState[i-2][j-1] = Forecast;
                        board[i-2][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+2,j+1)){
                        mBoardState[i+2][j+1] = Forecast;
                        board[i+2][j+1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+2,j-1)){
                        mBoardState[i+2][j-1] = Forecast;
                        board[i+2][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j-2)){
                        mBoardState[i+1][j-2] = Forecast;
                        board[i+1][j-2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j-2)){
                        mBoardState[i-1][j-2] = Forecast;
                        board[i-1][j-2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j+2)){
                        mBoardState[i+1][j+2] = Forecast;
                        board[i+1][j+2].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i-1,j+2)){
                        mBoardState[i-1][j+2] = Forecast;
                        board[i-1][j+2].mStatus = Forecast;
                    }
                }
            }
        }
    } else if(CardID == 8){ // neighbour
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (IsMoveLegal(i-1,j)){
                        mBoardState[i-1][j] = Forecast;
                        board[i-1][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i+1,j)){
                        mBoardState[i+1][j] = Forecast;
                        board[i+1][j].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j-1)){
                        mBoardState[i][j-1] = Forecast;
                        board[i][j-1].mStatus = Forecast;
                    }
                    if (IsMoveLegal(i,j+1)){
                        mBoardState[i][j+1] = Forecast;
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
                        mBoardState[i][j] = Forecast;
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
            if (mBoardState[i][j] == Forecast){
                board[i][j].mStatus = Empty;
                mBoardState[i][j] = Empty;
                }
        }
    }
    
    
                    
    return;
}