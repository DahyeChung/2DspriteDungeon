#include "Hero.h"
//히어로 행동 

using namespace DungeonGame;

void Hero:: Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	bool playerIsAlive = playerState.PlayerHP > 0;

	if (playerIsAlive)
	{
		Vector2d direction(0.0f, 0.0f);
		if (playerState.WantsToGoUp)
			direction.Y = -1.0f;
		else if (playerState.WantsToGoDown)
			direction.Y = 1.0f;
		if (playerState.WantsToGoLeft)
			direction.X = -1.0f;
		else if (playerState.WantsToGoRight)
			direction.X = 1.0f;

		direction.Normalize();


		Vector2d newPosition = playerState.PlayerPosition;
		newPosition += direction * 200.0f * deltaSeconds;

		if (worldState.IsWalkableTile(newPosition))
		{
			playerState.PlayerPosition = newPosition;
		}
	}

	worldState.CameraPosition = playerState.PlayerPosition;

	Position = playerState.PlayerPosition - Vector2d(Size.X * 0.5f, Size.Y * 0.85f);




	if (playerState.InvincibilitySeconds > 0.0f)
	{
		playerState.InvincibilitySeconds -= deltaSeconds;
		Visible = !Visible; //enemy 와 collide -> 투명무적상태 후 돌아옴

	}
	else
		Visible = playerIsAlive; //damage blink 

}
