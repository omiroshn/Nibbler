#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP
#include <string>
#include "GameEntity.hpp"
#include "AssetManager.hpp"

//**************************************************************************************************
//	Texture
//--------------------------------------------------------------------------------------------------
class Texture : public GameEntity
{
public:

	Texture(const std::string& path);
	Texture(const std::string& path, int x, int y, int w, int h);
	Texture(const std::string& text, const std::string& path, int size, SDL_Color color);
	virtual ~Texture();

	virtual void	Render();
	void			setStartX(int32_t amount) { mClipRect.x = amount;	}
	void			setStartY(int32_t amount) { mClipRect.y = amount;	}

protected:

	SDL_Texture*	mTex;
	Graphics*		mGraphics; //singeltone

	int mWidth;
	int mHeight;
	bool mClipped;

	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

};

#endif