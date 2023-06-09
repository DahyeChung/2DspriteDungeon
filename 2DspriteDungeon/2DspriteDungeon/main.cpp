#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "GameCore.h"
//튜토리얼 2

using namespace DungeonGame;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* pWindow = SDL_CreateWindow("Dungeon Game",
        100, 100, //Display x,y pixel position 
        WINDOW_WIDTH, WINDOW_HEIGHT, //Pixel width * height 
        SDL_WINDOW_SHOWN); // Show the window

    //Game Icon
    SDL_Surface* pSurface = SDL_LoadBMP("icon.bmp"); 
    SDL_SetWindowIcon(pWindow, pSurface);


    SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    PlayerState playerState = {};
    WorldState worldState = {};


    InitializeGame(pRenderer, playerState, worldState); //DungeonGame::InitializeGame() 라고 불러올 수도 있다.

    int frameStartTicks, frameEndTicks = 0;
    int deltaTicks = 0;

    while (!playerState.HasFinishedGame) //bool 이 false 인 동안 == 게임이 돌아가는동안 
    {
        if (deltaTicks < 1)
        {
            frameStartTicks = SDL_GetTicks();
            SDL_Delay(1);//min == 1
            frameEndTicks = SDL_GetTicks();
            deltaTicks = frameEndTicks - frameStartTicks;
        }

        frameStartTicks = SDL_GetTicks();

        GetInput(playerState, worldState);

        float deltaSeconds = (float)deltaTicks / 1000.0f;

        UpdateGame(deltaSeconds, playerState, worldState);
        RenderGame(pRenderer,playerState, worldState);

        frameEndTicks = SDL_GetTicks();
        deltaTicks = frameEndTicks - frameStartTicks;

    }

    CleanupGame(playerState, worldState);

       


    SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
    


	return 0;
}