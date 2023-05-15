#include "Render.h"

void renderScrollingBackground(int& scrollingOffset,
	const int acceleration,
	LTexture gBackgroundTexture,
	SDL_Renderer* gRenderer)
{
	scrollingOffset -= BACKGROUND_SPEED + acceleration;
	if (scrollingOffset < -gBackgroundTexture.getWidth())
	{
		scrollingOffset = 0;
	}
	gBackgroundTexture.Render(scrollingOffset, 0, gRenderer);
	gBackgroundTexture.Render(scrollingOffset + gBackgroundTexture.getWidth(), 0, gRenderer);
}


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

void drawEggGained(LTexture gEggPic,
	LTexture gEggGainedScore, 
	SDL_Color textColor, 
	SDL_Renderer *gRenderer, 
	TTF_Font *gFont, 
	const int& egggained)
{
	gEggPic.Render(330, 50 ,gRenderer);
	if (gEggGainedScore.loadFromRenderedText(std::to_string(egggained), gFont, textColor, gRenderer))
	{
		gEggGainedScore.Render(400, TEXT_2_POSY,gRenderer);
	}
}

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

