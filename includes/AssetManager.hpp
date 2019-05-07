#ifndef _ASSETMANAGER_HPP
#define _ASSETMANAGER_HPP
#include "Graphics.hpp"
#include <SDL_mixer.h>
#include <map>

//**************************************************************************************************
//	AssetManager
//--------------------------------------------------------------------------------------------------
class AssetManager
{
public:

	static AssetManager* Instance();
	static void Release();
	SDL_Texture *GetTexture(std::string filename);
	SDL_Texture *GetText(std::string text, std::string filename, int size, SDL_Color color);
	Mix_Music *GetMusic(std::string filename);
	Mix_Chunk *GetSeffect(std::string filename);

private:
	AssetManager();
	~AssetManager();

	TTF_Font *GetFont(std::string filename, int size);

	static AssetManager* sInstance;
	std::map<std::string, SDL_Texture* > mTextures;
	std::map<std::string, SDL_Texture *> mTex;
	std::map<std::string, TTF_Font *> mFonts;
	std::map<std::string, Mix_Music *> mMusic;
	std::map<std::string, Mix_Chunk *> mSeffects;
};
#endif