#ifndef PATTERN_H_
#define PATTERN_H_

#include "LTexture.h"

#define IN_AIR_ENEMY 0
#define ON_GROUND_ENEMY1 1
#define ON_GROUND_ENEMY2 2

#define ENEMY_POSITION_RANGE 400

#define SLOW_FRAME_CHAR 4
#define SLOW_FRAME_ENEMY 4

#define ENEMY_MAX_HEIGHT 250
#define ENEMY_MIN_HEIGHT 300


class Patterns
{
public:
	Patterns(int _type = 0);
	
	~Patterns();

	void loadFromFile(std::string path, SDL_Renderer* gRenderer);

	void Move(const int& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

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

	SDL_Texture *PatternsTexture;
};

#endif
