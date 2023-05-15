#ifndef MAINCHAR_H_
#define MAINCHAR_H_

#include "LTexture.h"

#define JUMP 1
#define FALL 2
#define RUN	0

class Character
{
public:
	static const int JUMP_SPEED = 10;
	static const int FALL_SPEED = 10;

	Character();

	bool onGround();

	void handleEvent(SDL_Event& e, Mix_Chunk *gJump);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int getPosX();

	int getPosY();

private:
	int posX, posY;

	int status;
};

#endif 