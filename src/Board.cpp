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
    for (int row=0; row<mSize; ++row){
        for (int col=0; col<mSize; ++col){
            board[row][col].ChangeRectangle((mUpperX + Layout::EdgeWidth + col * Layout::CellWidth),
                                            (mUpperY + Layout::EdgeWidth + row * Layout::CellHeight),
                                            Layout::CellWidth,
                                            Layout::CellHeight);
            board[row][col].SetRow(row);
            board[row][col].SetCol(col);
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
            // if statement necessary to avoid rounding up to zero if mouse out (but close) of board
            E.motion.x >= mUpperX ? MouseCol = (E.motion.x - mUpperX) / Layout::CellWidth
                                  : MouseCol = -1;
            E.motion.y >= mUpperY ? MouseRow = (E.motion.y - mUpperY) / Layout::CellHeight
                                  : MouseRow = -1;
            
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
                if ((CurrentMove-1)%2==0){
                    PlaceUnit(E.motion.y, E.motion.x, Player1);

                } else {
                    PlaceUnit(E.motion.y, E.motion.x, Player2);
                }
                                     
                Status temp = mPlayerThisTurn;
                mPlayerThisTurn = mOpponent;
                mOpponent = temp;
                ForecastResetter();

        } else if (E.type == Events::P1_PASSED || E.type == Events::P2_PASSED){
            Status temp = mPlayerThisTurn;
            mPlayerThisTurn = mOpponent;
            mOpponent = temp;
            ForecastResetter();
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
    
    // Cannot play on another unit
    if (board[row][col].mStatus == Player1
    ||  board[row][col].mStatus == Player2) {return false;}

    // Cannot play in a space without liberties
    if (board[row+1][col].mStatus == mOpponent && 
        board[row-1][col].mStatus == mOpponent && 
        board[row][col+1].mStatus == mOpponent && 
        board[row][col-1].mStatus == mOpponent ){
        return false;
    }
    return true;
}


int Board::GetGroupLiberties(int (&arr)[19][19], int GroupId){
    int Liberties{0};
    for (int col = 0; col < mSize; ++col){
        for (int row = 0; row < mSize; ++row){
            if (arr[row][col] == GroupId){
                if (row < 18 && arr[row+1][col] == Empty) {++Liberties;}
                if (row > 0  && arr[row-1][col] == Empty) {++Liberties;}
                if (col < 18 && arr[row][col+1] == Empty) {++Liberties;}
                if (col > 0  && arr[row][col-1] == Empty) {++Liberties;}
            }
        }
    }
    return Liberties;
}

void Board::RemoveGroup(int GroupId){
    for (int col = 0; col < mSize; ++col){
        for (int row = 0; row < mSize; ++row){
            if (mGroupsOnBoard[row][col] == GroupId){
                mGroupsOnBoard[row][col] = 0;
                board[row][col].mStatus = Empty;
            }
        }
    }
}


void Board::ReplaceGroupIndex(int (&arr)[19][19], int OldIndex, int NewIndex){
    for (int col = 0; col < mSize; ++col){
        for (int row = 0; row < mSize; ++row){
            if (arr[row][col] == OldIndex) {arr[row][col] = NewIndex;}
        }
    }
}
void Board::PlaceUnit(int row, int col, Status Player){
// First we remove the captured enemy group
    if (row > 0 && board[row-1][col].mStatus == mOpponent ){
        int GroupID = mGroupsOnBoard[row-1][col];
        int Liberties = GetGroupLiberties(mGroupsOnBoard, GroupID);
        if (Liberties == 1){
            RemoveGroup(GroupID);
        }
    }
    if (row < 18 && board[row+1][col].mStatus == mOpponent){
        int GroupID = mGroupsOnBoard[row+1][col];
        int Liberties = GetGroupLiberties(mGroupsOnBoard, GroupID);
        if (Liberties == 1){
            RemoveGroup(GroupID);
        }
    }
    if (col > 0 && board[row][col-1].mStatus == mOpponent){
        int GroupID = mGroupsOnBoard[row][col-1];
        int Liberties = GetGroupLiberties(mGroupsOnBoard, GroupID);
        if (Liberties == 1){
            RemoveGroup(GroupID);
        }
    }
    if (col < 18 && board[row][col+1].mStatus == mOpponent){
        int GroupID = mGroupsOnBoard[row][col+1];
        int Liberties = GetGroupLiberties(mGroupsOnBoard, GroupID);
        if (Liberties == 1){
            RemoveGroup(GroupID);
        }
    }

// Then we see if this merges multiple of our groups
    std::vector<int> AdjacentAlliesIdx;

    if ((row < 18 && board[row+1][col].mStatus == mPlayerThisTurn)){
        AdjacentAlliesIdx.emplace_back(mGroupsOnBoard[row+1][col]);
    }
    if (row > 0 && board[row-1][col].mStatus == mPlayerThisTurn){
        AdjacentAlliesIdx.emplace_back(mGroupsOnBoard[row-1][col]);
    }
    if (col < 18 && board[row][col+1].mStatus == mPlayerThisTurn){
        AdjacentAlliesIdx.emplace_back(mGroupsOnBoard[row][col+1]);
    }
    if (col > 0 && board[row][col-1].mStatus == mPlayerThisTurn){
        AdjacentAlliesIdx.emplace_back(mGroupsOnBoard[row][col-1]);
    }


    if(AdjacentAlliesIdx.size() > 0){
        for (int col = 0; col < mSize; ++col){
            for (int row = 0; row < mSize; ++row){
                mTemp_GroupsOnBoard[row][col] = mGroupsOnBoard[row][col];
            }
        }
        mTemp_GroupsOnBoard[row][col] = mCurrentGroupIndex;
        for (int idx : AdjacentAlliesIdx){ // Replacing groups in temp copy
            ReplaceGroupIndex(mTemp_GroupsOnBoard, idx, mCurrentGroupIndex);
        }
        if(GetGroupLiberties(mTemp_GroupsOnBoard, mCurrentGroupIndex) != 0){
            for (int i = 0; i < mSize; ++i){
                for (int j = 0; j < mSize; ++j){
                    mGroupsOnBoard[i][j] = mTemp_GroupsOnBoard[i][j];
                }
            }
        ++mCurrentGroupIndex; // increment for next use
        } else {// illegal move, copy old board state (should be caught at when displaying legal move [but currently is not])
            for (int i = 0; i < mSize; ++i){
                for (int j = 0; j < mSize; ++j){
                    mTemp_GroupsOnBoard[i][j] = mGroupsOnBoard[i][j];
                }
            }
            std::cout << std::format("Illegal move!") << std::endl; // should never happen?
        }
            
        
    } else{
        mGroupsOnBoard[row][col] = mCurrentGroupIndex;
        ++mCurrentGroupIndex;
    }
    board[row][col].mStatus = Player;

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