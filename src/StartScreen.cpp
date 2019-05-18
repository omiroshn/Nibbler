#include "StartScreen.hpp"
#include "InputManager.hpp"

//=================================================================================================
// StartScreen
//-------------------------------------------------------------------------------------------------
StartScreen::StartScreen()
{
	choiceMade	= false;
	choice		= 0;
	snakeGame	= std::make_unique<Texture>("Snake Game", "Roboto-Black.ttf", 32, SDL_Color{ 0, 0, 0, 0 });
	snakeGame->Pos(Vector2(Graphics::WIDTH * 0.35f, 900.0f));
	onePlayer	= std::make_unique<Texture>("1player.png", 0, 0, 239, 71);
	onePlayer->Pos(Vector2(Graphics::WIDTH * 0.35f, 932.0f));
	twoPlayer	= std::make_unique<Texture>("2player.png", 0, 0, 239, 71);
	twoPlayer->Pos(Vector2(Graphics::WIDTH * 0.35f, 1003.0f));
	quit = std::make_unique<Texture>("quit.png", 0, 0, 239, 71);
	quit->Pos(Vector2(Graphics::WIDTH * 0.35f, 1074.0f));

	//backGround = std::make_unique<Texture>();
	arrow		= std::make_unique<Texture>("SnakeArrow.png", 0, 0, 224, 64);
	arrow->setScale(Vector2(0.5f, 0.5f));
	arrow->Pos(Vector2(Vector2(Graphics::WIDTH * 0.20f, 952.0f)));
	mInputManager = InputManager::Instance();
}
//=================================================================================================
// Play
//-------------------------------------------------------------------------------------------------
bool StartScreen::PlayScreen(float _amount)
{
	Vector2 higherPoint(Graphics::WIDTH * 0.35f, 68.0f);

	if(snakeGame->Pos() != higherPoint)
	{
		snakeGame->Translate(Vector2(0.0f, _amount));
		onePlayer->Translate(Vector2(0.0f, _amount));
		twoPlayer->Translate(Vector2(0.0f, _amount));
		quit->Translate(Vector2(0.0f, _amount));
		arrow->Translate(Vector2(0.0f, _amount));
		return true;
	}
	else
	{
		std::cout << "false\n";
		return false;
	}
}
//=================================================================================================
// Render
//-------------------------------------------------------------------------------------------------
void StartScreen::Render()
{
	onePlayer->Render();
	twoPlayer->Render();
	quit->Render();
	snakeGame->Render();
	arrow->Render();
}
//=================================================================================================
// Update
//-------------------------------------------------------------------------------------------------
void StartScreen::Update()
{
	if (mInputManager->KeyPressed(SDL_SCANCODE_W) && choice > 0)
	{
		arrow->Translate(Vector2(0.0f, -72.0f));
		--choice;
	}
	if (mInputManager->KeyPressed(SDL_SCANCODE_S) && choice < 2)
	{
		arrow->Translate(Vector2(0.0f, 72.0f));
		++choice;
	}
	if (mInputManager->KeyPressed(SDL_SCANCODE_KP_ENTER))
	{
		choiceMade = true;
	}
	mInputManager->Update();
}