#pragma once
#include <XEngine.h>

class TileMap
{
public:
	TileMap();
	TileMap(std::string filename);
	~TileMap();

	void Load(std::string fileName, std::string tileFile);

	void Draw();
	//void Update(float dt);

	void Save(std::string fileName);
private:
	int* mMap;
	int mCol;
	int mRow;
	float mTileSize;
	X::TextureId* mTextures;
	int mTextureCount;
};