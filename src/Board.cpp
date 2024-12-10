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
    case SDL_MOUSEMOTION:
        mHasMoved = true;
        MouseCol = (E.motion.x - Config::MOUSE_X_SHIFT - mUpperX) / mCellWidth; 
        MouseRow = (E.motion.y - Config::MOUSE_Y_SHIFT - mUpperY) / mCellHeight;
        if (IsIntersectionValid(MouseCol, MouseRow)){
            board[MouseRow][MouseCol].HandleMouseMotion(E.motion);
            mLastCol = MouseCol;
            mLastRow = MouseRow;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        MouseCol = (E.motion.x - mUpperX) / mCellWidth;
        MouseRow = (E.motion.y - mUpperY) / mCellHeight;
        if(IsMoveLegal(MouseRow, MouseCol)){
            if (IsIntersectionValid(MouseCol, MouseRow)){
                board[MouseRow][MouseCol].HandleMouseClick(E.button, mMoveNbr);
            };
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

bool Board::IsIntersectionValid(int X, int Y){ return (X >= 0 && X < mSize && Y >= 0 && Y < mSize); }

/*
    * Ensure that the hover image stays in place even if the mouse hasn't move this frame
*/
void Board::CheckHover(){
    if (!mHasMoved && board[mLastRow][mLastCol].mStatus==Empty)
        board[mLastRow][mLastCol].mStatus = Hover;
}

bool Board::IsMoveLegal(int row, int col){
    
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
void Board::Forecaster(int CardID){
    // TODO : Use correct values of cardID once we are assured that the system works
    if (CardID == 0){ // adjacent moves
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (i-1 > 0  && mBoardState[i-1][j] == 0){
                        mBoardState[i-1][j] = Forecast;
                        board[i-1][j].mStatus = Forecast;
                    }
                    if (i+1 < mSize && mBoardState[i+1][j] == 0){
                        mBoardState[i+1][j] = Forecast;
                        board[i+1][j].mStatus = Forecast;
                    }
                    if (j-1 > 0  && mBoardState[i][j-1] == 0){
                        mBoardState[i][j-1] = Forecast;
                        board[i][j-1].mStatus = Forecast;
                    }
                    if (j+1 < mSize && mBoardState[i][j+1] == 0){
                        mBoardState[i][j+1] = Forecast;
                        board[i][j+1].mStatus = Forecast;
                    }
                }
            }
        }
    }else if(CardID == 1){ // diagonal moves
        for (int i = 0; i < mSize; ++i){
            for (int j = 0; j < mSize; ++j){
                if(mBoardState[i][j] == mPlayerThisTurn){
                    if (i-1>0  && j-1>0  && mBoardState[i-1][j-1] == 0){
                        mBoardState[i-1][j-1] = Forecast;
                        board[i-1][j-1].mStatus = Forecast;
                    }
                    if (i+1<mSize && j+1<mSize && mBoardState[i+1][j+1] == 0){
                        mBoardState[i+1][j+1] = Forecast;
                        board[i+1][j+1].mStatus = Forecast;
                    }
                    if (i-1>0  && j+1<mSize && mBoardState[i-1][j+1] == 0){
                        mBoardState[i-1][j+1] = Forecast;
                        board[i-1][j+1].mStatus = Forecast;
                    }
                    if (i+1<mSize && j-1>0  && mBoardState[i+1][j-1] == 0){
                        mBoardState[i+1][j-1] = Forecast;
                        board[i+1][j-1].mStatus = Forecast;
                    }
                }
            }
        }
    }else if(CardID == 2){
        for (int i=0; i<mSize; ++i){
            for (int j=0; j<mSize; ++j){
                if (i>2 && i<mSize-3 && j>2 && j<mSize-3){
                    mBoardState[i][j] = Forecast;
                    board[i][j].mStatus = Forecast;
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