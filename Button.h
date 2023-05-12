#ifndef BUTTON_H_
#define BUTTON_H_

#include "Functions.h"
#include "LTexture.h"

class Button
{
public:
	ButtonSprite currentSprite;

	Button();

	Button(int x, int y);

	void setPosition(int x, int y);

	bool isInside(SDL_Event *e, int size);

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);

private:
	SDL_Point position;
};

#endif // !BUTTON_H_