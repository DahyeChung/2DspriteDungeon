#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class AnimatedSprite : public Sprite
	{
	public:
		void Initialize(SDL_Renderer* pRenderer, const std::string& image1Filepath, const std::string& image2Filepath);
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	protected:
		SDL_Texture* Frame1Texture;
		SDL_Texture* Frame2Texture;
		float SecondsAlive;
		float AnimatedMultiplier;


	};

}