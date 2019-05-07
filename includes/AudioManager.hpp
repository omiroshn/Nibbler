#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include "AssetManager.hpp"

//**************************************************************************************************
//	AudioManager
//--------------------------------------------------------------------------------------------------
class AudioManager
{

public:
	static	void Release();
	static	AudioManager *Instance();
	void	PlayMusic(std::string filename, int loops = -1);
	void	PauseMusic();
	void	ResumeMusic();

	void		PlaySFX(std::string filename, int loops = 0, int channel = 0);
	// void PauseSFX();
	// void ResumeSFX();

private:
	AudioManager();
	~AudioManager();

	static AudioManager*	sInstance;
	AssetManager*			mAssetMngr;
};

#endif