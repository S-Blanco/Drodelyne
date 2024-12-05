#include "Card.h"
#include <format>

Card::Card(int UpperX, int UpperY, int Width, std::string File)
    :mCardWidthClick{300},
    mCardHeightClick{static_cast<int>(mCardRatio*mCardWidthClick)},
    mCardWidthIdle{Width},
    mCardHeightIdle{static_cast<int>(mCardRatio*mCardWidthIdle)},
    mRectPosition{UpperX,UpperY,Width,static_cast<int>(mCardRatio*Width)},
    Button(UpperX, UpperY, mCardWidthIdle, 100)
    {
        ResizeButton(UpperX, UpperY, mCardWidthIdle, mCardHeightIdle);
        if (File==""){
            LoadFile(mEmptyFile.c_str(), mFullImage);
            LoadFile(mEmptyFile.c_str(), mEmptyImage);
            mIsEmpty = true;
        }else{
            LoadFile(File.c_str(), mFullImage);
            LoadFile(mEmptyFile.c_str(), mEmptyImage);
        }
        
}


void Card::Render(SDL_Surface* Surface){
        if (!mIsShown){return;}
        #ifdef DEGUB
            std::cout << std::format("Card rectangle data {}, {}, {}, {}", mRectPosition.x, mRectPosition.y, mRectPosition.w, mRectPosition.h) << std::endl;
        #endif
        if (mIsEmpty){ SDL_BlitScaled(mEmptyImage, nullptr, Surface, &mRectPosition); }
        else{ SDL_BlitScaled(mFullImage, nullptr, Surface, &mRectPosition); }
}

int Card::LoadFile(std::string File, SDL_Surface*& Image){ // TODO: Review this pointer reference...
    SDL_FreeSurface(Image);
    Image = IMG_Load(File.c_str());

    if (!Image){
        #ifdef DEBUG
            std::cout << "[Error] Failed to load card image '" << File << "'\n" << SDL_GetError() << std::endl;
        #endif
        return -1;
    }
    SDL_SetSurfaceBlendMode(Image, SDL_BLENDMODE_BLEND); // blend mode : https://wiki.libsdl.org/SDL2/SDL_BlendMode
    return 0;
}


void Card::CopyImage(const Card& SrcCard){
    mFullImage = SrcCard.getImage();
}

int Card::SetImage(std::string File){
    return LoadFile(File.c_str(), mFullImage);
}