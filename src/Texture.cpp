#include "Texture.hpp"

Texture::Texture(const std::string& path)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetTexture(path);
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
	mClipped = false;
}

Texture::Texture(const std::string& text, const std::string& path, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, path, size, color);
	mClipped = false;
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture()
{
	mTex = nullptr;
	mGraphics = nullptr;
}

void Texture::Render()
{
	Vector2 pos = Pos();
	/*position == center*/

	mRenderRect.x = static_cast<int32_t>(pos.x);
	mRenderRect.y = static_cast<int32_t>(pos.y);
	mGraphics->DrawTexture(mTex, (mClipped)? &mClipRect : NULL , &mRenderRect);
}

Texture::Texture(std::string const &path, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetTexture(path);
	mClipped		= true;
	mWidth			= w;
	mHeight			= h;
	mRenderRect.w	= mWidth;
	mRenderRect.h	= mHeight;
	mClipRect.x		= x;
	mClipRect.y		= y;
	mClipRect.w		= mWidth;
	mClipRect.h		= mHeight;
}