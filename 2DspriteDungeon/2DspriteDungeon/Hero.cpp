#include "Hero.h"
//히어로 행동 

using namespace DungeonGame;

void Hero::Initialize(SDL_Renderer* pRenderer, const std::string& image1Filepath, const std::string& image2Filepath)
{
	Frame1Texture = LoadTexture(pRenderer, image1Filepath);
	Frame2Texture = LoadTexture(pRenderer, image2Filepath);
	MyTexture = Frame1Texture;
	SecondsAlive = 0.0f;
}


void Hero:: Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	bool playerIsAlive = playerState.PlayerHP > 0;
	float animationMultiplier = 0.0f;

	playerState.ShotCooldownSeconds -= deltaSeconds;
	if (playerState.ShotCooldownSeconds < 0.0f)
	{
		playerState.ShotCooldownSeconds = 0.0f;
	}

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

		if (direction != Vector2d(0.0f, 0.0f))
		{
			animationMultiplier = 4.0f;
			playerState.PreviousDirection = direction;
		}


		if (playerState.WantsToShoot)
		{
			Shoot(playerState, playerState.PreviousDirection);
		}


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

	//Animation Logic
	{
		SecondsAlive += deltaSeconds;
		int frame = (int)(SecondsAlive * animationMultiplier) % 2;
		if (frame == 0)
			MyTexture = Frame1Texture;
		else if (frame == 1)
			MyTexture = Frame2Texture;
	}

}

void Hero::Shoot(PlayerState& playerState, const Vector2d& direction)
{
	if (playerState.ShotCooldownSeconds <= 0.0f)
	{

		for (int i = 0; i < playerState.Projectiles.size(); ++i)
		{
			if (!playerState.Projectiles[i].Alive)
			{
				playerState.Projectiles[i].Alive = true;
				playerState.Projectiles[i].Lifetime = 0.0f;
				playerState.Projectiles[i].Direction = direction;
				playerState.Projectiles[i].Position = playerState.PlayerPosition;

				playerState.ShotCooldownSeconds = 0.25f;
				break;
			}
		}
	}

}
