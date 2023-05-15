#ifndef RENDER_H_
#define RENDER_H_

#include "Functions.h"
#include "LTexture.h"
#include "Button.h"
#include "Pattern.h"
#include "Mainchar.h"
#include "Egg.h"
#include "Gen_Col.h"

bool init();
bool loadMedia();
void close();

void renderScrollingBackground(int& scrollingOffset,
    const int acceleration,
    LTexture gBackgroundTexture,
    SDL_Renderer* gRenderer);

std::string getHighScoreFromFile(std::string path);

void updateHighScore(std::string path,
    const int& score, 
    const std::string& prevHighscore);

int updateGameTimeAndScore(int& time, int& speed, int& score);

void drawEggGained(LTexture gEggPic,
	LTexture gEggGainedScore, 
	SDL_Color textColor, 
	SDL_Renderer *gRenderer, 
	TTF_Font *gFont, 
	const int& egggained);

void drawPlayerScore(LTexture gScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const int& score);

void drawPlayerHighScore(LTexture gTextTexture,
    LTexture gHighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont, 
    const std::string& HighScore);

void drawEndGameSelection(LTexture gLoseTextTexture,
    LTexture gIntructTextTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    bool& Play_Again);

#endif 