//====================================================================================================
// Filename:	SpriteRenderer.cpp
// Created by:	Peter Chan
//====================================================================================================

#include "Precompiled.h"
#include "SpriteRenderer.h"

#include "GraphicsSystem.h"
#include "Texture.h"
#include <DirectXTK-main/Inc/CommonStates.h>
#include <DirectXTK-main/Inc/SpriteBatch.h>

using namespace X;

namespace
{
	SpriteRenderer* sSpriteRenderer = nullptr;
}

void SpriteRenderer::StaticInitialize()
{
	XASSERT(sSpriteRenderer == nullptr, "[SpriteRenderer] System already initialized!");
	sSpriteRenderer = new SpriteRenderer();
	sSpriteRenderer->Initialize();
}

//----------------------------------------------------------------------------------------------------

void SpriteRenderer::StaticTerminate()
{
	if (sSpriteRenderer != nullptr)
	{
		sSpriteRenderer->Terminate();
		SafeDelete(sSpriteRenderer);
	}
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer* SpriteRenderer::Get()
{
	XASSERT(sSpriteRenderer != nullptr, "[SpriteRenderer] No instance registered.");
	return sSpriteRenderer;
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer::SpriteRenderer()
	: mCommonStates(nullptr)
	, mSpriteBatch(nullptr)
{
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer::~SpriteRenderer()
{
	XASSERT(mSpriteBatch == nullptr, "[SpriteRenderer] Renderer not freed.");
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Initialize()
{
	XASSERT(mSpriteBatch == nullptr, "[SpriteRenderer] Already initialized.");
	GraphicsSystem* gs = GraphicsSystem::Get();
	mCommonStates = new DirectX::DX11::CommonStates(gs->GetDevice());
	mSpriteBatch = new DirectX::DX11::SpriteBatch(gs->GetContext());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Terminate()
{
	XASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Already terminated.");
	SafeDelete(mSpriteBatch);
	SafeDelete(mCommonStates);
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::BeginRender()
{
	XASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, mCommonStates->NonPremultiplied());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::EndRender()
{
	XASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mSpriteBatch->End();

	// Restore state objects
	auto blendState = mCommonStates->Opaque();
	auto depthStencilState = mCommonStates->DepthDefault();
	auto rasterizerState = mCommonStates->CullCounterClockwise();

	ID3D11DeviceContext* context = GraphicsSystem::Get()->GetContext();
	context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(depthStencilState, 0);
	context->RSSetState(rasterizerState);
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Draw(const Texture& texture, const Math::Vector2& pos, float rotation)
{
	XASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	DirectX::XMFLOAT2 origin{ texture.GetWidth() * 0.5f, texture.GetHeight() * 0.5f };
	mSpriteBatch->Draw(texture.mShaderResourceView, *(DirectX::XMFLOAT2*)&pos, nullptr, DirectX::Colors::White, rotation, origin);
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Draw(const Texture& texture, const Math::Rect& sourceRect, const Math::Vector2& pos, float rotation)
{
	XASSERT(mSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	RECT rect;
	rect.left = static_cast<LONG>(sourceRect.left);
	rect.top = static_cast<LONG>(sourceRect.top);
	rect.right = static_cast<LONG>(sourceRect.right);
	rect.bottom = static_cast<LONG>(sourceRect.bottom);
	DirectX::XMFLOAT2 origin{ texture.GetWidth() * 0.5f, texture.GetHeight() * 0.5f };
	mSpriteBatch->Draw(texture.mShaderResourceView, *(DirectX::XMFLOAT2*)&pos, &rect, DirectX::Colors::White, rotation, origin);
}