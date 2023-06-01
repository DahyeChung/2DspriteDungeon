#include "Hero.h"
//히어로 행동 

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



	Vector2d newPosition = Position;
	newPosition += direction * 200.0f * deltaSeconds;
	if (true)
	{
		Position = newPosition;
	}

}
