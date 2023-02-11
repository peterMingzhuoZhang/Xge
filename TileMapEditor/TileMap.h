#ifndef TILEMAP_H
#define TILEMAP_H
#include "XEngine.h"
#include "PTCamera.h"
class TileMap
{
public:
	TileMap();

	void Load(const char* file1, const char* file2);
	void Unload();
	void Render(PTCamera &theCamera);

	int GetIndex(int x, int y) const;
	int GetIndex(X::Math::Vector2 pos) const;
	X::Math::Vector2 GetIndexPosition(int index) const;
	bool CheckCollision(const X::Math::LineSegment& edge) const;

	int GetTextureCount()const { return mTextCount; }
	float GetTextureSize()const { return mTextureSize; }
	int* GetMap()const { return mMap; }
	X::TextureId* GetTextures() const { return mTextureIds; }

	void SaveMap(const char* theFile);

private:
	int mRows;
	int mColumns;
	int mTextCount;
	float mTextureSize;

	int* mMap;
	X::TextureId* mTextureIds;
};



#endif // !TILEMAP_H

