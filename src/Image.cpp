#include "Image.h"


Image::Image(const std::string& File):mScalingMode{ScalingMode::Fill}{
    LoadFile(File);
    mAppliedSrcRectangle = SDL_Rect{0,0,mImageSurface->w, mImageSurface->h};
    mAppliedDestRectangle = SDL_Rect{0,0,mImageSurface->w, mImageSurface->h};
}

Image::Image(const std::string& File,
             const SDL_Rect& SourceRect, const SDL_Rect& DestRect,
             ScalingMode ScalingMode):  
    mScalingMode{ScalingMode}
    {
        LoadFile(File);
        SetSrcRectangle(SourceRect);
        SetDestinationRectangle(DestRect);
    }

Image::~Image(){SDL_FreeSurface(mImageSurface);}

void Image::Render(SDL_Surface* DestinationSurface){
    if (mScalingMode == ScalingMode::Fill){
        if (mAppliedDestRectangle.x == 0 &&
            mAppliedDestRectangle.y == 0 &&
            mAppliedDestRectangle.w == 0 &&
            mAppliedDestRectangle.h == 0){
            SDL_BlitScaled(mImageSurface, &mAppliedSrcRectangle,
                    DestinationSurface, nullptr);    
        }else{
            SDL_BlitScaled(mImageSurface, &mAppliedSrcRectangle,
                    DestinationSurface, &mAppliedDestRectangle);
        }
        
    }else{
        SDL_BlitSurface(mImageSurface, nullptr,
                    DestinationSurface, nullptr);    
    }    
}

void Image::SaveToFile(std::string Location){ IMG_SavePNG(mImageSurface, Location.c_str());}

void Image::LoadFile(const std::string& File) {
    if (File == mFile) { return; }
    SDL_FreeSurface(mImageSurface);
    mFile = File;
    mImageSurface = IMG_Load(File.c_str());
    if (!mImageSurface){
        std::cout << "Failed to load image '" << File << "'\n" << SDL_GetError() << std::endl;
    }
    SDL_SetSurfaceBlendMode(mImageSurface, SDL_BLENDMODE_BLEND); // blend mode : https://wiki.libsdl.org/SDL2/SDL_BlendMode

}


void Image::SetSrcRectangle(const SDL_Rect& Rect){
    mRequestedSrcRectangle = Rect;
    if(ValidateRectangle(Rect, mImageSurface, "Source rectangle")){
        mAppliedSrcRectangle = Rect;
    } else {
        mAppliedSrcRectangle = {0,0,mImageSurface->w, mImageSurface->h};
    }
}


void Image::SetDestinationRectangle(const SDL_Rect& Rect) {
    mRequestedDestRectangle = Rect;
    if (ValidateRectangle(Rect, nullptr, "Destination Rectangle")) {
        mAppliedDestRectangle = Rect;
    } else {
        mAppliedDestRectangle = {0, 0, 0, 0};
    }
}


bool Image::ValidateRectangle(const SDL_Rect& Rect,
                              const SDL_Surface* Surface,
                              const std::string& Context) const{
    if (SDL_RectEmpty(&Rect)){
        std::cout << "[Error]: " << Context << ": Rectangle has no area" << std::endl;
        return false;
    }
    if (Surface && !RectangleWithinSurface(Rect, Surface)){
        std::cout << "[Error]: " << Context << ": Rectangle not within Surface target" <<std::endl;
        return false;
    }
    return  true;

}

void Image::SetBlitMode(ScalingMode NewMode){
    mScalingMode = NewMode;
}



bool Image::RectangleWithinSurface(const SDL_Rect& Rect, const SDL_Surface* Surface) const{
    if(Rect.x<0){return false;}
    if(Rect.x + Rect.w > Surface->w) {return false;}
    if(Rect.y<0){return false;}
    if(Rect.y + Rect.h > Surface->h) {return false;}
    return true;
}
