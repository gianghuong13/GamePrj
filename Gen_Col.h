#include "Functions.h"
#include "Button.h"
#include "Pattern.h"
#include "Mainchar.h"
#include "Egg.h"

void generateEnemy(Patterns& enemy1,
    Patterns& enemy2,
    Patterns& enemy3,
    SDL_Rect(&gEnemyClips)[FLYING_FRAMES],
    SDL_Renderer* gRenderer);

bool checkCollision(Character character,
    SDL_Rect* char_clip,
    Patterns pattern,
    SDL_Rect*pattern_clip = nullptr);

bool checkEnemyCollision(Character character,
    Patterns enemy1,
    Patterns enemy2,
    Patterns enemy3,
    SDL_Rect* char_clip,
    SDL_Rect* enemy_clip = nullptr);

void generateEgg(Egg& egg,
	SDL_Rect(&gEggClips)[EGG_FRAMES],
	Egg& bigegg,
	SDL_Rect(&gBEggClips)[EGG_FRAMES],
	SDL_Renderer * gRenderer);

bool checkEggCollision(Character character,
	SDL_Rect* char_clip,
	Egg egg,
	SDL_Rect* egg_clip, int& eggained, Mix_Chunk *gGainEgg);

void controlCharFrame(int& frame);

void controlEnemyFrame(int& frame);

void controlEggFrame(int &frame);