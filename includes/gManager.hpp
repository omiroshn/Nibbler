#ifndef _GMANAGER_HPP
#define _GMANAGER_HPP

#include "AnimatedTexture.hpp"
#include "AudioManager.hpp"
#include "Food.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "StartScreen.hpp"
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
	SDL_Event 			mEvent;
	//Singeltontes =========================================
	Graphics*			mGraphics;
	AssetManager*		mAssetMgr;
	InputManager*		mInputManager;
	AudioManager*		mAudioMan;
	Timer*				mTimer;
	//Game Staff --------------------------------------------
	std::unique_ptr<Level>				mLevel; // make a vector of levels
	std::unique_ptr<Player>				mPlayer;
	std::unique_ptr<Food>				mFood;
	std::vector<std::unique_ptr<Wall>>	mWalls;
	//StartScreen
	std::unique_ptr<StartScreen>		mStartScreen;
};

#endif