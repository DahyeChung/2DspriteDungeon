#include "GameCore.h"
#include <stdio.h>
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "Foe.h"
#include "HUD.h"
#include "BG.h"

namespace DungeonGame
{
	std::vector<Sprite*> SpriteList; //everytime create sprites put it in this list
	//Sprite testSprite; //스프라이트 여러개
	//Sprite testSprite2;

	bool WorldState::IsWalkableTile(const Vector2d& inPosition) //Tile Collision
 	{

		int column = (int)(inPosition.X / TileSizeInPixels.X);
		int row = (int)(inPosition.Y / TileSizeInPixels.Y);

		char currentTile = ' '; //any tiles here will be allowed to move
		int index = row * TilesPerRow + column;
		if (index >= 0 && index < (int)Tiles.size())
			currentTile = Tiles[index];

		

		return currentTile == '.';
	}

	SDL_Texture* pTexture = nullptr;
	Vector2d testDirection = Vector2d(0.0f, 1.0f); 



	float testX = 100;

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.HasFinishedGame = false;

		playerState.WantsToGoUp = false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;


		worldState.TilesPerRow = 8; //num of tiles 
		worldState.TileSizeInPixels = Vector2d(72.0f, 72.0f);
		worldState.Tiles =
			"  ####  "
			" #....# "
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#..##..#"
			" ##  ## ";
		
		worldState.Items.push_back({ true,Item_RedPotion, Vector2d(2.0f * worldState.TileSizeInPixels.X,7.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true,Item_RedPotion, Vector2d(2.0f * worldState.TileSizeInPixels.X,8.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true,Item_BluePotion, Vector2d(2.0f * worldState.TileSizeInPixels.X,9.0f * worldState.TileSizeInPixels.Y) });

		worldState.Foes.push_back({ true, Vector2d(5.0f * worldState.TileSizeInPixels.X,9.0f * worldState.TileSizeInPixels.Y) });
		



		BG* bg = new BG;
		bg->Initialize(pRenderer, "Assets/Sprites/Backgrounds/background.bmp");
		bg->Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		SpriteList.push_back(bg);

			RoomRenderer* roomRenderer = new RoomRenderer;
			roomRenderer->InitializeRoomTiles(pRenderer,"Assets/Sprites/tiles/tile.bmp","Assets/Sprites/tiles/wall.bmp"); //floor and wall
			SpriteList.push_back(roomRenderer);

			//Items
			for (unsigned int i = 0; i < worldState.Items.size(); ++i)
			{
				std::string itemFilepath = "Assets/Sprites/Items/redPotion.bmp";

				switch (worldState.Items[i].Type)
				{
				case Item_RedPotion:
					itemFilepath = "Assets/Sprites/Items/redPotion.bmp";
					break;
				case Item_BluePotion:
					itemFilepath = "Assets/Sprites/Items/bluePotion.bmp";
					break;
				}

				Item* newItem = new Item;
				newItem->Initialize(pRenderer, itemFilepath);
				newItem->SetItemIndex(i);
				SpriteList.push_back(newItem);
			}

			//Enemies
			for (unsigned int i = 0; i < worldState.Foes.size(); ++i)
			{
				std::string foeFilepath = "Assets/Sprites/Enemy/Attack1_0.bmp";

				Foe* newFoe = new Foe;
				newFoe->Initialize(pRenderer, foeFilepath);
				newFoe->SetFoeIndex(i);
				SpriteList.push_back(newFoe);
			}

		
		//Sprite 1 : hero
		Hero* newHero = new Hero;
		newHero->Initialize(pRenderer, "Assets/Sprites/Hero/Total/Idle/HeroKnight_0_11zon.bmp");
		playerState.PlayerPosition = Vector2d(3.0f * worldState.TileSizeInPixels.X, 2.0f * worldState.TileSizeInPixels.Y);
		
		//newHero->Position = Vector2d(3.0f * worldState.TileSizeInPixels.X, 2.0f*worldState.TileSizeInPixels.Y);
		SpriteList.push_back(newHero);
		
		
		//Sprite 2
		Sprite* newSprite2 = new Sprite;
		newSprite2->Initialize(pRenderer, "test.bmp");
		newSprite2->Position = Vector2d(100.0f, 220.0f);
		SpriteList.push_back(newSprite2);

		HUD* newHUD = new HUD;
		newHUD->InitializeInventorySprites(pRenderer, "Assets/Sprites/Items/redPotion.bmp", "Assets/Sprites/Items/bluePotion.bmp");
		SpriteList.push_back(newHUD);

		/*
		for (int i = 0; i < 200; ++i) //만약에 아주여러개 많이 만들려면? 테스트
		{
			//Sprite 200
			Sprite* newSprite3 = new Sprite;
			newSprite3->Initialize(pRenderer, "Assets/Sprites/Hero/Total/Idle/HeroKnight_1_11zon.bmp");
			newSprite3->Position = Vector2d(100.0f + 16.0f * i, 320.0f + 4.0f * i );
			SpriteList.push_back(newSprite3);
		}
		
		*/




	
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

				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUp = true;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = true;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = true;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = true;
					break;


				}

			}

			else if (e.type == SDL_KEYUP)
			{	
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{

				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUp = false;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = false;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = false;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = false;
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
			SpriteList[i]->Render(pRenderer, playerState, worldState, Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - worldState.CameraPosition);
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
