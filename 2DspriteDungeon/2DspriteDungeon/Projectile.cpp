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
		//Vector2d newPosition = currProjectile.Position;
		//newPosition += currProjectile.Direction * 500.0f * deltaSeconds;
		//currProjectile.Position = newPosition;
		
		currProjectile.Position = playerState.PlayerPosition + currProjectile.Direction * 32.0f; 

		for (int i = 0; i < worldState.Foes.size(); ++i)
		{
			FoeData& currFoe = worldState.Foes[i];
			Vector2d vecToFoe = currFoe.Position - currProjectile.Position;
			if (vecToFoe.GetLength() < 30.0f)
			{
				//currProjectile.Alive = false;
				currFoe.Alive = false;
				break;
			}
		}
		currProjectile.Lifetime += deltaSeconds;
		if (currProjectile.Lifetime > 0.125f)
		{
			currProjectile.Alive = false;
		}
	}

	Position = currProjectile.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currProjectile.Alive;

}
