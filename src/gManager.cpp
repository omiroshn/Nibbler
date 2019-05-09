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

	mPlayer			= new Player("snake.png");
	mFood			= new Food("snake.png", Vector2(64.0f, 64.0f), 0, 96, 32, 32);
	mLevel			= new Level();

	// $todo -> set below part into the function and call after level is complete
	// $todo -> make a vector of levels, in32_t - current level
	mLevel->LoadLevel("map1.txt");
	mLevel->ParseLevel();
	mFood->SetRespawnDementions(mLevel->LevelWidth(), mLevel->LevelHeight());
	//mPlayer->Pos(mLevel->PlayerPosition());
	for(size_t i = 0; i < mLevel->WallsPosition().size(); ++i)
	{
		mWalls.emplace_back(new Wall("st.bmp", mLevel->WallsPosition()[i], 0, 0, 32, 32));
	}
	// mFont = new Texture("Hello world", "Roboto-Black.ttf", 32, {0, 0, 0, 0});
	// mFont->Pos(Vector2(200, 200));
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

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
	
	delete mFood;
	mFood = nullptr;

	for(auto wall : mWalls)
	{
		if(wall)
		{
			delete wall;
			wall = nullptr;
		}
	}
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
	while (!_isDone)
	{
		mTimer->Update();
		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT || (mEvent.type == SDL_KEYDOWN &&
				mEvent.key.keysym.sym == SDLK_ESCAPE))
			{
				_isDone = true;
			}
		}

		mPlayer->HandleInput(mTimer->getDeltaTime());
		if (mTimer->getDeltaTime() >= (10.0f / FrameRate))
		{
			CheckCollision();
			Update();
			mGraphics->ClearBuffer();

			HandleInput();
			
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