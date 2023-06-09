#pragma once
#include "SDL.h"
#include <string>
#include <vector>

namespace DungeonGame
{
	//Window Size
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;


	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			X(0.0f),
			Y(0.0f)
		{

		}
		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{

		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && otherPosition.Y;
		}

		bool operator !=(const Vector2d& otherPosition) const
		{
			return !(*this == otherPosition);

		}
		Vector2d& operator+=(const Vector2d & rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}

		const Vector2d operator+(const Vector2d& rhs) const
		{
			return Vector2d(*this) += rhs; //right hand sige
		}

		Vector2d& operator-=(const Vector2d & rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}

		const Vector2d operator-(const Vector2d& rhs) const
		{
			return Vector2d(*this) -= rhs; 
		}

		Vector2d& operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}
		const Vector2d operator*(float scalar) const
		{
			return Vector2d(*this) *= scalar;
		}
		float GetLength()
		{
			return sqrtf(X * X + Y * Y);
		}

		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f)
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}


	};

	enum ItemType
	{
		Item_RedPotion,
		Item_BluePotion,
		Item_KEY
	};


	enum FoeBehavior
	{
		FoeBehavior_SEEK_PLAYER,
		FoeBehavior_PATROL

	};

	struct ProjectileData
	{
		bool Alive;
		float Lifetime;
		Vector2d Direction;
		Vector2d Position;

	};


	struct PlayerState
	{
		bool HasFinishedGame;

		bool WantsToGoUp;
		bool WantsToGoDown;
		bool WantsToGoLeft;
		bool WantsToGoRight;
		bool WantsToShoot;

		float ShotCooldownSeconds;

		Vector2d PlayerPosition;
		Vector2d PreviousDirection;

		std::vector<ItemType> ItemInventory;
		std::vector<ProjectileData> Projectiles;

		int PlayerHP;
		float InvincibilitySeconds;

		bool PlayerHasWon() const;
	};


	struct ItemData
	{
		bool Alive;
		ItemType Type;
		Vector2d Position;
	};

	struct FoeData
	{
		bool Alive;
		FoeBehavior Behavior;
		Vector2d Position;

		int NavPointIndex;
		std::vector<Vector2d> NavigationPoints;
	};

	struct DoorData
	{
		bool Alive;
		bool FinalDoor;
		Vector2d Position;
	};

	struct WorldState
	{
		int TilesPerRow;
		std::string Tiles;
		Vector2d TileSizeInPixels;

		Vector2d CameraPosition;

		std::vector<ItemData> Items;
		std::vector<FoeData> Foes; //enemy
		std::vector<DoorData> Doors; 

		float SecondsSincePlayerDefeat;

		bool IsWalkableTile(const Vector2d& inPosition);
	};


	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, WorldState& worldState);
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);
}