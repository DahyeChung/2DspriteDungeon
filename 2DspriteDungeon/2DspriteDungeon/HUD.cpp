#include "HUD.h"

using namespace DungeonGame;

void HUD::InitializeHudSprites(SDL_Renderer* pRenderer, const std::string& redPotionFilepath, const std::string& bluePotionFilepath, const std::string& healthFilepath)
{
	RedPotionTexture = LoadTexture(pRenderer, redPotionFilepath);
	BluePotionTexture = LoadTexture(pRenderer, bluePotionFilepath);
	HealthTexture = LoadTexture(pRenderer,healthFilepath);
}

void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
	

	//Health Display
	for (unsigned int i = 0; i < playerState.PlayerHP; ++i)
	{
		MyTexture = HealthTexture;


		if (MyTexture != nullptr) //if nothing 
		{
			SDL_Rect destRect = {
				(int)(16.0f + 48.0f * i),
				(int)16.0f,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}

	}

	//Inventory Display
	for (unsigned int i = 0; i < playerState.ItemInventory.size(); ++i)
	{
		ItemType currItem = playerState.ItemInventory[i];

		switch (currItem)
		{
		case Item_RedPotion:
			MyTexture = RedPotionTexture;
			break;
		case Item_BluePotion:
			MyTexture = BluePotionTexture;
			break;
		default:
			MyTexture = nullptr;
			break;
		}

		if (MyTexture != nullptr) //if nothing 
		{
			SDL_Rect destRect = {
				(int)(16.0f + 48.0f * i),
				(int)32.0f,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
	}
}