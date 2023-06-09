#include "Door.h"
//히어로 행동 

using namespace DungeonGame;

void Door::SetDoorIndex(int newIndex)
{
	DoorIndex = newIndex;
}

void Door::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	DoorData& currDoor = worldState.Doors[DoorIndex];

	if (currDoor.Alive)
	{
		bool playerHasKey = false;
		if (currDoor.FinalDoor)
		{
			int redPotionCount = 0;
			int bluePotionCount = 0;
			for (int i = 0; i < playerState.ItemInventory.size(); ++i)
			{
				if (playerState.ItemInventory[i] == Item_RedPotion)
				{
					redPotionCount++;
				}
				else if (playerState.ItemInventory[i] == Item_BluePotion)
				{
					bluePotionCount++;
				}
			}

			if (redPotionCount >= 2 && bluePotionCount >= 1)
				playerHasKey = true;
		}

		else 
		{
			for (int i = 0; i < playerState.ItemInventory.size(); ++i)
			{
				if (playerState.ItemInventory[i] == Item_KEY)
				{
					playerHasKey = true;
					break;
				}
			}
		}
		

		if (playerHasKey)
		{
			Vector2d vecToPlayer = currDoor.Position - playerState.PlayerPosition;
			if (vecToPlayer.GetLength() < 45.0f)
			{
				currDoor.Alive = false;
			}
		}
		
	}

	Position = currDoor.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currDoor.Alive;

}
