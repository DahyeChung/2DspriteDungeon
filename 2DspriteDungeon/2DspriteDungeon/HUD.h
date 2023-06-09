#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class HUD : public Sprite
	{
	public:
		void InitializeHudSprites(SDL_Renderer* pRenderer, const std::string& redPotionFilepath, const std::string& bluePotionFilepath, const std::string& keyFilepath, const std::string& healthFilepath, const std::string& gameOverFilepath, const std::string& victoryFilepath);
		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* RedPotionTexture;
		SDL_Texture* BluePotionTexture;
		SDL_Texture* KeyTexture;

		SDL_Texture* HealthTexture;

		SDL_Texture* GameOverTexture;
		SDL_Texture* VictoryTexture;


	};
}