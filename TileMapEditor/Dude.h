#ifndef DUDE_H
#define DUDE_H
#include "XEngine.h"
#include "PTCamera.h"
#include <string>
#include "TileMap.h"

static const int textureCount = 8;
static const std::string textures[textureCount]= {"scv_01.png","scv_03.png","scv_05.png","scv_07.png","scv_09.png","scv_11.png","scv_13.png","scv_15.png" };

class Dude
{
public:
	Dude();
	~Dude();

	void Load();
	void Update(const TileMap& map, float deltaTime);
	void Render(PTCamera &theCamera);
	void Unload();

	void setPostion(X::Math::Vector2 position) { mPosition = position; };
	void setVelocity(X::Math::Vector2 velocity) { mVelocity = velocity; };
	X::Math::Vector2 getPostion() const { return mPosition; };

	X::Math::Rect GetBoundingBox() const;
private:
	X::TextureId mAllTextures[textureCount];
	int mCurrentTexture;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;

	
};



#endif // !DUDE_H
