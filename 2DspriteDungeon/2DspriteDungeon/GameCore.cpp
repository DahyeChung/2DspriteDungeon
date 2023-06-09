#include "GameCore.h"
#include <stdio.h>
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "Foe.h"
#include "HUD.h"
#include "BG.h"
#include "Projectile.h"
#include "Door.h"

namespace DungeonGame
{
	std::vector<Sprite*> SpriteList;

		//win conditions
	bool PlayerState::PlayerHasWon() const
	{
		int numberOfRedPotions = 0;
		int numberOfBluePotions = 0;

		for (int i = 0; i < ItemInventory.size(); ++i)
		{
			if (ItemInventory[i] == Item_RedPotion)
				numberOfRedPotions++;
			else if (ItemInventory[i] == Item_BluePotion)
				numberOfBluePotions++;
		}

		return numberOfRedPotions == 3 && numberOfBluePotions == 2;
	}
	

	bool WorldState::IsWalkableTile(const Vector2d& inPosition) //Tile Collision
 	{
		for (int i = 0; i < Doors.size(); ++i)
		{
			if (Doors[i].Alive)
			{
				Vector2d vecToDoor = Doors[i].Position - inPosition;
				if (vecToDoor.GetLength() < 30.0f)
					return false;
			}

		}


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
		playerState.PlayerHP = 5;
		playerState.InvincibilitySeconds = 0.0f;
		playerState.ShotCooldownSeconds = 0.0f;
		playerState.PreviousDirection = Vector2d(1.0f, 0.0f);


		playerState.WantsToGoUp = false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;
		playerState.WantsToShoot = false;

		//shoot
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(144.0f,72.0f)});
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(144.0f,144.0f)});
		playerState.Projectiles.push_back({ false, 0.0f, Vector2d(1.0f, 0.0f), Vector2d(144.0f,200.0f)});


		worldState.SecondsSincePlayerDefeat = 0.0f;


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

		worldState.Items.push_back({ true,Item_KEY, Vector2d(2.0f * worldState.TileSizeInPixels.X,5.0f * worldState.TileSizeInPixels.Y) });
		
		worldState.Items.push_back({ true,Item_RedPotion, Vector2d(2.0f * worldState.TileSizeInPixels.X,7.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true,Item_RedPotion, Vector2d(2.0f * worldState.TileSizeInPixels.X,8.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true,Item_BluePotion, Vector2d( 2.0f * worldState.TileSizeInPixels.X,9.0f * worldState.TileSizeInPixels.Y) });

		worldState.Items.push_back({ true,Item_RedPotion, Vector2d(7.0f * worldState.TileSizeInPixels.X,7.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true,Item_RedPotion, Vector2d(7.0f * worldState.TileSizeInPixels.X,8.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true,Item_BluePotion, Vector2d(7.0f * worldState.TileSizeInPixels.X,9.0f * worldState.TileSizeInPixels.Y) });

		worldState.Foes.push_back({ true, FoeBehavior_SEEK_PLAYER,Vector2d(5.0f * worldState.TileSizeInPixels.X,9.0f * worldState.TileSizeInPixels.Y) });

		{
			FoeData myFoe = { true, FoeBehavior_PATROL, Vector2d(6.0f * worldState.TileSizeInPixels.X, 7.0f * worldState.TileSizeInPixels.Y) };
			myFoe.NavPointIndex = 0;
			myFoe.NavigationPoints.push_back(Vector2d(Vector2d(9.0f * worldState.TileSizeInPixels.X, 7.0f * worldState.TileSizeInPixels.Y)));
			myFoe.NavigationPoints.push_back(Vector2d(Vector2d(9.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y)));
			myFoe.NavigationPoints.push_back(Vector2d(Vector2d(2.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y)));
			worldState.Foes.push_back(myFoe);

		}


		worldState.Doors.push_back({ true, Vector2d(5.0f * worldState.TileSizeInPixels.X,6.0f * worldState.TileSizeInPixels.Y) });



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
				case Item_KEY:
					itemFilepath = "Assets/Sprites/Items/key.bmp";
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
				Foe* newFoe = new Foe;
				newFoe->Initialize(pRenderer, "Assets/Sprites/Enemy/Attack1_0.bmp","Assets/Sprites/Enemy/AttackMain2.bmp");
				newFoe->SetFoeIndex(i);
				SpriteList.push_back(newFoe);
			}

			//Door
			for (unsigned int i = 0; i < worldState.Doors.size(); ++i)
			{
				Door* newDoor = new Door;
				newDoor->Initialize(pRenderer, "Assets/Sprites/Tiles/door.bmp");
				newDoor->SetDoorIndex(i);
				SpriteList.push_back(newDoor);
			}

		
		//Sprite 1 : hero
		Hero* newHero = new Hero;
		newHero->Initialize(pRenderer, "Assets/Sprites/Hero/Total/Idle/HeroKnight_0_11zon.bmp", "Assets/Sprites/Hero/Total/Walk/HeroKnight_16_11zon.bmp");
		playerState.PlayerPosition = Vector2d(3.0f * worldState.TileSizeInPixels.X, 2.0f * worldState.TileSizeInPixels.Y);
		
		//newHero->Position = Vector2d(3.0f * worldState.TileSizeInPixels.X, 2.0f*worldState.TileSizeInPixels.Y);
		SpriteList.push_back(newHero);


		//Projectile
		for (unsigned int i = 0; i < playerState.Projectiles.size(); ++i)
		{
			std::string shotFilepath = "Assets/Sprites/Hero/Attack/attack.bmp";

			Projectile* newShot = new Projectile;
			newShot->Initialize(pRenderer, shotFilepath);
			newShot->SetProjectileIndex(i);
			SpriteList.push_back(newShot);
		}
	
		
		//Item Inventory
		HUD* newHUD = new HUD;
		newHUD->InitializeHudSprites(pRenderer, "Assets/Sprites/Items/redPotion.bmp", "Assets/Sprites/Items/bluePotion.bmp","Assets/Sprites/Items/key.bmp", "Assets/Sprites/Hero/Total/Idle/HeroKnight_0_11zon.bmp", "Assets/Sprites/GameOver/ending.bmp", "Assets/Sprites/GameOver/win.bmp" ); 
		SpriteList.push_back(newHUD);

		
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

				case SDLK_SPACE:
					playerState.WantsToShoot = true;
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

				case SDLK_SPACE:
					playerState.WantsToShoot = false;
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
		
		//Game Over
		if (playerState.PlayerHP <= 0 || playerState.PlayerHasWon())
		{
			worldState.SecondsSincePlayerDefeat += deltaSeconds;

			if (worldState.SecondsSincePlayerDefeat > 3.0f)
			{
				playerState.HasFinishedGame = true;
			}
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
