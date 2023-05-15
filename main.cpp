#include "main.h"

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
			bool isPlayed = false;

			Mix_PlayMusic(gMenuMusic, -1);
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
					handlePlayButton(&e_mouse, PlayButton, quitMenu, isPlayed, gClick);
						
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

				gTitleTexture.Render(TITLE_POSX,TITLE_POSY,gRenderer);
				
				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer);
			}

			while (isPlayed)
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
				Egg egg(EGG);
				Egg bigegg(BIG_EGG);
				
				Mix_PlayMusic(gMusic, -1);
				generateEnemy(enemy1, enemy2, enemy3, gEnemyClips, gRenderer);
				generateEgg(egg, gEggClips, bigegg, gBigEggClips, gRenderer);
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
								isPlayed = false;
							}

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

						SDL_Rect* currentClip_Egg = &gEggClips[frameEnemy / 5];
						egg.Move(acceleration);
						egg.Render(gRenderer, currentClip_Egg);
						
						SDL_Rect* currentClip_BigEgg = &gBigEggClips[frameEnemy / 5];
						bigegg.Move(acceleration);
						bigegg.Render(gRenderer, currentClip_BigEgg);

						drawEggGained(gEggPic, gEggGainedScore, textColor, gRenderer, gFont, egggained);
						drawPlayerScore(gScoreTexture, textColor, gRenderer, gFont, score);
						drawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

						
						if (checkEggCollision(character, currentClip_Character, egg, currentClip_Egg, egggained, gGainEgg))
						{
							egg.Delete();
						}
						if (checkEggCollision(character, currentClip_Character, bigegg, currentClip_BigEgg, egggained, gGainEgg))
						{
							bigegg.Delete();
						}

						if (checkEnemyCollision(character,
							enemy1, enemy2, enemy3,
							currentClip_Character, currentClip_Enemy))
						{
							gDeadTexture.Render(character.getPosX() - 5, character.getPosY() - 5, gRenderer);
							Mix_PauseMusic();
							Mix_PlayChannel(-1, gLose, 0);
							updateHighScore("highscore.txt", score, highscore);
							quit = true;
						}


						SDL_RenderPresent(gRenderer);

						controlCharFrame(frameCharacter);
						controlEnemyFrame(frameEnemy);
						controlEggFrame(frameEgg);
					}
				}

				drawEndGameSelection(gLoseTextTexture, gIntructTextTexture, &e, gRenderer, isPlayed);
				if (!isPlayed)
				{
					enemy1.~Patterns();
					enemy2.~Patterns();
					enemy3.~Patterns();
					egg.~Egg();
				}
			}
		}
	}
	close();

	return 0;
}
