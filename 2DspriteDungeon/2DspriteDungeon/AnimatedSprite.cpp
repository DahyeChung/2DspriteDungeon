#include "AnimatedSprite.h"

using namespace DungeonGame;

void AnimatedSprite::Initialize(SDL_Renderer* pRenderer, const std::string& image1Filepath, const std::string& image2Filepath)
{
	Frame1Texture = LoadTexture(pRenderer, image1Filepath);
	Frame2Texture = LoadTexture(pRenderer, image2Filepath);
	MyTexture = Frame1Texture;
	SecondsAlive = 0.0f;
	AnimatedMultiplier = 1.0f;
}


void AnimatedSprite::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	float animatedMultiplier = 0.0f;
	//Animation Logic
	{
		SecondsAlive += deltaSeconds;
		int frame = (int)(SecondsAlive * AnimatedMultiplier) % 2;
		if (frame == 0)
			MyTexture = Frame1Texture;
		else if (frame == 1)
			MyTexture = Frame2Texture;
	}

}
