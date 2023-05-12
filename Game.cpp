#include "Game.h"

std::string getHighScoreFromFile(std::string path)
{
	std::fstream highScoreFile;
	std::string highscore;

	highScoreFile.open(path, std::ios::in);
	highScoreFile >> highscore;

	return highscore;
}

void updateHighScore(std::string path,
	const int& score, 
	const std::string& prevHighscore)
{
	int oldHighScore = 0;
	std::fstream highScoreFile;
	std::string newHighScore;
	std::stringstream convertToInt(prevHighscore);

	highScoreFile.open(path, std::ios::out);

	convertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	highScoreFile << newHighScore;
}

int updateGameTimeAndScore(int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}
	
	time += TIME_INCREASEMENT;

	return time;
}

void renderScrollingBackground(int& scrollingOffset,
	const int acceleration,
	LTexture gBackgroundTexture,
	SDL_Renderer* gRenderer)
{
	scrollingOffset -= GROUND_SPEED + acceleration;
	if (scrollingOffset < -gBackgroundTexture.getWidth())
	{
		scrollingOffset = 0;
	}
	gBackgroundTexture.Render(scrollingOffset, 0, gRenderer);
	gBackgroundTexture.Render(scrollingOffset + gBackgroundTexture.getWidth(), 0, gRenderer);
}

void handlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.isInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton, 
	Button& BackButton, 
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &Quit_game, 
	Mix_Chunk *gClick)
{
	if (HelpButton.isInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_game = true;
						close();
					}

					if (BackButton.isInside(e, SMALL_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
						{	
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
						}
						break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.isInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State,
	Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.isInside(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
					Mix_ResumeMusic();
					Game_State = true;
					Back_To_Game = true;
				}
				break;
				
				}
			}
			else
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			}
		
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}

void handlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer, 
	SDL_Rect (&gContinueButton)[BUTTON_TOTAL], 
	Button& PauseButton, 
	Button ContinueButton, 
	LTexture gContinueButtonTexture, 
	bool &Game_State, 
	Mix_Chunk *gClick)
{
	if (PauseButton.isInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			Mix_PauseMusic();
			break;
		case SDL_MOUSEBUTTONUP:
			Game_State = false;
			handleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, gClick);
			break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void generateEnemy(Patterns& enemy1,
	Patterns& enemy2,
	Patterns& enemy3,
	//Patterns& egg,
	SDL_Rect(&gEnemyClips)[FLYING_FRAMES], 
	//SDL_Rect(&gEggClips)[EGG_FRAMES],
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
	/*egg.loadFromFile("imgs/enemy/hatch.png", gRenderer);
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
	}*/
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
	else
	{
		const int TRASH_PIXEL_1 = 25;
		const int TRASH_PIXEL_2 = 20;

		int leftB = pattern.getPosX() + TRASH_PIXEL_1;
		int rightB = pattern.getPosX() + pattern_clip->w - TRASH_PIXEL_1;
		int topB = pattern.getPosY();
		int bottomB = pattern.getPosY() + pattern_clip->h;

		if (rightA >= leftB && leftA <= rightB)
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
	/*else 
	{	
		const int TRASH_PIXEL_1 = 20;
		const int TRASH_PIXEL_2 = 20;

		int leftB = pattern.getPosX();
		int rightB = pattern.getPosX() + pattern_clip->w;
		int topB = pattern.getPosY();
		int bottomB = pattern.getPosY() + pattern_clip->h;

		if (rightA - TRASH_PIXEL_1 == leftB || bottomA - TRASH_PIXEL_2 == topB)
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
	}*/

	return collide;
}

/*bool checkEggCollision(Character character,
	SDL_Rect* char_clip,
	Patterns egg,
	SDL_Rect* egg_clip)
{
	if (checkCollision(character, char_clip, egg, egg_clip))
	{
		return true;
	}
	return false;
}*/

/*int updateEggGained(Character character,
	SDL_Rect* char_clip,
	Patterns egg,
	SDL_Rect* egg_clip,
	int& egg_gained)
{	
	if (checkEggCollision(character, char_clip, egg, egg_clip))
	{
		egg_gained ++;
	}
	return egg_gained;
}*/

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

/*void controlEggFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / 5 >= EGG_FRAMES)
	{
		frame = 0;
	}
}*/

/*void drawEggGained(LTexture gEggPic,
	LTexture gEggGainedScore, 
	SDL_Color textColor, 
	SDL_Renderer *gRenderer, 
	TTF_Font *gFont, 
	const int& egggained)
{
	gEggPic.Render(350, 65 ,gRenderer);
	if (gEggGainedScore.loadFromRenderedText(std::to_string(egggained), gFont, textColor, gRenderer))
	{
		gEggGainedScore.Render(400, TEXT_2_POSY,gRenderer);
	}
}*/

void drawPlayerScore(LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont, 
	const int& score)
{
	if (gScoreTexture.loadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
}

void drawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const std::string& HighScore)
{
	gTextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
	if (gHighScoreTexture.loadFromRenderedText(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
	}
}

void drawEndGameSelection(LTexture gLoseTextTexture,
	LTexture gIntructTextTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}
			}

			gLoseTextTexture.Render(400, 150, gRenderer);
			gIntructTextTexture.Render(150, 200, gRenderer);
			SDL_RenderPresent(gRenderer);
		}
	}
}
