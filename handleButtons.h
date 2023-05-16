#include "Functions.h"
#include "LTexture.h"
#include "Button.h"
#include "Render.h"

void handlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play,
    Mix_Chunk* gClick);

void handleOptionsButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_TOTAL],
    Button& OptionsButton,
    Button& BackButton,
    LTexture gInstructionTexture,
    LTexture gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& Quitgame,
    Mix_Chunk* gClick);

void handleQuitButton(SDL_Event* e,
    Button& QuitButton,
    bool& Quit,
    Mix_Chunk* gClick);
