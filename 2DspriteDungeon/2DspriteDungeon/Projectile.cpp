#include "Projectile.h"
//히어로 행동 

using namespace DungeonGame;

void Projectile::SetProjectileIndex(int newIndex)
{
	ProjectileIndex = newIndex;
}




void Projectile::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	ProjectileData& currProjectile = playerState.Projectiles[ProjectileIndex];

	if (currProjectile.Alive)
	{
		/*
		Vector2d vecToPlayer = currProjectile.Positon - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			currProjectile.Alive = false;

			playerState.ProjectileInventory.push_back(currProjectile.Type);

		}
		/*
		vecToPlayer.Normalize(); //Projectile move away from the player //AI Move To 로 활용가능
		currProjectile.Positon += vecToPlayer * -50.0f * deltaSeconds;
		

		if (vecToPlayer.GetLength() < 100.0f)
		{
			vecToPlayer.Normalize();

			Vector2d newPosition = currProjectile.Positon;
			newPosition += vecToPlayer * -50.0f * deltaSeconds;

			if (worldState.IsWalkableTile(newPosition))
			{
				currProjectile.Positon = newPosition;
			}
		}
		*/

		Vector2d direction(1.0f, 0.0f);
		direction.Normalize();

		Vector2d newPosition = currProjectile.Position;
		newPosition += direction * 500.0f * deltaSeconds;
		currProjectile.Position = newPosition;

		currProjectile.Lifetime += deltaSeconds;
		if (currProjectile.Lifetime > 0.5f)
		{
			currProjectile.Alive = false;
		}
	}

	Position = currProjectile.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currProjectile.Alive;

}
