#include "RoomRenderer.h"

using namespace DungeonGame;

void RoomRenderer::InitializeRoomTiles(SDL_Renderer* pRenderer, const std::string& floorFilepath, const std::string& wallFilepath)
{
	FloorTexture = LoadTexture(pRenderer, floorFilepath);
	WallTexture = LoadTexture(pRenderer, wallFilepath);
}

void RoomRenderer::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
{
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

		if (MyTexture != nullptr) //if nothing 
		{
		SDL_Rect destRect = { 
			columnsRendered * (int)Position.X, 
			rowsRendered * (int)Position.Y,
			(int)Size.X, 
			(int)Size.Y };

		SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}

		columnsRendered++;
		if (columnsRendered % worldState.TilesPerRow == 0)
		{
			rowsRendered++;
			columnsRendered = 0;
		}

	}
}