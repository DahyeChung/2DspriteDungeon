#include "GameCore.h"
#include <stdio.h>

namespace DungeonGame
{
	SDL_Texture* pTexture = nullptr;
	Vector2d testPosition = Vector2d(100.0f, 120.0f); 
	Vector2d testDirection = Vector2d(0.0f, 1.0f); 



	float testX = 100;

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;
		SDL_Surface* pBmp = SDL_LoadBMP("Assets\\Sprites\\Hero\\Total\\Walk\\bmp\\HeroKnight_8.bmp"); // 적절한 경로로 수정
		if (pBmp == nullptr)
		{
			printf("Fail to load images");
			return;
		}

		SDL_SetColorKey(pBmp, SDL_TRUE, SDL_MapRGB(pBmp->format, 0, 0, 0));
		pTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
		SDL_FreeSurface(pBmp);
	}
	void GetInput(PlayerState& playerState, WorldState& worldState)
	{
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				playerState.HasFinishedGame = true;
			else if (e.type == SDL_KEYDOWN)
			{	
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.HasFinishedGame = true;
					break;
				}

			}
		}
	}
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
	{
		testDirection.Normalize();
		testPosition += testDirection * 50.0f * deltaSeconds;
	}
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{	
		SDL_RenderClear(pRenderer);

		SDL_Rect destRect = { (int)testPosition.X, (int)testPosition.Y,42, 39 };
		SDL_RenderCopy(pRenderer, pTexture, nullptr, &destRect);

		SDL_RenderPresent(pRenderer);
	}
	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		SDL_DestroyTexture(pTexture);
	}

}
