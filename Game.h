#ifndef GAME_H_
#define GAME_H_

#include "Functions.h"
#include "Button.h"
#include "Pattern.h"
#include "Mainchar.h"

bool init();
bool loadMedia();
void close();

std::string getHighScoreFromFile(std::string path);

void updateHighScore(std::string path,
    const int& score, 
    const std::string& prevHighscore);

int updateGameTimeAndScore(int& time, int& speed, int& score);

/*int updateEggGained(Character character,
	SDL_Rect* char_clip,
	Patterns egg,
	SDL_Rect* egg_clip,
	int& egg_gained);*/

void renderScrollingBackground(int& scrollingOffset,
    const int acceleration,
    LTexture gBackgroundTexture,
    SDL_Renderer* gRenderer);

void handlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play,
    Mix_Chunk* gClick);

void handleHelpButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_TOTAL],
    Button& HelpButton,
    Button& BackButton,
    LTexture gInstructionTexture,
    LTexture gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& Quit_game,
    Mix_Chunk* gClick);

void handleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& Quit,
    Mix_Chunk* gClick);

void handleContinueButton(Button ContinueButton,
    LTexture gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    bool& Game_State, Mix_Chunk* gClick);

void handlePauseButton(SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    Button& PauseButton,
    Button ContinueButton,
    LTexture gContinueButtonTexture,
    bool& game_state,
    Mix_Chunk* gClick);

void generateEnemy(Patterns& enemy1,
    Patterns& enemy2,
    Patterns& enemy3,
    //Patterns& egg,
    SDL_Rect(&gEnemyClips)[FLYING_FRAMES],
    //SDL_Rect(&gEggClips)[EGG_FRAMES],
    SDL_Renderer* gRenderer);


bool checkCollision(Character character,
    SDL_Rect* char_clip,
    Patterns pattern,
    SDL_Rect*pattern_clip = nullptr);

/*bool checkEggCollision(Character character,
    SDL_Rect* char_clip,
    Patterns egg,
    SDL_Rect* egg_clip = nullptr);*/

bool checkEnemyCollision(Character character,
    Patterns enemy1,
    Patterns enemy2,
    Patterns enemy3,
    SDL_Rect* char_clip,
    SDL_Rect* enemy_clip = nullptr);

void controlCharFrame(int& frame);

void controlEnemyFrame(int& frame);

/*void controlEggFrame(int &frame);

void drawEggGained(LTexture gEggPic,
	LTexture gEggGainedScore, 
	SDL_Color textColor, 
	SDL_Renderer *gRenderer, 
	TTF_Font *gFont, 
	const int& egggained);*/

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