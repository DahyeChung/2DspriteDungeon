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
		//Move Foe
		Vector2d movementVector = Vector2d(1.0f, 0.0f);
		if (currFoe.Behavior == FoeBehavior_SEEK_PLAYER)
			movementVector = playerState.PlayerPosition - currFoe.Position;
		else if (currFoe.Behavior == FoeBehavior_PATROL)
		{
			if (currFoe.NavigationPoints.size() > 0)
			{
				Vector2d currentNavPoint = currFoe.NavigationPoints[currFoe.NavPointIndex];
				movementVector = currentNavPoint - currFoe.Position;

				if(movementVector.GetLength() < 15.0f)
				{ 
					currFoe.NavPointIndex++;

					if (currFoe.NavPointIndex >= currFoe.NavigationPoints.size())
						currFoe.NavPointIndex = 0;

				}



			}
		}
		movementVector.Normalize();
		currFoe.Position += movementVector * FOE_MOVEMENT_SPEED * deltaSeconds;

		//Hurt Player
		Vector2d vecToPlayer = playerState.PlayerPosition - currFoe.Position;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			//currFoe.Alive = false;
			if (playerState.PlayerHP > 0 && playerState.InvincibilitySeconds <= 0.0f)
			{
				playerState.PlayerHP -= 1;
				playerState.InvincibilitySeconds = 1.5f;
			}

		}

		//Animation
		AnimatedMultiplier = 6.0f;

	}

	Position = currFoe.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currFoe.Alive;

	AnimatedSprite::Update(deltaSeconds, playerState, worldState);

}
