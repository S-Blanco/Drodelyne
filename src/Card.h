#pragma once

#include <SDL.h>

#include "Button.h"
#include "Image.h"


class Card: public Button{
    public:
        Card(int UpperX, int UpperY, int Width, int ID=-1, std::string File="");
        Card() = default;
        ~Card(){};
        
        bool mIsEmpty{false};
        bool mIsShown{true};
        
        void Render(SDL_Surface* Surface);
        void CopyImage(const Card& SrcCard);
        int SetImage(std::string File);
        SDL_Surface* getImage()const {return mFullImage;};

        int mID;


    private:

        float mCardRatio = 1.44;
        int mCardWidthClick;
        int mCardHeightClick;
        int mCardWidthIdle;
        int mCardHeightIdle;

        SDL_Rect mRectPosition;
        SDL_Surface* mFullImage{nullptr};
        SDL_Surface* mEmptyImage{nullptr};
        std::string mEmptyFile{"../assets/img/cards/card_empty_p1.png"};
        int LoadFile(std::string File, SDL_Surface*& Image);

};