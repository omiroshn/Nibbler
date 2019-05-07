#include "AudioManager.hpp"

AudioManager *AudioManager::sInstance = nullptr;

AudioManager *AudioManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

AudioManager::AudioManager()
{
	mAssetMngr = AssetManager::Instance();
	// Mix_Init();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		std::cout << "Error initializing SDL2_mixer" << Mix_GetError() <<std::endl;
	}
}



void AudioManager::PlayMusic(std::string filename, int loops)
{
	Mix_PlayMusic(mAssetMngr->GetMusic(filename), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0){
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic(){

	if (Mix_PausedMusic() != 0){
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel)
{
	Mix_PlayChannel(channel, mAssetMngr->GetSeffect(filename), loops);
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AudioManager::~AudioManager()
{
	mAssetMngr = nullptr;
	Mix_Quit();
}