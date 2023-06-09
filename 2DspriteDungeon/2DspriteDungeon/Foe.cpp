#include "Foe.h"

using namespace DungeonGame;

void Foe::SetFoeIndex(int newIndex)
{
	FoeIndex = newIndex;
}

void Foe::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	const float FOE_MOVEMENT_SPEED = 100.0f; //enemy speed

	FoeData& currFoe = worldState.Foes[FoeIndex];
	AnimatedMultiplier = 0.0f;

	if (currFoe.Alive && !playerState.PlayerHasWon()) //ÃßÀû
	{
		//enemy chase
		Vector2d vecToPlayer = currFoe.Positon - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			//currFoe.Alive = false;
			if (playerState.PlayerHP > 0 && playerState.InvincibilitySeconds <= 0.0f)
			{
				playerState.PlayerHP -= 1;
				playerState.InvincibilitySeconds = 1.5f;
			}
			
		}
		vecToPlayer.Normalize(); 
		vecToPlayer *= -1.0f;
		currFoe.Positon += vecToPlayer * FOE_MOVEMENT_SPEED * deltaSeconds;
		AnimatedMultiplier = 6.0f;

	}

	Position = currFoe.Positon - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currFoe.Alive;

	AnimatedSprite::Update(deltaSeconds, playerState, worldState);

}
