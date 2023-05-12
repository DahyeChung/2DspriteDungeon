#pragma once
#include "SDL.h"

namespace DungeonGame
{
	struct PlayerState
	{
		bool HasFinishedGame;
	};

	struct WorldState
	{

	};


	void InitializeGame(PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, WorldState& worldState);
	void UpdateGame(PlayerState& playerState, WorldState& worldState);
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);
}