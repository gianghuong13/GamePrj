#include "Pattern.h"

Patterns::Patterns(int _type)
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
	if (type == IN_AIR_ENEMY)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
	}
	else if (type == ON_GROUND_ENEMY1)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = GROUND - 15 ;
	}
	else if (type == ON_GROUND_ENEMY2)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		posY = GROUND - 5 ;
	}
	PatternsTexture = nullptr;
}

Patterns::~Patterns()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = 0;
	if (PatternsTexture != nullptr)
	{
		PatternsTexture = nullptr;
	}
}

void Patterns::loadFromFile(std::string path, SDL_Renderer* gRenderer)
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

	PatternsTexture = tmpTexture;
}

void Patterns::Move(const int &acceleration)
{
	posX += -(ENEMY_SPEED + acceleration);
	if (posX + MAX_ENEMY_WIDTH < 0)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;

		if (type == IN_AIR_ENEMY)
		{
			posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
		}
	}
}

void Patterns::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, PatternsTexture, currentClip, &renderSpace);
}

int Patterns::getType()
{
	if (type == IN_AIR_ENEMY)
	{
		return IN_AIR_ENEMY;
	}
	else if (type == ON_GROUND_ENEMY1)
	{
		return ON_GROUND_ENEMY1;
	}
	else return ON_GROUND_ENEMY2;
}

int Patterns::getSpeed(const int &acceleration)
{
	return ENEMY_SPEED + acceleration;
}

int Patterns::getPosX()
{
	return posX;
}

int Patterns::getPosY()
{
	return posY;
}

int Patterns::getWidth()
{
	return eWidth;
}

int Patterns::getHeight()
{
	return eHeight;
}