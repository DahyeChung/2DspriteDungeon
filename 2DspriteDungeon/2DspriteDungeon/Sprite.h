#pragma once
#include "SDL.h"
#include "GameCore.h"
#include <string>
#include <vector>

namespace DungeonGame
{
	class Sprite
	{
	public : 
		Sprite();
		virtual void Initialize(SDL_Renderer* pRenderer, const std::string& image1Filepath);
		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);
		virtual void Cleanup();
		static void CleanupTextures();

	public:
		Vector2d Position;
		Vector2d Size;
		bool Visible; //check if sprite is visible

	protected:
		SDL_Texture* MyTexture; 

		static SDL_Texture* LoadTexture(SDL_Renderer* pRenderer, const std::string& imageFilepath);


		struct LoadedTexture //모든 이미지파일 관리
		{
			std::string Filename;
			SDL_Texture* Texture;
		};

		static std::vector<LoadedTexture> s_LoadedTextures;

	};


}