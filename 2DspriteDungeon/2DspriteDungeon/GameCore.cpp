#include "GameCore.h"
#include <stdio.h>
#include "Sprite.h"

namespace DungeonGame
{
	std::vector<Sprite*> SpriteList; //everytime create sprites put it in this list
	//Sprite testSprite; //스프라이트 여러개
	//Sprite testSprite2;


	SDL_Texture* pTexture = nullptr;
	Vector2d testDirection = Vector2d(0.0f, 1.0f); 



	float testX = 100;

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;


		//Sprite 1
		Sprite* newSprite = new Sprite;
		newSprite->Initialize(pRenderer, "Assets\\Sprites\\Hero\\Total\\Walk\\bmp\\HeroKnight_8.bmp");
		newSprite->Position = Vector2d(100.0f, 120.0f);
		SpriteList.push_back(newSprite);

		//Sprite 2
		Sprite* newSprite2 = new Sprite;
		newSprite2->Initialize(pRenderer, "나중에 경로 넣어.bmp");
		newSprite2->Position = Vector2d(100.0f, 220.0f);
		SpriteList.push_back(newSprite2);

		for (int i = 0; i < 200; ++i) //만약에 아주여러개 많이 만들려면? 테스트
		{
			//Sprite 200
			Sprite* newSprite3 = new Sprite;
			newSprite3->Initialize(pRenderer, "나중에 경로 넣어.bmp");
			newSprite3->Position = Vector2d(100.0f + 16.0f * i, 320.0f + 4.0f * i );
			SpriteList.push_back(newSprite3);
		}




	
	}
	void GetInput(PlayerState& playerState, WorldState& worldState)
	{
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				playerState.HasFinishedGame = true;
			else if (e.type == SDL_KEYDOWN)
			{	
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.HasFinishedGame = true;
					break;
				}

			}
		}
	}
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
	{
		//testDirection.Normalize();
		//testSprite.Position += testDirection * 50.0f * deltaSeconds;

		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Update(deltaSeconds, playerState, worldState);
		}
		

	}


	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{	
		SDL_RenderClear(pRenderer);

		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Render(pRenderer, playerState, worldState);
		}

		SDL_RenderPresent(pRenderer);
	}
	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Cleanup();
			delete SpriteList[i];
		}
		SpriteList.clear();

		Sprite::CleanupTextures();

	}

}
