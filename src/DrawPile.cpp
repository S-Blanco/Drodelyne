#include "DrawPile.h"


DrawPile::DrawPile(std::string CardBackground, int DeckSize)
    :mCardBackground{CardBackground}, mDeckSize{DeckSize}
    {
        mCardBackground.SetDestinationRectangle({Layout::TopDeckX, Layout::TopDeckY, Layout::CardWidth, Layout::CardHeight});
        mDeckSizeDisplay.mContent = std::to_string(mDeckSize);
        mDeckSizeDisplay.SetFontSize(56);
        mDeckSizeDisplay.mDestRectangle.x = Layout::TopDeckX ;
        mDeckSizeDisplay.mDestRectangle.y = Layout::TopDeckY + 0.35*Layout::CardHeight;
        mDeckSizeDisplay.mDestRectangle.w = Layout::CardWidth;
        mDeckSizeDisplay.mDestRectangle.h = Layout::CardHeight;
    }


void DrawPile::Render(SDL_Surface* Surface){
    mCardBackground.Render(Surface);
    mDeckSizeDisplay.Render(Surface);
}


void DrawPile::SetCurrentIndex(int idx){
    mDeckSizeDisplay.mContent = std::to_string(idx);
}