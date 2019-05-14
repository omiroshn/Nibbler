#include "Graphics.hpp"

Graphics* Graphics::sInstance = nullptr;
bool Graphics::sInitialized = false;

//**************************************************************************************************
//	Graphics::Instance
//--------------------------------------------------------------------------------------------------
Graphics* Graphics::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new Graphics();
	}
	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = nullptr;
	sInitialized = false;
}

bool Graphics::Initialized(){
	return sInitialized;
}

Graphics::Graphics(){
	_surf = nullptr;
	_window = nullptr;
	sInitialized = Init();
}

Graphics::~Graphics(){
	SDL_DestroyWindow(_window);
	_window = NULL;
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
//==================================================================================================
//	Graphics::Init
//--------------------------------------------------------------------------------------------------
bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (_window == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	mRenderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(mRenderer, 230, 0xff, 0xff, 0xff);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)){
		std::cout << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	_surf = SDL_GetWindowSurface(_window);
	return true;
}
//==================================================================================================
//	Graphics::LoadTexture
//--------------------------------------------------------------------------------------------------
SDL_Texture *Graphics::LoadTexture(std::string const &path)
{
	SDL_Texture *tex	= nullptr;
	SDL_Surface *surf	= nullptr;

	surf = IMG_Load(path.c_str());
	if (surf == nullptr)
	{
		std::cout << IMG_GetError() << std::endl;
		return tex;
	}
	tex = SDL_CreateTextureFromSurface(mRenderer, surf);
	if (tex == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return tex;
	}
	SDL_FreeSurface(surf);
	return tex;
}
//==================================================================================================
//	Graphics::CreateTTF
//--------------------------------------------------------------------------------------------------
SDL_Texture *Graphics::CreateTTF(TTF_Font *font, std::string text, SDL_Color color)
{
	SDL_Surface *surf = nullptr;
	SDL_Texture *texture = nullptr;

	surf = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surf == nullptr)
	{
		std::cout << TTF_GetError() << std::endl;
		return nullptr;
	}
	texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	if (texture == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return texture;
	}
	SDL_FreeSurface(surf);
	return texture;
}

void Graphics::ClearBuffer(){

	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture *tex, SDL_Rect *clip ,SDL_Rect *rend, float angle, SDL_RendererFlip flip){

	SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
}

void Graphics::Render(){
	
	SDL_RenderPresent(mRenderer);
}