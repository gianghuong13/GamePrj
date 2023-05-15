#include "Mainchar.h"

Character::Character()
{
	posX = SCREEN_WIDTH - 750;
	posY = GROUND;

	status = 0;
}

bool Character::onGround()
{
	return posY == GROUND;
}

void Character::handleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
	if (e.type == SDL_KEYDOWN && (e.key.repeat == 1 || e.key.repeat == 0))
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (onGround())
				{
					Mix_PlayChannel(-1, gJump, 0);
					status = JUMP;
				}
			}

			case SDLK_SPACE:
			{
				if (onGround())
				{
					Mix_PlayChannel(-1, gJump, 0);
					status = JUMP;
				}
			}
		}
	}
}

void Character::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
	}
}

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::getPosX()
{
	return posX;
}

int Character::getPosY()
{
	return posY;
}