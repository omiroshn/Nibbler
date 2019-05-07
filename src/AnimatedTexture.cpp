#include "AnimatedTexture.hpp"

AnimateTexture::AnimateTexture(std::string path, int x, int y, int w, int h, int frameCount, float AnimSpeed, ANIM_DIR animDir)
: Texture(path,x,y,w,h)
{
	mTimer = Timer::Instance();
	mStartX = x;
	mStartY = y;
	mFrameCount = frameCount;
	mAnimationSpeed = AnimSpeed;
	mTimerPerSec = AnimSpeed / mFrameCount;
	mAnimationTimer = 0.0f;
	mAnminDir = animDir;
	mAnimationDone = false;
	mWrapMode = loop;

}

AnimateTexture::~AnimateTexture(){

}

void AnimateTexture::WrapMode(WRAP_MODE mode){
	mWrapMode = mode;
}
void AnimateTexture::Update(){

	if (!mAnimationDone){
		mAnimationTimer += mTimer->getDeltaTime();
		if (mAnimationTimer >= mAnimationSpeed){

			if (mWrapMode == loop){

				mAnimationTimer -= mAnimationSpeed;
			}
			else {

				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimerPerSec;
			}
		}
		if (mAnminDir == horizontal){
			mClipRect.x = mStartX + (int)(mAnimationTimer / mTimerPerSec) * mWidth;
		} else {
			mClipRect.y = mStartY + (int)(mAnimationTimer / mTimerPerSec) * mHeight;
		}
	}
}