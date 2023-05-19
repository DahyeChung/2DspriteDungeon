#include "GameCore.h"
#include <stdio.h>

namespace DungeonGame
{
	SDL_Texture* pTexture = nullptr;
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
		testX += 20 * deltaSeconds;
	}
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{	
		SDL_RenderClear(pRenderer);

		SDL_Rect destRect = { testX, 150,42, 39 };
		SDL_RenderCopy(pRenderer, pTexture, nullptr, &destRect);

		SDL_RenderPresent(pRenderer);
	}
	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		SDL_DestroyTexture(pTexture);
	}

}
