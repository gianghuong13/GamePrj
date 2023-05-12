#include "Functions.h"
#include "Game.h"
#include "LTexture.h"
#include "Button.h"
#include "Mainchar.h"
#include "Pattern.h"


SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
//Mix_Chunk* gGainEgg = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips[FLYING_FRAMES];
SDL_Rect gDeadClips[5];
//SDL_Rect gEggClips[EGG_FRAMES];


LTexture gMenuTexture;
LTexture gTitleTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture;
LTexture gCharacterTexture;
LTexture gCharacterDashTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gLoseTexture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;
LTexture gLoseTextTexture;
LTexture gIntructTextTexture;
//LTexture gEggTexture;
//LTexture gEggPic;
//LTexture gEggGainedScore;
LTexture gDeadTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);

Character character;
Character deadChar;

int main(int argc, char* argv[])
{
	if (!init())
	{
		std::cout << "Failed to intialize" << std::endl;
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "Failed to load media" << std::endl;
		}
		else
		{
			bool quitMenu = false;
			bool playAgain = false;

			Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
			while (!quitMenu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						quitMenu = true;
					}

					bool quitGame = false;
					handlePlayButton(&e_mouse, PlayButton, quitMenu, playAgain, gClick);
						
					handleHelpButton(&e_mouse, gBackButton,
									 HelpButton, BackButton, 
									 gInstructionTexture, gBackButtonTexture,
									 gRenderer, quitGame, gClick);

					handleExitButton(&e_mouse, ExitButton, quitMenu, gClick);

					if (quitGame == true)
					{
						return 0;
					}
				}

				//renderScrollingBackground(scrollingOffset, acceleration, gBackgroundTexture, gRenderer);
				gTitleTexture.Render(TITLE_POSX,TITLE_POSY,gRenderer);
				
				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer);
			}

			while (playAgain)
			{
				srand(time(NULL));
				int time = 0;
				int score = 0;
				int acceleration = 0;
				int frameCharacter = 0;
				int frameEnemy = 0;
				int frameEgg = 0;
				int egggained = 0;
				std::string highscore = getHighScoreFromFile("highscore.txt");
				
				SDL_Event e;
				Patterns enemy1(ON_GROUND_ENEMY1);
				Patterns enemy2(ON_GROUND_ENEMY2);
				Patterns enemy3(IN_AIR_ENEMY);
				
				Mix_PlayMusic(gMusic, IS_REPEATITIVE);
				generateEnemy(enemy1, enemy2, enemy3, gEnemyClips, gRenderer);
				int scrollingOffset = 0;
								

				bool quit = false;
				bool gameState = true;
				while (!quit)
				{
					if (gameState)
					{
						updateGameTimeAndScore(time, acceleration, score);

						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								quit = true;
								playAgain = false;
							}

							handlePauseButton(&e, gRenderer, gContinueButton,
								PauseButton, ContinueButton,
								gContinueButtonTexture, gameState, gClick);

							character.handleEvent(e, gJump);
						}
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						renderScrollingBackground(scrollingOffset, acceleration, gBackgroundTexture, gRenderer);
						
						character.Move();
						SDL_Rect* currentClip_Character = nullptr;
			
						if (character.onGround())
						{
							currentClip_Character = &gCharacterClips[frameCharacter / SLOW_FRAME_CHAR];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}
						else
						{
							currentClip_Character = &gCharacterClips[3];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}


						enemy1.Move(acceleration);
						enemy1.Render(gRenderer);
			
						enemy2.Move(acceleration);
						enemy2.Render(gRenderer);

						SDL_Rect* currentClip_Enemy = &gEnemyClips[frameEnemy / SLOW_FRAME_ENEMY];
						enemy3.Move(acceleration);
						enemy3.Render(gRenderer, currentClip_Enemy);

						/*SDL_Rect* currentClip_Egg = &gEggClips[frameEnemy / 5];
						egg.Move(acceleration);
						egg.Render(gRenderer, currentClip_Egg);*/

						SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
						PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);

						//drawEggGained(gEggPic, gEggGainedScore, textColor, gRenderer, gFont, egggained);
						drawPlayerScore(gScoreTexture, textColor, gRenderer, gFont, score);
						drawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

						/*if (checkEggCollision(character, currentClip_Character, egg, currentClip_Egg))
						{
							Mix_PlayChannel(MIX_CHANNEL, gGainEgg, NOT_REPEATITIVE);
							egggained ++;
						}*/

						

						if (checkEnemyCollision(character,
							enemy1, enemy2, enemy3,
							currentClip_Character, currentClip_Enemy))
						{
							gDeadTexture.Render(character.getPosX() - 5, character.getPosY() - 5, gRenderer);
							Mix_PauseMusic();
							Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
							updateHighScore("highscore.txt", score, highscore);
							quit = true;
						}


						SDL_RenderPresent(gRenderer);

						controlCharFrame(frameCharacter);
						controlEnemyFrame(frameEnemy);
						//controlEggFrame(frameEgg);
					}
				}

				drawEndGameSelection(gLoseTextTexture, gIntructTextTexture, &e, gRenderer, playAgain);
				if (!playAgain)
				{
					enemy1.~Patterns();
					enemy2.~Patterns();
					enemy3.~Patterns();
					//egg.~Patterns();
				}
			}
		}
	}
	close();

	return 0;
}


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

	/*gGainEgg = Mix_LoadWAV("sound/collectegg.wav");
	if (gGainEgg == nullptr)
	{
		std::cout << "Failed to load egg collect sound" << Mix_GetError() << std::endl;
		success = false;
	}*/

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

			/*if (!gEggPic.loadFromFile("imgs/enemy/egg.png",gRenderer))
			{
				std::cout << "Failed to load egg picture" << std::endl;
				success = false;
			}*/

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

			if (!gHelpButtonTexture.loadFromFile("imgs/button/largebutton2.png", gRenderer))
			{
				std::cout << "Failed to load help_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i].x = 125 * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = 125;
					gHelpButton[i].h = 40;
				}
			}

			if (!gExitButtonTexture.loadFromFile("imgs/button/largebutton3.png", gRenderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = 125 * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = 125;
					gExitButton[i].h = 40;
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

			

			if (!gPauseButtonTexture.loadFromFile("imgs/button/smallbuttoncontinue.png", gRenderer))
			{
				std::cout << "Failed to load pause_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i].x = 50 * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = 50;
					gPauseButton[i].h = 47;
				}
			}

			if (!gContinueButtonTexture.loadFromFile("imgs/button/smallbuttonpause.png", gRenderer))
			{
				std::cout << "Failed to load continue_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gContinueButton[i].x = 50 * i;
					gContinueButton[i].y = 0;
					gContinueButton[i].w = 50;
					gContinueButton[i].h = 50;
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
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTextTexture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gHighScoreTexture.Free();
	gBackgroundTexture.Free();
	//gEggTexture.Free();
	//gEggPic.Free();
	gDeadTexture.Free();

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	//Mix_FreeChunk(gGainEgg);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;
	//gGainEgg = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
