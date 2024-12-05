#include "UI.h"
#include "Layout.h" // included here because when included in UI.h, multiple include error even with pragma once?

UI::UI(std::array<std::string, mDeckSize> PlayerDeck)
    :mPlayer1Deck{PlayerDeck},mCardIndex{0}
    {
        // TODO : Make it actually random
        std::shuffle(mDrawingPile.begin(), mDrawingPile.end(),std::default_random_engine(0));
        #ifdef DEBUG
            std::cout << "Deck shuffled: ";
            for (int i=0; i<mDeckSize; ++i){ std::cout << mDrawingPile[i] << ","; }
            std::cout << std::endl;
        #endif
        {
        using namespace Layout;
        mDeckSpot = Card(TopDeckX, TopDeckY, CardWidth, "../assets/img/cards/card_p1.png");
        mCardSpots[0] = Card(TopHandX, TopHandY, CardWidth, mPlayer1Deck[mDrawingPile[mCardIndex]]);
        ++mCardIndex; // TODO : Probably need some checking if card loading went wrong before increasing the index
        mCardSpots[1] = Card(TopHandX + CardWidth + CardMarginX, TopHandY, CardWidth, mPlayer1Deck[mDrawingPile[mCardIndex]]);
        ++mCardIndex;
        mCardSpots[2] = Card(TopHandX, TopHandY + CardHeight + InterRowY, CardWidth, mPlayer1Deck[mDrawingPile[mCardIndex]]);
        ++mCardIndex;
        mCardSpots[3] = Card(TopHandX + CardWidth + CardMarginX, TopHandY + CardHeight + InterRowY, CardWidth);

        for (int i=0; i<mDrawingSize; ++i){
            mShufflePile[i] = mDrawingPile[mCardIndex + i];
        }
        #ifdef DEBUG
            std::cout << "Shuffling pile: ";
            for (int i=0; i<mDrawingSize; ++i){ std::cout << mShufflePile[i] << ","; }
            std::cout << std::endl;
        #endif
        mCardIndex={0}; // Reset because for now on, we'll draw from the shuffling pile and not the deck
        DrawCard(mCardSpots[3]);

        mPreviewSpot = Card(BigModeX, BigModeY, BigCardWidth, "../assets/img/cards/card_p1_front.png");
        mPreviewSpot.mIsActive = false;
        mPreviewSpot.mIsShown = false;
        }
    }
    
void UI::DrawCard(Card& spot){
    spot.SetImage(mPlayer1Deck[mShufflePile[mCardIndex]]);
    spot.mIsEmpty = false;
    ++mCardIndex;
    #ifdef DEBUG
        std::cout << "Shuffling pile after draw: ";
        for (int i=mCardIndex; i<mDrawingSize; ++i){ std::cout << mShufflePile[i] << ","; }
        std::cout << std::endl;
    #endif
    
}
void UI::HandleEvent(const SDL_Event& E){
    // card in preview spot was played
    if (E.type == Events::CARD_PLAYED){
        #ifdef DEBUG
            std::cout << std::format("Currently at card number {}", mCardIndex) << std::endl;
        #endif
        if (mCardIndex>=mDeckSize){
            #ifdef DEBUG
                std::cout << std::format("Reshuffling") << std::endl;
            #endif
            mCardIndex = 0;
            // TODO: Make it actually random
            std::shuffle(mDrawingPile.begin(), mDrawingPile.end(), std::default_random_engine(0));
        }

        for (Card& spot : mCardSpots){
            if (spot.mIsEmpty){ DrawCard(spot); }
            spot.mIsEmpty = false;
            spot.mIsActive = true;
            spot.mIsShown = true;
        }
    }
    
    if (E.type == SDL_MOUSEBUTTONDOWN){
        mClickedOnCard=false;

        for (Card& spot : mCardSpots){ // Check if click on a card in the player's hand
            if(spot.mIsActive 
            && !spot.mIsEmpty
            && IsWithinBounds(E.motion.x, E.motion.y, spot)){
                #ifdef DEBUG
                    std::cout << std::format("[Hand] Handle the click") << std::endl;
                #endif
                mPreviewSpot.CopyImage(spot);
                mPreviewSpot.mIsActive = true;
                mPreviewSpot.mIsShown = true;
                spot.mIsEmpty = true;
                spot.mIsShown = false;
                mClickedOnCard=true;
                for (Card& Card : mCardSpots){Card.mIsActive=false;}
                break;
            }
        }
        // Check if player clicked on the card on the preview spot
        if (!mClickedOnCard && mPreviewSpot.mIsActive && IsWithinBounds(E.motion.x, E.motion.y, mPreviewSpot)){
            if(E.button.button == SDL_BUTTON_RIGHT){
                #ifdef DEBUG
                    std::cout << std::format("Right click") << std::endl;
                    std::cout << std::format("[Preview] Handle the click") << std::endl;
                #endif
                mPreviewSpot.mIsActive = false;
                mPreviewSpot.mIsShown = false;
                for (Card& Card : mCardSpots){
                    Card.mIsActive = true;
                    Card.mIsShown  = true;
                    Card.mIsEmpty  = false;
                }

                
            }else if (E.button.button == SDL_BUTTON_LEFT){
                // Left click confirm player wants to use the card in the preview spot
                // sends event PLAYED_CARD and next turn, we draw a new one.
                
                #ifdef DEBUG
                    std::cout << std::format("Left click") << std::endl;
                    std::cout << std::format("[Preview] Handle the click") << std::endl;
                #endif
                
                mPreviewSpot.mIsActive = false;
                mPreviewSpot.mIsShown = false;
                // mGraveyardPile[mCardIndex] = 
                // TODO : Merge the 2 events.
                // Since there can only have a unit played when a card is played, one of
                // the 2 events generated (here and in Unit.HandleMouseClick) will disappear
                SDL_Event CardPlayed{Events::CARD_PLAYED};
                SDL_PushEvent(&CardPlayed);

            }
            
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