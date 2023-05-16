#ifndef MAIN_H_
#define MAIN_H_

#include "Functions.h"
#include "Render.h"
#include "LTexture.h"
#include "Button.h"
#include "handleButtons.h"
#include "Mainchar.h"
#include "Pattern.h"
#include "Egg.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gGainEgg = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gOptionsButton[BUTTON_TOTAL];
SDL_Rect gQuitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips[FLYING_FRAMES];
SDL_Rect gEggClips[EGG_FRAMES];
SDL_Rect gBigEggClips[EGG_FRAMES];

LTexture gTitleTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture;
LTexture gCharacterTexture;
LTexture gPlayButtonTexture;
LTexture gOptionsButtonTexture;
LTexture gQuitButtonTexture;
LTexture gBackButtonTexture;
LTexture gLoseTexture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;
LTexture gLoseTextTexture;
LTexture gIntructTextTexture;
LTexture gEggTexture;
LTexture gBigEggTexture;
LTexture gEggPic;
LTexture gEggGainedScore;
LTexture gDeadTexture;

Button PlayButton(PLAY_BUTTON_X, PLAY_BUTTON_Y);
Button OptionsButton(HELP_BUTTON_X, HELP_BUTTON_Y);
Button QuitButton(EXIT_BUTTON_X, EXIT_BUTTON_Y);
Button BackButton(BACK_BUTTON_X, BACK_BUTTON_Y);

Character character;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Can not initialize SDL" << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Can not create window" << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				std::cout << "Can not creater renderer" << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "Can not initialize SDL_image" << IMG_GetError() << std::endl;
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					std::cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError();
					success = false;
				}

				if (TTF_Init() == -1)
				{
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError();
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	gMusic = Mix_LoadMUS("sound/music.wav");
	if (gMusic == nullptr)
	{
		std::cout << "Failed to load background music" << Mix_GetError() << std::endl;
		success = false;
	}

	gMenuMusic = Mix_LoadMUS("sound/music.wav");
	if (gMenuMusic == nullptr)
	{
		std::cout << "Failed to load menu music" << Mix_GetError() << std::endl;
		success = false;
	}

	gClick = Mix_LoadWAV("sound/buttonSound.wav");
	if (gClick == nullptr)
	{
		std::cout << "Failed to load button click music" << Mix_GetError() << std::endl;
		success = false;
	}

	gJump = Mix_LoadWAV("sound/jump.wav");
	if (gJump == nullptr)
	{
		std::cout << "Failed to load jump sound" << Mix_GetError() << std::endl;
		success = false;
	}

	gGainEgg = Mix_LoadWAV("sound/collectegg.wav");
	if (gGainEgg == nullptr)
	{
		std::cout << "Failed to load egg collect sound" << Mix_GetError() << std::endl;
		success = false;
	}

	gLose = Mix_LoadWAV("sound/loseHP.wav");
	if (gLose == nullptr)
	{
		std::cout << "Failed to load button lose sound" << Mix_GetError() << std::endl;
		success = false;
	}

	else
	{
		gFont = TTF_OpenFont("font/m6x11.ttf", 35);
		if (gFont == NULL)
		{
			std::cout << "Failed to load font" << Mix_GetError() << std::endl;
			success = false;
		}
		else
		{
			if (!gText2Texture.loadFromRenderedText("HI ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text2 texture" << std::endl;
				success = false;
			}

			if (!gLoseTextTexture.loadFromRenderedText("Game Over !", gFont, textColor, gRenderer)){
				std::cout << "Failed to render lose text texture" << std::endl;
				success = false;
			}

			if (!gIntructTextTexture.loadFromRenderedText("Press SPACE bar to restart or ESC to quit game!", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to load intructions text after losing" << std::endl;
				success = false;
			}

			if (!gDeadTexture.loadFromFile("imgs/character/dead.png", gRenderer)){
				std::cout << "Failed to load dead texture" << std::endl;
				success = false;
			}

			if (!gEggPic.loadFromFile("imgs/enemy/egg.png",gRenderer))
			{
				std::cout << "Failed to load egg picture" << std::endl;
				success = false;
			}

			if (!gTitleTexture.loadFromFile("imgs/background/title.png", gRenderer))
			{
				std::cout << "Failed to load title image" << std::endl;
				success = false;
			}

			if(!gBackgroundTexture.loadFromFile("imgs/background/background.png",gRenderer))
			{
				std::cout << "Failed to load title image" << std::endl;
				success = false;
			}


			if (!gInstructionTexture.loadFromFile("imgs/background/intruction.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gPlayButtonTexture.loadFromFile("imgs/button/largebutton1.png", gRenderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i].x = 125 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 125;
					gPlayButton[i].h = 41;
				}
			}

			if (!gOptionsButtonTexture.loadFromFile("imgs/button/largebutton2.png", gRenderer))
			{
				std::cout << "Failed to load help_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gOptionsButton[i].x = 125 * i;
					gOptionsButton[i].y = 0;
					gOptionsButton[i].w = 125;
					gOptionsButton[i].h = 40;
				}
			}

			if (!gQuitButtonTexture.loadFromFile("imgs/button/largebutton3.png", gRenderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gQuitButton[i].x = 125 * i;
					gQuitButton[i].y = 0;
					gQuitButton[i].w = 125;
					gQuitButton[i].h = 40;
				}
			}

			if (!gBackButtonTexture.loadFromFile("imgs/button/smallbuttonback.png", gRenderer))
			{
				std::cout << "Failed to load back_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = 50 * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = 50;
					gBackButton[i].h = 50;
				}
			}

			if (!gCharacterTexture.loadFromFile("imgs/character/move.png", gRenderer))
			{
				std::cout << "Failed to load character_run image." << std::endl;
				success = false;
			}
			else 
			{
				gCharacterClips[0].x = CHAR_WIDTH * 0;
				gCharacterClips[0].y = 0;
				gCharacterClips[0].w = CHAR_WIDTH;
				gCharacterClips[0].h = CHAR_HEIGHT;

				gCharacterClips[1].x = CHAR_WIDTH * 1;
				gCharacterClips[1].y = 0;
				gCharacterClips[1].w = CHAR_WIDTH;
				gCharacterClips[1].h = CHAR_HEIGHT;

				gCharacterClips[2].x = CHAR_WIDTH * 2;
				gCharacterClips[2].y = 0;
				gCharacterClips[2].w = CHAR_WIDTH;
				gCharacterClips[2].h = CHAR_HEIGHT;

				gCharacterClips[3].x = CHAR_WIDTH * 3;
				gCharacterClips[3].y = 0;
				gCharacterClips[3].w = CHAR_WIDTH;
				gCharacterClips[3].h = CHAR_HEIGHT;

				gCharacterClips[4].x = CHAR_WIDTH * 4;
				gCharacterClips[4].y = 0;
				gCharacterClips[4].w = CHAR_WIDTH;
				gCharacterClips[4].h = CHAR_HEIGHT;

				gCharacterClips[5].x = CHAR_WIDTH * 5;
				gCharacterClips[5].y = 0;
				gCharacterClips[5].w = CHAR_WIDTH;
				gCharacterClips[5].h = CHAR_HEIGHT;
			}
		}
	}
	return success;
}

void close()
{
	gTitleTexture.Free();
	gInstructionTexture.Free();
	gCharacterTexture.Free();
	gPlayButtonTexture.Free();
	gOptionsButtonTexture.Free();
	gQuitButtonTexture.Free();
	gBackButtonTexture.Free();
	gLoseTextTexture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gHighScoreTexture.Free();
	gBackgroundTexture.Free();
	gEggTexture.Free();
	gBigEggTexture.Free();
	gEggPic.Free();
	gDeadTexture.Free();

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	Mix_FreeChunk(gGainEgg);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;
	gGainEgg = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

#endif
