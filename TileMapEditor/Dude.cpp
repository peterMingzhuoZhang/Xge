#include "Dude.h"


Dude::Dude()
	: mCurrentTexture(0)
	, mPosition({0.0f,0.0f})
	, mVelocity({0.0f,0.0f})
	
{
	
}



Dude::~Dude()
{
}

void Dude::Load()
{
	for (int i = 0; i < textureCount; ++i)
	{
		mAllTextures[i] = X::LoadTexture(textures[i].c_str());
	}

}

void Dude::Update(const TileMap& map,float deltaTime)
{
	const float speed = 250.0f;

	//get Vetical vel
	if (X::IsKeyDown(X::Keys::W))
	{
		mCurrentTexture = 0;
		mVelocity.y = -speed;
	}else if (X::IsKeyDown(X::Keys::S))
	{
		mCurrentTexture = 4;
		mVelocity.y = speed;

	}
	else {
		mVelocity.y = 0.0f;
	}

	//get horzortal vel
	if (X::IsKeyDown(X::Keys::D))
	{
		mCurrentTexture = 2;
		mVelocity.x = speed;
	}else if (X::IsKeyDown(X::Keys::A))
	{
		mCurrentTexture = 6;
		mVelocity.x = -speed;
	}
	else {
		mVelocity.x = 0.0f;
	}

	// check displacement feasible
	X::Math::Vector2 displacement = mVelocity * deltaTime;
	X::Math::Rect currentBox = GetBoundingBox();

	//If moving right
	if (displacement.x > 0.0f)
	{
		X::Math::LineSegment rightEdge{
			currentBox.right + displacement.x,
			currentBox.top,
			currentBox.right + displacement.x,
			currentBox.bottom,
		};
		if (map.CheckCollision(rightEdge))
		{
			displacement.x = 0.0f;
		}
	}
	//If moving left
	if (displacement.x < 0.0f)
	{
		X::Math::LineSegment leftEdge{
			currentBox.left + displacement.x,
			currentBox.top,
			currentBox.left + displacement.x,
			currentBox.bottom,
		};
		if (map.CheckCollision(leftEdge))
		{
			displacement.x = 0.0f;
		}
	}
	//If moving up
	if (displacement.y < 0.0f)
	{
		X::Math::LineSegment upEdge{
			currentBox.left,
			currentBox.top + displacement.y,
			currentBox.right,
			currentBox.top + displacement.y,
		};
		if (map.CheckCollision(upEdge))
		{
			displacement.y = 0.0f;
		}
	}
	// If moving down
	if (displacement.y > 0.0f)
	{
		X::Math::LineSegment bottomEdge{
			currentBox.left,
			currentBox.bottom + displacement.y,
			currentBox.right,
			currentBox.bottom + displacement.y,
		};
		if (map.CheckCollision(bottomEdge))
		{
			displacement.y = 0.0f;
		}
	}
	
	mPosition += displacement;
	
	if ((X::IsKeyDown(X::Keys::W))&&(X::IsKeyDown(X::Keys::D)))
	{
		mCurrentTexture = 1;
	}
	if ((X::IsKeyDown(X::Keys::D)) && (X::IsKeyDown(X::Keys::S)))
	{
		mCurrentTexture = 3;
	}
	if ((X::IsKeyDown(X::Keys::S)) && (X::IsKeyDown(X::Keys::A)))
	{
		mCurrentTexture = 5;
	}
	if ((X::IsKeyDown(X::Keys::A)) && (X::IsKeyDown(X::Keys::W)))
	{
		mCurrentTexture = 7;
	}
}


void Dude::Render(PTCamera &theCamera)
{
	X::Math::Vector2 renderPosition = mPosition;
	renderPosition.x -= X::GetSpriteWidth(mAllTextures[0]) * 0.5f;
	renderPosition.y -= X::GetSpriteHeight(mAllTextures[0]);
	theCamera.Render(mAllTextures[mCurrentTexture], renderPosition);	

	auto rect = GetBoundingBox();
	auto min = theCamera.ConvertToScreen({rect.left,rect.top});
	auto max = theCamera.ConvertToScreen({rect.right,rect.bottom});
	X::DrawScreenRect(min.x,min.y,max.x,max.y,X::Math::Vector4::Red());
}

X::Math::Rect Dude::GetBoundingBox() const
{
	uint32_t width = X::GetSpriteWidth(mAllTextures[mCurrentTexture]);
	uint32_t height = X::GetSpriteHeight(mAllTextures[mCurrentTexture]);
	return{
		mPosition.x - (width * 0.5f),
		mPosition.y - height,
		mPosition.x + (width * 0.5f),
		mPosition.y
	};
}

void Dude::Unload()
{
}
