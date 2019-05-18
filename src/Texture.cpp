#include "Texture.hpp"

Texture::Texture(const std::string& path)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetTexture(path);
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
	mClipped = false;
	mScale = Vector2(1.0f, 1.0f);
}

Texture::Texture(const std::string& text, const std::string& path, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, path, size, color);
	mClipped = false;
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);
	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
	mScale = Vector2(1.0f, 1.0f);
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
	//mRenderRect.x = static_cast<int32_t>(pos.x - mWidth * mScale.x * 0.5f);
	//mRenderRect.y = static_cast<int32_t>(pos.y - mHeight * mScale.y * 0.5f);
	mRenderRect.w = static_cast<int32_t>(mWidth * mScale.x);
	mRenderRect.h = static_cast<int32_t>(mHeight * mScale.y);
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
	mScale = Vector2(1.0f, 1.0f);
}