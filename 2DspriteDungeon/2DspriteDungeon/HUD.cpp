#include "HUD.h"

using namespace DungeonGame;

void HUD::InitializeInventorySprites(SDL_Renderer* pRenderer, const std::string& redPotionFilepath, const std::string& bluePotionFilepath)
{
	RedPotionTexture = LoadTexture(pRenderer, redPotionFilepath);
	BluePotionTexture = LoadTexture(pRenderer, bluePotionFilepath);
}

void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
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
				(int)16.0f,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}


	}


	/*
	int columnsRendered = 0;
	int rowsRendered = 0;

	for (unsigned int i = 0; i < worldState.Tiles.size(); ++i)
	{
		char currentTile = worldState.Tiles[i];

		//문자열을 bmp 이미지로 변환시키는 작업
		switch (currentTile)
		{
		case '#':
			MyTexture = WallTexture;
			break;
		case '.':
			MyTexture = FloorTexture;
			break;
		default:
			MyTexture = nullptr;
			break;
		}

		

		columnsRendered++;
		if (columnsRendered % worldState.TilesPerRow == 0)
		{
			rowsRendered++;
			columnsRendered = 0;
		}
		

	}
	*/
}