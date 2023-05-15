#include "Gen_Col.h"

void generateEnemy(Patterns& enemy1,
	Patterns& enemy2,
	Patterns& enemy3,
	SDL_Rect(&gEnemyClips)[FLYING_FRAMES], 
	SDL_Renderer * gRenderer)
{
	enemy1.loadFromFile("imgs/enemy/cactus1.png", gRenderer);
	enemy2.loadFromFile("imgs/enemy/cactus2.png", gRenderer);
	enemy3.loadFromFile("imgs/enemy/1bat.png", gRenderer);
	{
		gEnemyClips[0].x = ENEMY_WIDTH * 0;
		gEnemyClips[0].y = 0;
		gEnemyClips[0].w = ENEMY_WIDTH;
		gEnemyClips[0].h = ENEMY_HEIGHT;

		gEnemyClips[1].x = ENEMY_WIDTH * 1;
		gEnemyClips[1].y = 0;
		gEnemyClips[1].w = ENEMY_WIDTH;
		gEnemyClips[1].h = ENEMY_HEIGHT;

		gEnemyClips[2].x = ENEMY_WIDTH * 2;
		gEnemyClips[2].y = 0;
		gEnemyClips[2].w = ENEMY_WIDTH;
		gEnemyClips[2].h = ENEMY_HEIGHT;

		gEnemyClips[3].x = ENEMY_WIDTH * 3;
		gEnemyClips[3].y = 0;
		gEnemyClips[3].w = ENEMY_WIDTH;
		gEnemyClips[3].h = ENEMY_HEIGHT;

	}
}

bool checkCollision(Character character,
	SDL_Rect* char_clip,
	Patterns pattern, 
	SDL_Rect* pattern_clip)
{
	bool collide = false;
	
	int leftA = character.getPosX();
	int rightA = character.getPosX() + char_clip->w;
	int topA = character.getPosY();
	int bottomA = character.getPosY() + char_clip->h;

	if (pattern.getType() == ON_GROUND_ENEMY1 || pattern.getType() == ON_GROUND_ENEMY2)
	{
		const int TRASH_PIXEL_1 = 20;
		const int TRASH_PIXEL_2 = 20;

		int leftB = pattern.getPosX();
		int rightB = pattern.getPosX() + pattern.getWidth();
		int topB = pattern.getPosY();
		int bottomB = pattern.getPosY() + pattern.getHeight();

		if (rightA - TRASH_PIXEL_1 >= leftB && leftA + TRASH_PIXEL_1 <= rightB)
		{
			if (bottomA - TRASH_PIXEL_2 >= topB)
			{
				collide = true;
			}
		}
	}
	else if (pattern.getType() == IN_AIR_ENEMY)
	{
		const int TRASH_PIXEL_1 = 25;
		const int TRASH_PIXEL_2 = 20;

		int leftB = pattern.getPosX();
		int rightB = pattern.getPosX() + pattern_clip->w;
		int topB = pattern.getPosY();
		int bottomB = pattern.getPosY() + pattern_clip->h;

		if (rightA - TRASH_PIXEL_1 >= leftB && leftA + TRASH_PIXEL_1 <= rightB)
		{
			if (topA + TRASH_PIXEL_2 <= bottomB && topA + TRASH_PIXEL_2 >= topB)
			{
				collide = true;
			}
			
			if (bottomA - TRASH_PIXEL_2 >= topB && bottomA - TRASH_PIXEL_2 <= bottomB)
			{
				collide = true;
			}
		}
	}

	return collide;
}

bool checkEnemyCollision(Character character,
	Patterns enemy1,
	Patterns enemy2, 
	Patterns enemy3,
	SDL_Rect* char_clip,
	SDL_Rect* enemy_clip)
{
	if (checkCollision(character, char_clip, enemy1))
	{
		return true;
	}
	if (checkCollision(character, char_clip, enemy2))
	{
		return true;
	}
	if (checkCollision(character, char_clip, enemy3, enemy_clip))
	{
		return true;
	}
	return false;
}

void generateEgg(Egg& egg,
	SDL_Rect(&gEggClips)[EGG_FRAMES],
	Egg& bigegg,
	SDL_Rect(&gBEggClips)[EGG_FRAMES],
	SDL_Renderer * gRenderer)
{
	egg.loadFromFile("imgs/enemy/hatch.png", gRenderer);
	{
		gEggClips[0].x = EGG_WIDTH * 0;
		gEggClips[0].y = 0;
		gEggClips[0].w = EGG_WIDTH;
		gEggClips[0].h = EGG_HEIGHT;

		gEggClips[1].x = EGG_WIDTH * 1;
		gEggClips[1].y = 0;
		gEggClips[1].w = EGG_WIDTH;
		gEggClips[1].h = EGG_HEIGHT;

		gEggClips[2].x = EGG_WIDTH * 2;
		gEggClips[2].y = 0;
		gEggClips[2].w = EGG_WIDTH;
		gEggClips[2].h = EGG_HEIGHT;

		gEggClips[3].x = EGG_WIDTH * 3;
		gEggClips[3].y = 0;
		gEggClips[3].w = EGG_WIDTH;
		gEggClips[3].h = EGG_HEIGHT;
	}
	bigegg.loadFromFile("imgs/enemy/bigegg.png", gRenderer);
	{
		gBEggClips[0].x = 60 * 0;
		gBEggClips[0].y = 0;
		gBEggClips[0].w = 60;
		gBEggClips[0].h = 60;

		gBEggClips[1].x = 60 * 1;
		gBEggClips[1].y = 0;
		gBEggClips[1].w = 60;
		gBEggClips[1].h = 60;

		gBEggClips[2].x = 60 * 2;
		gBEggClips[2].y = 0;
		gBEggClips[2].w = 60;
		gBEggClips[2].h = 60;

		gBEggClips[3].x = 60 * 3;
		gBEggClips[3].y = 0;
		gBEggClips[3].w = 60;
		gBEggClips[3].h = 60;
	}
}

bool checkEggCollision(Character character,
	SDL_Rect* char_clip,
	Egg egg,
	SDL_Rect* egg_clip, int& eggained, Mix_Chunk *gGainEgg)
{
	bool collide = false;
	
	int leftA = character.getPosX();
	int rightA = character.getPosX() + char_clip->w;
	int topA = character.getPosY();
	int bottomA = character.getPosY() + char_clip->h;

	if (egg.getType() == EGG)
	{	
		int leftB = egg.getPosX();
		int rightB = egg.getPosX() + egg_clip->w;
		int topB = egg.getPosY();
		int bottomB = egg.getPosY() + egg_clip->h;

		if (rightA - 10 >= leftB && leftA + 10 <= rightB)
		{
			if ((topA + 10 <= bottomB && topA + 10 >= topB) || bottomA - 10 <= bottomB && bottomA - 10 >= topB)
			{
				collide = true;
				eggained ++;
				Mix_PlayChannel(-1,gGainEgg,0);
			}
		}
	}
	else if (egg.getType() == BIG_EGG)
	{
		int leftB = egg.getPosX();
		int rightB = egg.getPosX() + egg_clip->w;
		int topB = egg.getPosY();
		int bottomB = egg.getPosY() + egg_clip->h;

		if (rightA - 15 >= leftB && leftA + 15 <= rightB)
		{
			if ((topA + 15 <= bottomB && topA + 15 >= topB) || bottomA - 15 <= bottomB && bottomA - 15 >= topB)
			{
				collide = true;
				eggained += 5;
				Mix_PlayChannel(-1,gGainEgg,0);
			}
		}
	}
	return collide;
}



void controlCharFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_CHAR >= RUNNING_FRAMES)
	{
		frame = 0;
	}
}

void controlEnemyFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY >= FLYING_FRAMES)
	{
		frame = 0;
	}
}

void controlEggFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / 5 >= EGG_FRAMES)
	{
		frame = 0;
	}
}