#include "TileMap.h"

#include <fstream>
#include <string>
#include <sstream>

TileMap::TileMap()
	:mRows(0)
	,mColumns(0)
	,mTextCount(0)
	,mTextureSize(0.0f)
{

}

void TileMap::Load(const char* levelFile, const char* tileFile)
{
	XASSERT(mMap == nullptr, "TileMap not empty, call unload befor you load");
	std::string line;
	std::stringstream tokenizer;
	std::ifstream theFile(levelFile);

	XASSERT(theFile.is_open(), "Fail to load file %s", levelFile);

	std::string temp;

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mTextureSize;

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mRows;

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mColumns;

	char theChar;
	mMap = new int[mColumns * mRows];
	for (int i = 0; i < (mColumns * mRows); ++i)
	{
		theFile.get(theChar);
		if (theChar == '\n')
		{
			theFile.get(theChar);
		}
		mMap[i] = (int)(theChar - '0');
	}

	theFile.close();


	theFile = std::ifstream(tileFile);
	XASSERT(theFile.is_open(), "File to load file %s", tileFile);
	

	

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mTextCount;

	mTextureIds = new X::TextureId[mTextCount];
	for (int i = 0; i < mTextCount; ++i)
	{
		getline(theFile, line);
		mTextureIds[i] = X::LoadTexture(line.c_str());
	}
	theFile.close();


	

}

void TileMap::Unload()
{
	X::SafeDeleteArray(mMap);
	X::SafeDeleteArray(mTextureIds);
}

void TileMap::Render(PTCamera &theCamera)
{
	for (int i = 0; i < (mRows * mColumns); ++i)
	{
		
		float postionX = (0.0f + (float)(i % (mColumns ))) * mTextureSize;
		float postionY = (0.0f + (float)(i / (mColumns ))) * mTextureSize;

		theCamera.Render(mTextureIds[mMap[i]], { postionX,postionY });
	}
}

int TileMap::GetIndex(int x, int y) const
{
	if ((x > mColumns) || (x < 0))
	{
		return -1;
	}
	if ((y > mRows) || (y < 0))
	{
		return -1;
	}

	return y * mColumns + x;

}

int TileMap::GetIndex(X::Math::Vector2 pos) const
{
	int x = pos.x / mTextureSize;
	int y = pos.y / mTextureSize;
	return GetIndex(x, y);
}

X::Math::Vector2 TileMap::GetIndexPosition(int index) const
{
	int y = index / mColumns;
	int x = index % mColumns;
	return X::Math::Vector2((float)x * mTextureSize, (float)y * mTextureSize);
}


bool TileMap::CheckCollision(const X::Math::LineSegment & edge) const
{
	int StartX = (int)(edge.from.x / mTextureSize);
	int startY = (int)(edge.from.y / mTextureSize);
	int endX = (int)(edge.to.x / mTextureSize);
	int endY = (int)(edge.to.y / mTextureSize);

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = StartX; x <= endX; x++)
		{
			int tileIndex = GetIndex(x,y);
			if (tileIndex == -1)
			{
				continue;
			}
			if ((mMap[tileIndex] != 0))
			{
				return true;
			}
		}
	}
	return false;
	
}

void TileMap::SaveMap(const char* theFile)
{
	std::ofstream myfile;
	myfile.open(theFile);

	//Start writing in
	myfile << "TileSize: " << mTextureSize << ".0f\n";
	myfile << "Rows: " << mRows << ".0f\n";
	myfile << "Colunms: " << mColumns << ".0f\n";

	for (int i = 0; i < (mColumns * mRows); i++)
	{
		myfile << mMap[i];
		if ((((i+1) % mColumns) == 0)&&(i != 0))
		{
			myfile << "\n";
		}
	}
	myfile.close();
}

