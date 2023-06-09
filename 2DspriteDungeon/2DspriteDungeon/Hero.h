#pragma once
#include "AnimatedSprite.h"

namespace DungeonGame
{
	class Hero : public AnimatedSprite
	{
	public: 
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private: 
		void Shoot(PlayerState& playerState, const Vector2d& direction);

	};

}