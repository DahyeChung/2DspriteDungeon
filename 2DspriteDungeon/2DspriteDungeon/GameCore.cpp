#include "GameCore.h"
#include <stdio.h>
#include "Sprite.h"

namespace DungeonGame
{
	SDL_Texture* pTexture = nullptr;

	Sprite testSprite; //스프라이트 여러개
	Sprite testSprite2;
	Vector2d testDirection = Vector2d(0.0f, 1.0f); 



	float testX = 100;

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;

		//Sprite 1
		testSprite.Initialize(pRenderer, "Assets\\Sprites\\Hero\\Total\\Walk\\bmp\\HeroKnight_8.bmp");
		testSprite.Position = Vector2d(100.0f, 120.0f);
		
		//Sprite 2
		testSprite2.Initialize(pRenderer, "나중에 경로 넣어.bmp");
		testSprite2.Position = Vector2d(100.0f, 220.0f);






	
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
		testSprite.Position += testDirection * 50.0f * deltaSeconds;

		//여러가지 sprites
		testSprite.Update(deltaSeconds, playerState, worldState);
		testSprite2.Update(deltaSeconds, playerState, worldState);
	}


	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{	
		SDL_RenderClear(pRenderer);


		//여러가지 sprites
		testSprite.Render(pRenderer, playerState, worldState);
		testSprite2.Render(pRenderer, playerState, worldState);

		SDL_RenderPresent(pRenderer);
	}
	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		testSprite.Cleanup();
		testSprite2.Cleanup();

	}

}
