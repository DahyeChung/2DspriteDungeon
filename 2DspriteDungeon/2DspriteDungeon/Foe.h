#pragma once
#include "AnimatedSprite.h"

namespace DungeonGame
{
	class Foe : public AnimatedSprite
	{
	public:
		void SetFoeIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);

	private:
		int FoeIndex;

	};

}