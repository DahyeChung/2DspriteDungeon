#include "Hero.h"
//����� �ൿ 

using namespace DungeonGame;

void Hero:: Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
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

	worldState.CameraPosition = playerState.PlayerPosition;

	Position = playerState.PlayerPosition - Vector2d(Size.X * 0.5f, Size.Y * 0.85f); 

}
