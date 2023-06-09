#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Hero : public Sprite
	{
	public: 
		void Initialize(SDL_Renderer* pRenderer, const std::string& image1Filepath, const std::string& image2Filepath);
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private: 
		void Shoot(PlayerState& playerState, const Vector2d& direction);

		SDL_Texture* Frame1Texture;
		SDL_Texture* Frame2Texture;
		float SecondsAlive;


	};

}