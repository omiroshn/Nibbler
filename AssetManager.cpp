#include "AssetManager.hpp"

AssetManager *AssetManager::sInstance = nullptr;

//**************************************************************************************************
//	AssetManager::Instance
//--------------------------------------------------------------------------------------------------
AssetManager* AssetManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AssetManager();
	}
	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AssetManager::AssetManager(){

}

AssetManager::~AssetManager()
{
	for (auto tex : mTextures)
	{
		if (tex.second != nullptr)
		{
			SDL_DestroyTexture(tex.second);
		}
	}
	mTextures.clear();

	for (auto tex : mTex){
		if (tex.second != nullptr){
			SDL_DestroyTexture(tex.second);
		}
	}
	mTex.clear();

	for (auto font : mFonts){
		if (font.second != nullptr){
			TTF_CloseFont(font.second);
		}
	}
	mFonts.clear();
}

SDL_Texture *AssetManager::GetTexture(std::string filename)
{
	std::string fullpath;
	fullpath.append("resourses/sprites/" + filename);

	if (mTextures[fullpath] == nullptr)
	{
		mTextures[fullpath] = Graphics::Instance()->LoadTexture(fullpath);
	}
	return mTextures[fullpath];
}

TTF_Font *AssetManager::GetFont(std::string filename, int size)
{
	std::string fullpath;
	fullpath.append("resourses/fonts/" + filename);

	std::string key = fullpath + (char)size;
	if (mFonts[key] == nullptr)
	{
		mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
		if (mFonts[key] == nullptr)
		{
			std::cout << "Error opening " << fullpath << "font " << TTF_GetError() <<std::endl; 
		}
	}
	return mFonts[key];
}

SDL_Texture *AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font *font = GetFont(filename, size);
	std::string key = text + filename + (char)size + (char)color.r + (char)color.g + (char)color.b;

	if (mTex[key] == nullptr)
	{
		mTex[key] = Graphics::Instance()->CreateTTF(font, text, color);
	}
	return mTex[key];
}

Mix_Music *AssetManager::GetMusic(std::string filename)
{
	std::string fullpath;
	fullpath.append("resourses/sound/" + filename);

	if (mMusic[fullpath] == nullptr)
	{
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mMusic[fullpath] == nullptr)
		{
			std::cout << "Error opening " << fullpath << "music " << Mix_GetError() <<std::endl; 
		}
	}
	return mMusic[fullpath];
}

Mix_Chunk *AssetManager::GetSeffect(std::string filename)
{
	std::string fullpath;
	fullpath.append("resourses/sound/" + filename);

	if (mSeffects[fullpath] == nullptr)
	{
		mSeffects[fullpath] = Mix_LoadWAV(fullpath.c_str());
		if (mSeffects[fullpath] == nullptr)
		{
			std::cout << "Error opening " << fullpath << "sound effect " << Mix_GetError() <<std::endl;
		}
	}
	return mSeffects[fullpath];
}