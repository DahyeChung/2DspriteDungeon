#pragma once
#include "SDL.h"
#include "GameCore.h"
#include "string"

namespace DungeonGame
{
	class Sprite
	{
	public : 
		Sprite();
		virtual void Initialize(SDL_Renderer* pRenderer, const std::string& imageFilepath);
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState);
		virtual void Cleanup();

	public:
		Vector2d Position;
		Vector2d Size;
		bool Visible; //check if sprite is visible

	protected:
		SDL_Texture* MyTexture; 

	};


}