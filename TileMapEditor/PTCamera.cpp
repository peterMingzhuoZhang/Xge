#include "PTCamera.h"


PTCamera::PTCamera()
	:mViewPostion({0.0f,0.0f})
{
}

PTCamera::~PTCamera()
{
}

void PTCamera::SetViewPos(Vector2 postion)
{
	mViewPostion = postion;
}

Vector2 PTCamera::ConvertToWorld(Vector2 screenPos)
{
	Vector2 worldPos = screenPos - Vector2({(float)X::GetScreenWidth()/2, (float)X::GetScreenHeight()/2});
	worldPos += mViewPostion;
	return worldPos;
}

Vector2 PTCamera::ConvertToScreen(Vector2 worldPos)
{
	Vector2 screenPos = worldPos - mViewPostion;
	screenPos += Vector2({ (float)X::GetScreenWidth()/2, (float)X::GetScreenHeight()/2 });
	return screenPos;
}

void PTCamera::Render(X::TextureId &texture, Vector2 worldPos)
{
	Vector2 screenPos = ConvertToScreen(worldPos);
	if ((screenPos.x >-32.0f)&&((screenPos.x < (float)X::GetScreenWidth()+ 32.0f) && (screenPos.y >-32.0f)&&(screenPos.y < (float)X::GetScreenHeight() + 32.0f)))
	{
		X::DrawSprite(texture, screenPos);
	}
	
}

void PTCamera::RenderRect(X::Math::Vector2 worldPos, X::Math::Vector4 color,float length)
{
	Vector2 pos = ConvertToScreen(worldPos);
	float left = pos.x;
	float right = pos.x + length;
	float top = pos.y;
	float bottom = pos.y + length;
	X::Math::Rect theRect = X::Math::Rect(left, top, right, bottom);
	X::DrawScreenRect(theRect, color);

}
