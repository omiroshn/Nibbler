#include "StartScreen.hpp"
#include "InputManager.hpp"

//=================================================================================================
// StartScreen
//-------------------------------------------------------------------------------------------------
StartScreen::StartScreen()
{
	choice		= 0;
	snakeGame	= std::make_unique<Texture>("Snake Game", "Roboto-Black.ttf", 32, SDL_Color{ 0, 0, 0, 0 });
	snakeGame->Pos(Vector2(Graphics::WIDTH * 0.35f, 900.0f));
	onePlayer	= std::make_unique<Texture>("One Player", "Roboto-Black.ttf", 32, SDL_Color{100, 100, 100, 0});
	onePlayer->Pos(Vector2(Graphics::WIDTH * 0.4f, 932.0f));
	twoPlayer	= std::make_unique<Texture>("Two Player", "Roboto-Black.ttf", 32, SDL_Color{ 0, 0, 0, 0 });
	twoPlayer->Pos(Vector2(Graphics::WIDTH * 0.4f, 964.0f));
	quit		= std::make_unique<Texture>("Quit", "Roboto-Black.ttf", 32, SDL_Color{ 0, 0, 0, 0 });
	quit->Pos(Vector2(Graphics::WIDTH * 0.4f, 996.0f));

	//backGround = std::make_unique<Texture>();
	arrow = std::make_unique<Texture>("->", "Roboto-Black.ttf", 32, SDL_Color{ 0, 0, 0, 0 });;
	arrow->Pos(Vector2(Vector2(Graphics::WIDTH * 0.36f, 932.0f)));
	mInputManager = InputManager::Instance();
}
//=================================================================================================
// Play
//-------------------------------------------------------------------------------------------------
bool StartScreen::Play()
{
	Vector2 higherPoint(Graphics::WIDTH * 0.35f, 68.0f);
	Vector2 add(0.0f, -0.05f);

	if(snakeGame->Pos() != higherPoint)
	{
		snakeGame->Translate(Vector2(add));
		onePlayer->Translate(Vector2(add));
		twoPlayer->Translate(Vector2(add));
		quit->Translate(Vector2(add));
		arrow->Translate(Vector2(add));
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
	// add input Handling
	//SDL_SCANCODE_RIGHT = 79,
	//SDL_SCANCODE_LEFT = 80,
	//SDL_SCANCODE_DOWN = 81,
	//SDL_SCANCODE_UP = 82,
	mInputManager->Update();
	if (mInputManager->KeyPressed(SDL_SCANCODE_W))
	{
		arrow->Translate(Vector2(0.0f, 2.0f));
		std::cout << "W\n";
	}
	if (mInputManager->KeyPressed(SDL_SCANCODE_S))
	{
		arrow->Translate(Vector2(0.0f, -2.0f));
		std::cout << "S\n";
	}
}