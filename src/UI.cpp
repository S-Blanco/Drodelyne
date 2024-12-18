#include "UI.h"
#include "Layout.h" // included here because when included in UI.h, multiple include error even with pragma once?

UI::UI(std::string Name1, std::array<std::string, mDeckSize> Player1DeckFile, std::array<int, 10> Player1DeckID, std::string P1DrawFile,
       std::string Name2, std::array<std::string, mDeckSize> Player2DeckFile, std::array<int, 10> Player2DeckID, std::string P2DrawFile)
       : mPlayers{{Name1, Player1DeckFile, Player1DeckID, P1DrawFile},{Name2, Player2DeckFile, Player2DeckID, P2DrawFile}}
    {
        
        mCurrentPlayer = &mPlayers[0];
        SetupHand(&mPlayers[0]);
        SetupHand(&mPlayers[1]);

        // mDiscard.mIsActive = false;
        // mDiscard.mIsVisible = false;

        // mCancel.mIsActive = false;
        // mCancel.mIsVisible = false;

        Write.SetFontSize(56);
        Write.mContent = std::format("{} : {}", mCurrentPlayer->mName, mCurrentPlayer->mObligation);


    }
    
void UI::SetupHand(Player* Player){

    // TODO : Make it actually random
        std::shuffle(Player->mDeckID.begin(), Player->mDeckID.end(),std::default_random_engine(0));
        {
        using namespace Layout;
        Player->mCardSpots[0] = Card(TopHandX, TopHandY, CardWidth, Player->mDeckID[Player->mCardIndex], Player->mDeckFile[Player->mDeckID[Player->mCardIndex]]);
        ++Player->mCardIndex; // TODO : Probably need some checking if card loading went wrong before increasing the index
        
        Player->mCardSpots[1] = Card(TopHandX + CardWidth + CardMarginX, TopHandY, CardWidth, Player->mDeckID[Player->mCardIndex], Player->mDeckFile[Player->mDeckID[Player->mCardIndex]]);
        ++Player->mCardIndex;
        
        Player->mCardSpots[2] = Card(TopHandX, TopHandY + CardHeight + InterRowY, CardWidth, Player->mDeckID[Player->mCardIndex], Player->mDeckFile[Player->mDeckID[Player->mCardIndex]]);
        ++Player->mCardIndex;
        
        Player->mCardSpots[3] = Card(TopHandX + CardWidth + CardMarginX, TopHandY + CardHeight + InterRowY, CardWidth);
        
        for (int i=0; i<mDrawingSize; ++i){ // copy rest of deck in shuffling pile to use for the rest of the game
            Player->mShufflePile[i] = Player->mDeckID[Player->mCardIndex + i];
        }

        Player->mCardIndex={0}; // Reset because for now on, we'll draw from the shuffling pile and not the deck
        DrawCard(Player->mCardSpots[3], Player);

        Player->mPreviewSpot = Card(BigModeX, BigModeY, BigCardWidth, -1,"../assets/img/cards/card_p1_front.png");
        Player->mPreviewSpot.mIsActive = false;
        Player->mPreviewSpot.mIsShown = false;
        }
    return;
}

void UI::SwapGraveyardAndShuffle(Player* Player){
    std::swap(Player->mGraveyardPile, Player->mShufflePile);
    std::fill(std::begin(Player->mGraveyardPile), std::end(Player->mGraveyardPile), -1);
    Player->mCardIndex = 0;
    // TODO: Make it actually random
    std::shuffle(Player->mShufflePile.begin(), Player->mShufflePile.end(), std::default_random_engine(0));
    return ;
}
    
void UI::DrawCard(Card& spot){
    DrawCard(spot, mCurrentPlayer);
}

void UI::DrawCard(Card& spot, Player* Player){
    if (Player->mCardIndex >= mDrawingSize){ // no more card to draw
        SwapGraveyardAndShuffle(Player);
    }
    spot.SetImage(Player->mDeckFile[Player->mShufflePile[Player->mCardIndex]]);
    spot.mID = Player->mShufflePile[Player->mCardIndex];
    spot.mIsEmpty = false;
    ++Player->mCardIndex;
    Player->mDeckSpot.SetCurrentIndex(GameSetting::DrawingSize - Player->mCardIndex);
    
}

void UI::HandleEvent(const SDL_Event& E){ HandleEvent(E, mCurrentPlayer); }
void UI::HandleEvent(const SDL_Event& E, Player* Player){
    
    
    // card in preview spot was played
    if(E.type == Events::UNIT_PLAYED){
        Player->mPreviewSpot.mIsActive = false;
        Player->mPreviewSpot.mIsShown = false;
        // mDiscard.mIsActive = false;
        // mDiscard.mIsVisible = false;
        // mCancel.mIsActive = false;
        // mCancel.mIsVisible = false;
            Player->mGraveyardPile[Player->mCardIndex-1] = Player->mPreviewSpot.mID; //-1 because the discard is one card late compared to the draw
        for (Card& spot : Player->mCardSpots){
            if (spot.mIsEmpty){ DrawCard(spot, Player); }
            spot.mIsEmpty = false;
            spot.mIsActive = true;
            spot.mIsShown = true;
        }
        SDL_Event ChangeScreen{Events::CHANGE_SCENE};
        mCurrentMove%2==0 ? ChangeScreen.motion.which = P2_TRANSITION
                          : ChangeScreen.motion.which = P1_TRANSITION;
        SDL_PushEvent(&ChangeScreen);
        ++mCurrentMove;
        mCurrentPlayer = &mPlayers[mCurrentMove%2];
        
    } else if (E.type == SDL_MOUSEBUTTONDOWN){
        mClickedOnHand=false;

        // if (mDiscard.mIsActive && mDiscard.IsWithinBounds(E.motion.x, E.motion.y)){
        //     SDL_Event CardSelected{Events::CARD_SELECTED};
        //     CardSelected.button.button = 5; // ID of free placement, TODO : put enum instead
        //     SDL_PushEvent(&CardSelected);
                
        //     Player->mObligation -= 5 ;
        //     mDiscard.mIsActive = false;

        // }
        // if (mCancel.mIsActive && mCancel.IsWithinBounds(E.motion.x, E.motion.y)){

        //     Player->mPreviewSpot.mIsActive = false;
        //     Player->mPreviewSpot.mIsShown = false;
        //     for (Card& Card : Player->mCardSpots){
        //         Card.mIsActive = true;
        //         Card.mIsShown  = true;
        //         Card.mIsEmpty  = false;
        //     }
        //     SDL_Event CardUnselected{Events::CARD_UNSELECTED};
        //     SDL_PushEvent(&CardUnselected);

        //     // this will move since it is the clicking of the button that trigger the visibility/activity
        //     mDiscard.mIsActive = false;
        //     mDiscard.mIsVisible = false;
        //     mCancel.mIsActive = false;
        //     mCancel.mIsVisible = false;
        // }
        // Check if click on a card in the player's hand
        for (Card& spot : Player->mCardSpots){ 
            if(spot.mIsActive 
            && !spot.mIsEmpty
            && spot.IsWithinBounds(E.motion.x, E.motion.y)){
                Player->mPreviewSpot.CopyImage(spot);
                Player->mPreviewSpot.mIsActive = true;
                Player->mPreviewSpot.mIsShown = true;
                Player->mPreviewSpot.mID = spot.mID;
                spot.mIsEmpty = true;
                spot.mIsShown = false;
                mClickedOnHand=true;
                for (Card& Card : Player->mCardSpots){ Card.mIsActive=false; }
                SDL_Event CardSelected{Events::CARD_SELECTED};
                CardSelected.button.button = spot.mID;
                SDL_PushEvent(&CardSelected);
                
                // mDiscard.mIsActive = true;
                // mDiscard.mIsVisible = true;
                // mCancel.mIsActive = true;
                // mCancel.mIsVisible = true;
                
                break;
            }
        }
        // Check if player clicked on the card in the preview spot to mCancel its use
        if (E.button.button == SDL_BUTTON_RIGHT
        &&  !mClickedOnHand
        &&  Player->mPreviewSpot.mIsActive
        &&  Player->mPreviewSpot.IsWithinBounds(E.motion.x, E.motion.y)){
            Player->mPreviewSpot.mIsActive = false;
            Player->mPreviewSpot.mIsShown = false;
            for (Card& Card : Player->mCardSpots){
                Card.mIsActive = true;
                Card.mIsShown  = true;
                Card.mIsEmpty  = false;
            }
            SDL_Event CardUnselected{Events::CARD_UNSELECTED};
            SDL_PushEvent(&CardUnselected);

            // this will move since it is the clicking of the button that trigger the visibility/activity
            // mDiscard.mIsActive = false;
            // mDiscard.mIsVisible = false;
            // mCancel.mIsActive = false;
            // mCancel.mIsVisible = false;
        }
    }
    
}

void UI::Render(SDL_Surface* Surface){
    Render(Surface, mCurrentPlayer);
    // mDiscard.Render(Surface);
    // mCancel.Render(Surface);
}

void UI::Render(SDL_Surface* Surface, Player* Player){
    for (Card& spot : Player->mCardSpots){
        spot.Render(Surface);
    }
    Player->mDeckSpot.Render(Surface);
    Player->mPreviewSpot.Render(Surface);
    
    // Move that elsewhere?
    Write.mContent = std::format("{} :\n{}", mCurrentPlayer->mName, mCurrentPlayer->mObligation);
    Write.Render(Surface);

}