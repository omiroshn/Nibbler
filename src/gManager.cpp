#include "gManager.hpp"

gManager* gManager::sInstance = nullptr;

gManager* gManager::Instance()
{
	if(sInstance == NULL)
	{
		sInstance = new gManager();
	}
	return sInstance;
}

void gManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

gManager::gManager()
{
	// maybe move from ctor to init function
	_isDone = false;
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
	{
		_isDone = true;
	}

	mAssetMgr		= AssetManager::Instance();
	mInputManager	= InputManager::Instance();
	mAudioMan		= AudioManager::Instance();
	mTimer			= Timer::Instance();

	mPlayer			= std::make_unique<Player>("snake.png");
	mFood			= std::make_unique<Food>("snake.png", Vector2(64.0f, 64.0f), 0, 96, 32, 32);
	mLevel			= std::make_unique<Level>();

	// $todo -> set below part into the function and call after level is complete
	// $todo -> make a vector of levels, in32_t - current level
	mLevel->LoadLevel("map1.txt");
	mLevel->ParseLevel();
	mFood->SetRespawnDementions(mLevel->LevelWidth(), mLevel->LevelHeight());
	//mPlayer->Pos(mLevel->PlayerPosition());
	for(size_t i = 0; i < mLevel->WallsPosition().size(); ++i)
	{
		mWalls.emplace_back(std::make_unique<Wall>("st.bmp", mLevel->WallsPosition()[i], 0, 0, 32, 32));
	}

	mStartScreen = std::make_unique<StartScreen>();
}

gManager::~gManager()
{
	AssetManager::Release();
	mAssetMgr = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	AudioManager::Release();
	mAudioMan = nullptr;

	Timer::Release();
	mTimer = nullptr;

	mWalls.clear();
}
//=================================================================================================
// HandleInput
//-------------------------------------------------------------------------------------------------
void gManager::HandleInput()
{
	// in Player class now
}
//=================================================================================================
//	Update
//-------------------------------------------------------------------------------------------------
void gManager::Update()
{
	mPlayer->Update();
	mFood->Update();
}
//=================================================================================================
// CheckCollision
//-------------------------------------------------------------------------------------------------
void gManager::CheckCollision()
{
	if (mPlayer->CheckCircleCollision(*mPlayer, *mFood))
	{
		mPlayer->Collide(*mFood);
		std::cout << "Score: " << mPlayer->Score() << "\n";
		mFood->ReSpawn(); //need change food pos to free square
	}
}
//=================================================================================================
// run
//-------------------------------------------------------------------------------------------------
void gManager::run()
{

	while (mStartScreen->Play())
	{
		mStartScreen->Render();
		mGraphics->Render();
		mGraphics->ClearBuffer();
	}
	while (!_isDone)
	{
		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT || (mEvent.type == SDL_KEYDOWN &&
				mEvent.key.keysym.sym == SDLK_ESCAPE))
			{
				_isDone = true;
			}
		}
		mStartScreen->Update();
		mStartScreen->Render();
		mGraphics->Render();
		mGraphics->ClearBuffer();
	}

	_isDone = false;
	while (!_isDone)
	{
		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT || (mEvent.type == SDL_KEYDOWN &&
				mEvent.key.keysym.sym == SDLK_ESCAPE))
			{
				_isDone = true;
			}
		}

		mTimer->Update();
		mPlayer->HandleInput(mTimer->getDeltaTime());
		if (mTimer->getDeltaTime() >= (10.0f / FrameRate))
		{
			HandleInput();
			CheckCollision();
			Update();
			mGraphics->ClearBuffer();
			
			for(auto &wall : mWalls)
			{
				wall->Render();
			}
			mFood->Render();
			mPlayer->Render();
			mGraphics->Render();
			mTimer->Reset();
		}
	}
}