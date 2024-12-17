#include "Text.h"


Text::Text(std::string Content)
    :mFont{TTF_OpenFont("Roboto-Medium.ttf", 12)},mContent{Content}
    {
        if(!mFont){
            std::cout << "Error loading font" << SDL_GetError() <<std::endl;
        }
        CreateSurface(Content);
    }

Text::Text(int FontSize)
    :mFont{LoadFont(FontSize)}
    {};

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

void Text::Render(SDL_Surface* DestSurface){
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
    
    SDL_BlitSurface(TextSurface, nullptr, DestSurface, &mDestRectangle);
}

TTF_Font* Text::LoadFont(int FontSize){
    TTF_Font* LoadedFont{TTF_OpenFont("Roboto-Medium.ttf", FontSize)};
    if(!LoadedFont){
        std::cout << "Error loading font : " << SDL_GetError() << std::endl;
    }
    return LoadedFont;
}