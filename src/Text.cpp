#include "Text.h"


Text::Text(int WrapSize, SDL_Rect DestRect, std::string Content)
:mDestRectangle{DestRect}, mFont{TTF_OpenFont("../assets/fonts/Roboto-Medium.ttf", 56)}, mContent{Content}, mWrapSize{WrapSize}
    {
          if(!mFont){
            std::cout << "Error loading font" << SDL_GetError() <<std::endl;
        }
        CreateSurface(Content);
    }

Text::Text(int FontSize, int WrapSize, SDL_Rect DestRect, std::string Content)
:mDestRectangle{DestRect}, mFont{TTF_OpenFont("../assets/fonts/Roboto-Medium.ttf", 56)}, mContent{Content}, mWrapSize{WrapSize}
    {
          if(!mFont){
            std::cout << "Error loading font" << SDL_GetError() <<std::endl;
        }
        CreateSurface(Content);
        SetFontSize(FontSize);
    }

Text::~Text(){
    if(TTF_WasInit){
        SDL_FreeSurface(mTextSurface);
        TTF_CloseFont(mFont);
    }   
}

void Text::CreateSurface(std::string Content){
    SDL_Surface* NewSurface = TTF_RenderUTF8_Blended(mFont, Content.c_str(), {255,255,255});
    if(NewSurface){
        SDL_FreeSurface(mTextSurface);
        mTextSurface = NewSurface;
    }else{
        std::cout << "Error creating TextSurface : " << SDL_GetError() << std::endl;
    }
}

void Text::Render(SDL_Surface* Surface){
    //Should be moved to ctor
    int Alignement = TTF_WRAPPED_ALIGN_CENTER;
    TTF_SetFontWrappedAlign(mFont, Alignement);

    SDL_Surface* TextSurface{TTF_RenderUTF8_Blended_Wrapped(mFont,
                                                            mContent.c_str(),
                                                            SDL_Color{255,255,255},
                                                            mWrapSize)};
    
    if(!TextSurface){
        std::cout << "Error generating the text : " << SDL_GetError() << std::endl;
    }
    #ifdef DEBUG
        SDL_FillRect(Surface,
                 &mDestRectangle,
                 SDL_MapRGB(Surface->format, 255, 0, 255));
    #endif
    SDL_BlitSurface(TextSurface, nullptr, Surface, &mDestRectangle);
}

TTF_Font* Text::LoadFont(int FontSize){
    TTF_Font* LoadedFont{TTF_OpenFont("../assets/fonts/Roboto-Medium.ttf", FontSize)};
    if(!LoadedFont){
        std::cout << "Error loading font : " << SDL_GetError() << std::endl;
    }
    return LoadedFont;
}