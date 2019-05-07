#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
	
//**************************************************************************************************
//	Graphics
//--------------------------------------------------------------------------------------------------
class Graphics
{

public:
	//make enum for constants------
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
	//=============================

	static Graphics*	Instance();
	static bool			Initialized();
	static void			Release();
	
	SDL_Texture*		LoadTexture(std::string const &path);
	SDL_Texture*		CreateTTF(TTF_Font *font, std::string text, SDL_Color color);
	void 				ClearBuffer();
	void 				DrawTexture(SDL_Texture *tex, SDL_Rect *clip = NULL ,SDL_Rect *rend = NULL, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void 				Render();

private:
	Graphics();
	~Graphics();

	bool				Init();

	static Graphics*	sInstance;
	static bool			sInitialized;
	SDL_Window*			_window;
	SDL_Surface*		_surf;
	SDL_Renderer*		mRenderer;

};

#endif