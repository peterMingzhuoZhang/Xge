//====================================================================================================
// Filename:	SpriteRenderer.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_XENGINE_SPRITERENDERER_H
#define INCLUDED_XENGINE_SPRITERENDERER_H

#include "XMath.h"

namespace DirectX {
	inline namespace DX11
	{
		class CommonStates; class SpriteBatch;
	}
}

namespace X {

class Texture;

class SpriteRenderer
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static SpriteRenderer* Get();

public:
	SpriteRenderer();
	~SpriteRenderer();

	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(const SpriteRenderer&) = delete;

	void Initialize();
	void Terminate();

	void BeginRender();
	void EndRender();

	void Draw(const Texture& texture, const Math::Vector2& pos, float rotation = 0.0f);
	void Draw(const Texture& texture, const Math::Rect& sourceRect, const Math::Vector2& pos, float rotation = 0.0f);

private:
	friend class Font;

	DirectX::DX11::CommonStates* mCommonStates;
	DirectX::DX11::SpriteBatch* mSpriteBatch;
};

} // namespace Graphics

#endif // #ifndef INCLUDED_XENGINE_SPRITERENDERER_H