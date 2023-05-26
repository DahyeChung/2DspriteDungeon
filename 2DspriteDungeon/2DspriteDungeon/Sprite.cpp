#include "Sprite.h"
#include "stdio.h"

using namespace DungeonGame;

Sprite::Sprite() :
	MyTexture(nullptr),
	Position(0.0f, 0.0f),
	Size(72.0f, 72.0f),
	Visible(true)
{

}

void Sprite::Initialize(SDL_Renderer* pRenderer, const std::string& imageFilepath)
{
	SDL_Surface* pBmp = SDL_LoadBMP(imageFilepath.c_str()); // multiple sprites
	if (pBmp == nullptr)
	{
		printf("Fail to load images");
		return;
	}

	SDL_SetColorKey(pBmp, SDL_TRUE, SDL_MapRGB(pBmp->format, 0, 0, 0));
	MyTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
	SDL_FreeSurface(pBmp);

}
void Sprite::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{

}
void Sprite::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
{
	SDL_Rect destRect = { (int)Position.X, (int)Position.Y,(int)Size.X, (int)Size.Y};
	SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
}
void Sprite::Cleanup()
{
	SDL_DestroyTexture(MyTexture);

}