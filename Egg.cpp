#include "Egg.h"

Egg::Egg(int _type)
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
	if (type == EGG)
	{
		posX = rand() % + EGG_RANGE + SCREEN_WIDTH;
		posY = rand() % (EGG_MAX_HEIGHT - EGG_MIN_HEIGHT + 1) + EGG_MIN_HEIGHT;
	}
	else if (type == BIG_EGG)
	{
		posX = rand() % + (EGG_RANGE+100) + SCREEN_WIDTH;
		posY = MAX_HEIGHT + 15;
	}
	EggTexture = nullptr;
}

Egg::~Egg()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = -1;
	if (EggTexture != nullptr)
	{
		EggTexture = nullptr;
	}
}

void Egg::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		std::cout << "Can not load image." << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			std::cout << "Can not create texture from surface." << SDL_GetError() << std::endl;
		}
		else
		{
			eWidth = tmpSurface->w;
			eHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	EggTexture = tmpTexture;
}

void Egg::Move(const int &acceleration)
{
	posX += -(EGG_SPEED + acceleration);
	if (posX + MAX_EGG_WIDTH < 0)
	{
		posX = rand() % + EGG_RANGE + SCREEN_WIDTH;

		if (type == EGG)
		{
			posY = rand() % (EGG_MIN_HEIGHT - EGG_MAX_HEIGHT + 1) + EGG_MIN_HEIGHT;
		}
		else if (type == BIG_EGG)
		{
			posY = MAX_HEIGHT + 15;
		}
	}
}

void Egg::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, EggTexture, currentClip, &renderSpace);
}

void Egg::Delete()
{
    posX = 0 - SCREEN_WIDTH;
}

int Egg::getType()
{
	if (type == EGG) return EGG;
}

int Egg::getSpeed(const int &acceleration)
{
	return EGG_SPEED + acceleration;
}

int Egg::getPosX()
{
	return posX;
}

int Egg::getPosY()
{
	return posY;
}

int Egg::getWidth()
{
	return eWidth;
}

int Egg::getHeight()
{
	return eHeight;
}