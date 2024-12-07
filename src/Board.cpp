#include "Board.h"
#include "Events.h"

# ifdef DEBUG
    #include <format>
#endif


Board::Board(){
    for (int i=0; i<mSize; ++i){
        for (int j=0; j<mSize; ++j){
            board[i][j].ChangeRectangle((mUpperX+j*mCellWidth),(mUpperY+i*mCellHeight),
                                        mCellWidth, mCellHeight);
            board[i][j].SetRow(i);
            board[i][j].SetCol(j);
            mBoardState[i][j] = Empty;
        }
    }
}

Board::Board(int UpperX, int UpperY, int ImgWidth, int ImgHeight)
    :mUpperX{UpperX}, mUpperY{UpperY}, mEmptyBoard("../assets/img/board/03_board.png",
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
        if(IsMoveLegal(MouseCol, MouseRow)){
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
        }
        if (E.type == Events::UNIT_PLAYED){
            // check player of previous move
                (mMoveNbr-1)%2==0 ? mBoardState[E.motion.y][E.motion.x]=Player1
                            : mBoardState[E.motion.y][E.motion.x]=Player2;
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

bool Board::IsIntersectionValid(int X, int Y){
    return (X>=0 && X <mSize && Y>=0 && Y <mSize);
}

/*
    * Ensure that the hover image stays in place even if the mouse hasn't move this frame
*/
void Board::CheckHover(){
    if (!mHasMoved && board[mLastRow][mLastCol].mStatus==Empty)
        board[mLastRow][mLastCol].mStatus = Hover;
}

bool Board::IsMoveLegal(int col, int row){
    if (col==1 && row==2){return false;}
    return true;
}