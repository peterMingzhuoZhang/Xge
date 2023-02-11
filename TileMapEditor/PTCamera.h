#ifndef PTCAMERA_H
#define PTCAMERA_H

#include "XEngine.h"
using X::Math::Vector2;

class PTCamera
{
public:
	PTCamera();
	~PTCamera();

	void SetViewPos(Vector2 postion);
	
	Vector2 ConvertToWorld(Vector2 screenPos);
	Vector2 ConvertToScreen(Vector2 worldPos);

	void Render(X::TextureId &texture, Vector2 worldPos);
	void RenderRect(X::Math::Vector2 worldPos, X::Math::Vector4 color,float length);
private:
	Vector2 mViewPostion;
};


#endif // !PTCAMERA_H
