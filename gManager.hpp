#ifndef _GMANAGER_HPP
#define _GMANAGER_HPP

#include "AnimatedTexture.hpp"
#include "AudioManager.hpp"
#include "Food.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include <memory>

//**************************************************************************************************
//	gManager
//--------------------------------------------------------------------------------------------------
class gManager
{
public:
	static gManager*	Instance();
	static void			Release();
	void 				run();

private:
	gManager();
	~gManager();

	void				HandleInput();
	void				Update();
	void				CheckCollision();

	static gManager*	sInstance;
	const int 			FrameRate = 60;
	bool 				_isDone;
	Graphics*			mGraphics;
	SDL_Event 			mEvent;
	AssetManager*		mAssetMgr;
	InputManager*		mInputManager;
	AudioManager*		mAudioMan;

	Timer*				mTimer;
	Level*				mLevel; // make a vector of levels
	//Wall*				mWall	= nullptr;
	Player*				mPlayer;
	Food*				mFood;
	std::vector<Wall*>	mWalls;
};

#endif