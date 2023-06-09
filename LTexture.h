#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "Functions.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

    SDL_Texture* getTexture() const {return mTexture;}

	bool loadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

	int getWidth();

	int getHeight();


private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif // !LTEXTURE_H_