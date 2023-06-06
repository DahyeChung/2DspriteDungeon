#include "Foe.h"

using namespace DungeonGame;

void Foe::SetFoeIndex(int newIndex)
{
	FoeIndex = newIndex;
}




void Foe::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	FoeData& currFoe = worldState.Foes[FoeIndex];

	if (currFoe.Alive)
	{
		//enemy chase
		Vector2d vecToPlayer = currFoe.Positon - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			currFoe.Alive = false;

		}
		/*
		vecToPlayer.Normalize(); //item move away from the player //AI Move To 로 활용가능
		currItem.Positon += vecToPlayer * -50.0f * deltaSeconds;
		*/

		if (vecToPlayer.GetLength() < 100.0f)
		{
			vecToPlayer.Normalize();

			Vector2d newPosition = currFoe.Positon;
			newPosition += vecToPlayer * -50.0f * deltaSeconds;

			if (worldState.IsWalkableTile(newPosition))
			{
				currFoe.Positon = newPosition;
			}
		}

	}

	Position = currFoe.Positon - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currFoe.Alive;

}
