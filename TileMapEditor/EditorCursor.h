#ifndef EDITORCURSOR_H
#define EDITORCURSOR_H


#include "TileMap.h"


class EditorCursor
{
public:
	EditorCursor();
	~EditorCursor();

	void Load(const TileMap& map);
	void Update(TileMap& map, PTCamera& camrea,float deltaTime);
	void Render(PTCamera &theCamera);
	void Unload();

	void setPostion(X::Math::Vector2 position) { mPosition = position; };
	void setVelocity(X::Math::Vector2 velocity) { mVelocity = velocity; };
	X::Math::Vector2 getPostion() const { return mPosition; };

	int GetToolBoxIndex(X::Math::Vector2 pos) const;

private:
	X::TextureId* mMapTextures;
	int mTextureCount;
	float mTextureSize;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mVelocity;

	int mSelectingMapIndex;
	int mSelectingToolBoxIndex;
	bool mIsSelecting;
	bool mPainting;

	X::Math::Vector2 mToolBoxPosition;

	void Select(TileMap& map);
	void SetTile(TileMap& map);
};

#endif // !EDITORCURSOR_H
