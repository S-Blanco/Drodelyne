#include "Rectangle.h"
#include "Events.h"
#include "Layout.h"

struct DrawRectangle{
	public:
    DrawRectangle(int x, int y, int w, int h, int idx);
	DrawRectangle(int x, int y, int w, int h, int idx, SDL_Color Color);
	void Render(SDL_Surface* Surface);
	void HandleEvent(SDL_Event E);
    void SetColor(SDL_Color NewColor){mColor = NewColor;};
	int GetScore(){return mScore;};
	
	int idx;
	
	protected:
	SDL_Color mColor{255, 0, 255};
	Rectangle Zone;

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