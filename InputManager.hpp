#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <SDL.h>
#include <string>
#include "MathHelper.hpp"

//**************************************************************************************************
//	InputManager
//--------------------------------------------------------------------------------------------------
class InputManager
{

public:

	enum MOUSE_BUTTON
	{
		left = 0,
		right,
		middle,
		back,
		forward,
		wheelUp,
		wheelDown
	};

public:

	static InputManager*	Instance();
	static void				Release();

	/*Keyboard*/
	bool					KeyDown(SDL_Scancode scancode);
	bool					KeyPressed(SDL_Scancode scancode);
	bool					KeyRealeased(SDL_Scancode scancode);

	/*Mouse*/
	bool					MouseButtonDown(MOUSE_BUTTON button);
	bool					MouseButtonPressed(MOUSE_BUTTON button);
	bool					MouseButtonRealesed(MOUSE_BUTTON button);

	Vector2					MousePos() const;
	void					MousePos(float x, float y);
	void					UpdatePrevInput();
	void					Update();

private:
	InputManager();
	~InputManager();

	static InputManager*	sInstance;
	const Uint8*			mKeybordState;
	Uint8*					mPrevKeybordState;
	int						mKeyLength;

	/*Mouse*/
	Uint32					mPrevMouseState;
	Uint32					mMouseState;
	Vector2					mMousePosition;

};

#endif