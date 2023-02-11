#include "EditorCursor.h"

const float editorScrollingSpeed = 100.0f;

EditorCursor::EditorCursor()
	:mTextureCount(0)
	,mTextureSize(0.0f)
	,mPosition({0.0f,0.0f})
	,mVelocity({0.0f,0.0f})
	,mSelectingMapIndex(-1)
	,mSelectingToolBoxIndex(-1)
	,mIsSelecting(false)
	,mToolBoxPosition({0.0f,0.0f})
{
}

EditorCursor::~EditorCursor()
{
	XASSERT(mMapTextures == nullptr, "Please unload the EditorCursor");
}
void EditorCursor::Load(const TileMap& map)
{
	mTextureCount = map.GetTextureCount();
	mTextureSize = map.GetTextureSize();
	mMapTextures = new X::TextureId[mTextureCount];
	for (int i = 0; i < mTextureCount; i++)
	{
		mMapTextures[i] = map.GetTextures()[i];
	}
}

void EditorCursor::Update(TileMap & map, PTCamera& camera,float deltaTime)
{
	int x = X::GetMouseScreenX();
	int y = X::GetMouseScreenY();
	X::Math::Vector2 mouseWorldPos = camera.ConvertToWorld({ (float)x, (float)y });
	if (!mIsSelecting)
	{
		if (X::IsKeyDown(X::Keys::RIGHT))
		{
			mVelocity.x += editorScrollingSpeed;
		}else if (X::IsKeyDown(X::Keys::LEFT))
		{
			mVelocity.x -= editorScrollingSpeed;
		}
		else
		{
			mVelocity.x = 0.0f;
		}
		if (X::IsKeyDown(X::Keys::DOWN))
		{
			mVelocity.y += editorScrollingSpeed;
		}else if (X::IsKeyDown(X::Keys::UP))
		{
			mVelocity.y -= editorScrollingSpeed;
		}
		else
		{
			mVelocity.y = 0.0f;
		}
		mPosition += mVelocity * deltaTime;


		mSelectingMapIndex = map.GetIndex(mouseWorldPos);
		mToolBoxPosition = map.GetIndexPosition(mSelectingMapIndex);
		

		if (X::IsMousePressed(X::Mouse::RBUTTON))
		{
			Select(map);
		}
		
		
		if (mPainting)
		{
			if (X::IsMouseDown(X::Mouse::LBUTTON))
			{
				SetTile(map);
			}
		}
		if (X::IsMousePressed(X::Mouse::LBUTTON))
		{
			mPainting = true;
		}
		
	}
	else
	{
		mSelectingToolBoxIndex = GetToolBoxIndex(mouseWorldPos);
		if (mSelectingToolBoxIndex <= 0)
		{
			mSelectingToolBoxIndex = 0;
		}
		else if (mSelectingToolBoxIndex >= mTextureCount - 1)
		{
			mSelectingToolBoxIndex = mTextureCount - 1;
		}
		
		if (X::IsMousePressed(X::Mouse::LBUTTON))
		{
			Select(map);
		}

		
		
	}
}

void EditorCursor::Render(PTCamera & theCamera)
{
	if (!mIsSelecting)
	{
		theCamera.RenderRect(mToolBoxPosition, X::Math::Vector4::DarkGray(), mTextureSize);

	}
	else
	{
		theCamera.RenderRect(mToolBoxPosition, X::Math::Vector4::DarkGray(), mTextureSize);
		for (int i = 0; i < mTextureCount; ++i)
		{
			Vector2 pos = { mToolBoxPosition.x + i * mTextureSize, mToolBoxPosition.y + mTextureSize };
			theCamera.Render(mMapTextures[i], pos);
			theCamera.RenderRect(pos, X::Math::Vector4::Yellow(), mTextureSize);
		}
		Vector2 pos = { mToolBoxPosition.x + mSelectingToolBoxIndex * mTextureSize, mToolBoxPosition.y + mTextureSize };
		theCamera.RenderRect(pos, X::Math::Vector4::DarkGray(), mTextureSize);
	}
}

void EditorCursor::Unload()
{
	XASSERT(mMapTextures != nullptr, "editor havent load yet!");
	X::SafeDeleteArray(mMapTextures);
}

int EditorCursor::GetToolBoxIndex(X::Math::Vector2 pos) const
{
	int x = (int)pos.x;
	x = x - (int)mToolBoxPosition.x;
	return (int)(x / mTextureSize);
}

void EditorCursor::Select(TileMap & map)
{
	mPainting = false;
	if (!mIsSelecting)
	{
		mToolBoxPosition = map.GetIndexPosition(mSelectingMapIndex);
		mIsSelecting = true;
	}
	else
	{
		mIsSelecting = false;
	}
}

void EditorCursor::SetTile(TileMap & map)
{
	map.GetMap()[mSelectingMapIndex] = mSelectingToolBoxIndex;
	
}
