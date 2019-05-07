#ifndef _ANIMATEDTEXTURE_HPP
#define _ANIMATEDTEXTURE_HPP
#include "Timer.hpp"
#include "Texture.hpp"

//**************************************************************************************************
//	AnimateTexture
//--------------------------------------------------------------------------------------------------
class AnimateTexture : public Texture
{
public:

/*animate once or loop it*/
	enum WRAP_MODE
	{
		once = 0,
		loop = 1
	};
/*Vertical animation or horizontal*/
	enum ANIM_DIR
	{
		horizontal = 0,
		vetrical = 1
	};

	AnimateTexture(std::string path, int x, int y, int w, int h, int frameCount, float AnimSpeed, ANIM_DIR animDir);
	~AnimateTexture();

	void			WrapMode(WRAP_MODE mode);
	void			Update();
private:

	bool		mAnimationDone;
	int			mStartX;
	int			mStartY;
	int			mFrameCount;
	ANIM_DIR	mAnminDir;
	WRAP_MODE	mWrapMode;
	float		mAnimationTimer;
	float		mAnimationSpeed;
	float		mTimerPerSec;

	Timer		*mTimer;

public:



};

#endif