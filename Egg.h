#ifndef EGG_H_
#define EGG_H_

#include "LTexture.h"

#define EGG 0
#define BIG_EGG 1
#define MAX_EGG_WIDTH 100

const int EGG_RANGE = 200;
const int EGG_MAX_HEIGHT = 250;
const int EGG_MIN_HEIGHT = 280;
const int EGG_SPEED = 5;


class Egg
{
public:
	Egg(int _type = 0);
	
	~Egg();

	void loadFromFile(std::string path, SDL_Renderer* gRenderer);

	void Move(const int& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);
	
	void Delete();
	
	int getType();

	int getSpeed(const int& acceleration);

	int getPosX();

	int getPosY();

	int getWidth();

	int getHeight();

private:
	int posX, posY;

	int eWidth, eHeight;

	int type;

	SDL_Texture *EggTexture;
};

#endif