#include "handleButtons.h"

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
			Mix_PlayChannel(-1, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleOptionsButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& OptionsButton, 
	Button& BackButton, 
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &Quitgame, 
	Mix_Chunk *gClick)
{
	if (OptionsButton.isInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			OptionsButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			OptionsButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(-1, gClick, 0);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quitgame = true;
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
							Mix_PlayChannel(-1, gClick, 0);
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
		OptionsButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void handleQuitButton(SDL_Event* e,
	Button& QuitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (QuitButton.isInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			QuitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			QuitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(-1, gClick, 0);
			break;
		}
	}
	else
	{
		QuitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}