#pragma once
#include "SDL.h"
#include <string>

namespace DungeonGame
{
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

	struct PlayerState
	{
		bool HasFinishedGame;
		bool WantsToGoUp;
		bool WantsToGoDown;
		bool WantsToGoLeft;
		bool WantsToGoRight;
	};

	struct WorldState
	{
		int TilesPerRow;
		std::string Tiles;
	};


	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState);
	void GetInput(PlayerState& playerState, WorldState& worldState);
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState);
	void CleanupGame(PlayerState& playerState, WorldState& worldState);
}