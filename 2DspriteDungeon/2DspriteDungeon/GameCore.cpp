#include "GameCore.h"

namespace DungeonGame
{
	void InitializeGame(PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;
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
	void UpdateGame(PlayerState& playerState, WorldState& worldState)
	{

	}
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{	
		SDL_RenderClear(pRenderer);
		//Render Commands go here ! 
		SDL_RenderPresent(pRenderer);
	}
	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{

	}

}
