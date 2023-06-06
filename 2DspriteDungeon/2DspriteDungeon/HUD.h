#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class HUD : public Sprite
	{
	public:
		void InitializeInventorySprites(SDL_Renderer* pRenderer, const std::string& redPotionFilepath, const std::string& bluePotionFilepath);

		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* RedPotionTexture;
		SDL_Texture* BluePotionTexture;



	};
}