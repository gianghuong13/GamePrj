#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 360
#define MAX_HEIGHT 180


#define SPEED_INCREASEMENT 1
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 5.5
#define ENEMY_SPEED 5.5
#define MAX_ENEMY_WIDTH 80


#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2


const std::string WINDOW_TITLE = "DINOSAUR";

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 455;

const int COMMON_BUTTON_WIDTH = 125;
const int COMMON_BUTTON_HEIGHT = 41;

const int SMALL_BUTTON_WIDTH = 50;
const int SMALL_BUTTON_HEIGHT = 50;

const int ENEMY_WIDTH = 31;
const int ENEMY_HEIGHT = 31;
const int CHAR_WIDTH = 62;
const int CHAR_HEIGHT = 62;
const int EGG_WIDTH = 48;
const int EGG_HEIGHT = 48;

const int TITLE_POSX = 0;
const int TITLE_POSY = 0;
const int PLAY_BUTON_POSX = 400;
const int PLAY_BUTTON_POSY= 250;
const int HELP_BUTTON_POSX = 400;
const int HELP_BUTTON_POSY = 300;
const int EXIT_BUTTON_POSX = 400;
const int EXIT_BUTTON_POSY = 350;
const int BACK_BUTTON_POSX = 40;
const int BACK_BUTTON_POSY = 200;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;

const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 70;
const int SCORE_POSX = 780;
const int SCORE_POSY = 70;
const int HIGH_SCORE_POSX = 710;
const int HIGH_SCORE_POSY = 70;


const int RUNNING_FRAMES = 6;
const int FLYING_FRAMES = 4;
const int RENDER_DRAW_COLOR = 0Xff;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

#endif 