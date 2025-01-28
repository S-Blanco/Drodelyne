#include "Box.h"
#include "Events.h"
#include "Layout.h"

struct DrawRectangle{
	public:
	DrawRectangle(int OuterRect_x, int OuterRect_y, int OuterRect_w, int OuterRect_h,
				  int BorderSize, int Index, SDL_Color InsideColor, SDL_Color OutsideColor);

	void Render(SDL_Surface* Surface);
	void HandleEvent(SDL_Event E);
    void SetColor(SDL_Color NewColor){mColor = NewColor;};
	int GetScore(){return mScore;};
	int GetIndex(){return mIndex;};
	
	
	protected:
	SDL_Color mColor{255, 0, 255};
	Box Zone;
	int mIndex;
	int mScore{0};
	
	int x0{0};
	int y0{0};
	int x1{0};
	int y1{0};
	bool flipX{false};
	bool flipY{false};
	bool IsPressed{false};
	bool IsWithinBounds(int x, int y);
	
};