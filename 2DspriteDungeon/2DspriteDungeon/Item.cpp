#include "Item.h"
//히어로 행동 

using namespace DungeonGame;

void Item::SetItemIndex(int newIndex)
{
	ItemIndex = newIndex;
}




void Item::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	ItemData& currItem = worldState.Items[ItemIndex];

	if (currItem.Alive)
	{
		Vector2d vecToPlayer = currItem.Positon - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			currItem.Alive = false;

			playerState.ItemInventory.push_back(currItem.Type);

		}
		/*
		vecToPlayer.Normalize(); //item move away from the player //AI Move To 로 활용가능
		currItem.Positon += vecToPlayer * -50.0f * deltaSeconds;
		*/

		if (vecToPlayer.GetLength() < 100.0f)
		{
			vecToPlayer.Normalize();

			Vector2d newPosition = currItem.Positon;
			newPosition += vecToPlayer * -50.0f * deltaSeconds;

			if (worldState.IsWalkableTile(newPosition))
			{
				currItem.Positon = newPosition;
			}
		}
		
	}

	Position = currItem.Positon - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currItem.Alive;

}
