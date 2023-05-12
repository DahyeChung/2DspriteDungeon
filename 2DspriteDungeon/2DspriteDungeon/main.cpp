#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "GameCore.h"
//튜토리얼 1 9분10

using namespace DungeonGame;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* pWindow = SDL_CreateWindow("Dungeon Game",
        100, 100, //Display x,y pixel position 
        1280, 720, //Pixel width * height 
        SDL_WINDOW_SHOWN); // Show the window

    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    PlayerState playerState = {};
    WorldState worldState = {};


    InitializeGame(playerState, worldState); //DungeonGame::InitializeGame() 라고 불러올 수도 있다.


    while (!playerState.HasFinishedGame) //bool 이 false 인 동안 == 게임이 돌아가는동안 
    {
        GetInput(playerState, worldState);
        UpdateGame(playerState, worldState);
        RenderGame(pRenderer,playerState, worldState);

    }

    CleanupGame();

       


    SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
    


	return 0;
}