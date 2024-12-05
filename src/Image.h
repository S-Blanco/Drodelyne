#pragma once


#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


enum class ScalingMode{None, Fill};

class Image{
    public:
        Image()=default;
        Image(const std::string& File);
        Image(const std::string& File,
              const SDL_Rect& SourceRect, const SDL_Rect& DestRect,
              ScalingMode ScalingMode);
        ~Image();
        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        void Render(SDL_Surface* DestinationSurface);
        void SaveToFile(std::string Location);
        void SetSrcRectangle(const SDL_Rect& Rect);
        void SetDestinationRectangle(const SDL_Rect& Rect);
        void SetBlitMode(ScalingMode NewMode);

    // protected:
    private:
        std::string     mFile{""};
        SDL_Surface*    mImageSurface{nullptr};
        SDL_Rect        mRequestedSrcRectangle{0,0,0,0};
        SDL_Rect        mAppliedSrcRectangle;
        SDL_Rect        mRequestedDestRectangle{0,0,0,0};
        SDL_Rect        mAppliedDestRectangle;
        ScalingMode     mScalingMode{ScalingMode::None};
        

        void LoadFile(const std::string& File);
        bool ValidateRectangle(const SDL_Rect& Rect, const SDL_Surface* Surface, const std::string& Context) const;
        bool RectangleWithinSurface(const SDL_Rect& Rect, const SDL_Surface* Surface) const;


};