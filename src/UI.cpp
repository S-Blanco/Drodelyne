#include "UI.h"
#include "Layout.h" // included here because when included in UI.h, multiple include error even with pragma once?

UI::UI(std::array<std::string, mDeckSize> PlayerDeckFile, std::array<int, 10> PlayerDeckID)
    :mPlayer1DeckFile{PlayerDeckFile},mPlayer1DeckID{PlayerDeckID},mCardIndex{0}
    {
        // TODO : Make it actually random
        std::shuffle(mPlayer1DeckID.begin(), mPlayer1DeckID.end(),std::default_random_engine(0));
        {
        using namespace Layout;
        mDeckSpot = Card(TopDeckX, TopDeckY, CardWidth, -1, "../assets/img/cards/card_p1.png");
        mCardSpots[0] = Card(TopHandX, TopHandY, CardWidth, mPlayer1DeckID[mCardIndex], mPlayer1DeckFile[mPlayer1DeckID[mCardIndex]]);
        ++mCardIndex; // TODO : Probably need some checking if card loading went wrong before increasing the index
        
        mCardSpots[1] = Card(TopHandX + CardWidth + CardMarginX, TopHandY, CardWidth, mPlayer1DeckID[mCardIndex], mPlayer1DeckFile[mPlayer1DeckID[mCardIndex]]);
        ++mCardIndex;
        
        mCardSpots[2] = Card(TopHandX, TopHandY + CardHeight + InterRowY, CardWidth, mPlayer1DeckID[mCardIndex], mPlayer1DeckFile[mPlayer1DeckID[mCardIndex]]);
        ++mCardIndex;
        
        mCardSpots[3] = Card(TopHandX + CardWidth + CardMarginX, TopHandY + CardHeight + InterRowY, CardWidth);
        
        for (int i=0; i<mDrawingSize; ++i){ // copy rest of deck in shuffling pile to use for the rest of the game
            mShufflePile[i] = mPlayer1DeckID[mCardIndex + i];
        }

        mCardIndex={0}; // Reset because for now on, we'll draw from the shuffling pile and not the deck
        DrawCard(mCardSpots[3]);

        mPreviewSpot = Card(BigModeX, BigModeY, BigCardWidth, -1,"../assets/img/cards/card_p1_front.png");
        mPreviewSpot.mIsActive = false;
        mPreviewSpot.mIsShown = false;
        }
    }
    

void UI::SwapGraveyardAndShuffle(){
    std::swap(mGraveyardPile, mShufflePile);
    std::fill(std::begin(mGraveyardPile), std::end(mGraveyardPile), -1);
    mCardIndex = 0;
    // TODO: Make it actually random
    std::shuffle(mShufflePile.begin(), mShufflePile.end(), std::default_random_engine(0));
    return ;
}
void UI::DrawCard(Card& spot){
    if (mCardIndex >= mDrawingSize){ // no more card to draw
        SwapGraveyardAndShuffle();
    }
    spot.SetImage(mPlayer1DeckFile[mShufflePile[mCardIndex]]);
    spot.mID = mShufflePile[mCardIndex];
    spot.mIsEmpty = false;
    ++mCardIndex;
    
}
void UI::HandleEvent(const SDL_Event& E){
    // card in preview spot was played
    if(E.type == Events::UNIT_PLAYED){
        mPreviewSpot.mIsActive = false;
        mPreviewSpot.mIsShown = false;
            mGraveyardPile[mCardIndex-1] = mPreviewSpot.mID; //-1 because the discard is one card late compared to the draw
        for (Card& spot : mCardSpots){
            if (spot.mIsEmpty){ DrawCard(spot); }
            spot.mIsEmpty = false;
            spot.mIsActive = true;
            spot.mIsShown = true;
        }
        SDL_Event CardPlayed{Events::CARD_PLAYED};
        SDL_PushEvent(&CardPlayed);

    } else if (E.type == SDL_MOUSEBUTTONDOWN){
        mClickedOnHand=false;

        // Check if click on a card in the player's hand
        for (Card& spot : mCardSpots){ 
            if(spot.mIsActive 
            && !spot.mIsEmpty
            && IsWithinBounds(E.motion.x, E.motion.y, spot)){
                mPreviewSpot.CopyImage(spot);
                mPreviewSpot.mIsActive = true;
                mPreviewSpot.mIsShown = true;
                mPreviewSpot.mID = spot.mID;
                spot.mIsEmpty = true;
                spot.mIsShown = false;
                mClickedOnHand=true;
                for (Card& Card : mCardSpots){ Card.mIsActive=false; }
                SDL_Event CardSelected{Events::CARD_SELECTED};
                CardSelected.button.button = spot.mID;
                SDL_PushEvent(&CardSelected);
                break;
            }
        }
        // Check if player clicked on the card in the preview spot to cancel its use
        if (E.button.button == SDL_BUTTON_RIGHT
        &&  !mClickedOnHand
        &&  mPreviewSpot.mIsActive
        &&  IsWithinBounds(E.motion.x, E.motion.y, mPreviewSpot)){
            mPreviewSpot.mIsActive = false;
            mPreviewSpot.mIsShown = false;
            for (Card& Card : mCardSpots){
                Card.mIsActive = true;
                Card.mIsShown  = true;
                Card.mIsEmpty  = false;
            }
            SDL_Event CardUnselected{Events::CARD_UNSELECTED};
            SDL_PushEvent(&CardUnselected);
        }
    }
    
}

bool UI::IsWithinBounds(int x, int y, Card& Card){
    return !(   x < Card.GetLeftX()
             || x > Card.GetRightX()
             || y < Card.GetTopY()
             || y > Card.GetBottomY());
}

void UI::Render(SDL_Surface* Surface){
    for (Card& spot : mCardSpots){
        spot.Render(Surface);
    }
    mDeckSpot.Render(Surface);
    mPreviewSpot.Render(Surface);
}