#include "TileMap.h"
#include <fstream>
#include <string>

TileMap::TileMap()
	: mMap(nullptr)
	, mCol(0)
	, mRow(0)
	, mTileSize(0)
	, mTextureCount(0)
	, mTextures(nullptr)
{
}

TileMap::TileMap(std::string filename)
{
}

TileMap::~TileMap()
{
	 X::SafeDeleteArray(mMap);
	 X::SafeDeleteArray(mTextures);
}

void TileMap::Load(std::string fileName, std::string tileFile)
{
	XASSERT(mMap == nullptr, "TileMap not empty, call unload befor you load");
	std::string line;
	std::stringstream tokenizer;
	const char* fileCstr = fileName.c_str();
	std::ifstream theFile(fileCstr);

	XASSERT(theFile.is_open(), "Fail to load file %s", fileCstr);

	std::string temp;

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mTileSize;

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mRow;

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mCol;

	char theChar;
	mMap = new int[mCol * mRow];
	for (int i = 0; i < (mCol * mRow); ++i)
	{
		theFile.get(theChar);
		if (theChar == '\n')
		{
			theFile.get(theChar);
		}
		mMap[i] = (int)(theChar - '0');
	}

	theFile.close();

	const char* tileFileCstr = tileFile.c_str();
	theFile = std::ifstream(tileFileCstr);
	XASSERT(theFile.is_open(), "File to load file %s", tileFileCstr);

	getline(theFile, line);
	tokenizer = std::stringstream(line);
	tokenizer >> temp;
	tokenizer >> mTextureCount;

	mTextures = new X::TextureId[mTextureCount];
	for (int i = 0; i < mTextureCount; ++i)
	{
		getline(theFile, line);
		mTextures[i] = X::LoadTexture(line.c_str());
	}
	theFile.close();


}

void TileMap::Draw()
{
	for (int i = 0; i < (mCol * mRow); i++)
	{
		float postionX = (0.0f + (float)(i % (mCol))) * mTileSize + mTileSize * 0.5f;
		float postionY = (0.0f + (float)(i / (mCol))) * mTileSize + mTileSize * 0.5f;

		X::DrawSprite(mTextures[mMap[i]], { postionX,postionY });
	}
}

void TileMap::Save(std::string fileName)
{
	std::ofstream myfile;
	myfile.open(fileName.c_str());

	//Start writing in
	myfile << "TileSize: " << mTileSize << ".0f\n";
	myfile << "Rows: " << mRow << ".0f\n";
	myfile << "Colunms: " << mCol << ".0f\n";

	for (int i = 0; i < (mCol * mRow); i++)
	{
		myfile << mMap[i];
		if ((((i + 1) % mCol) == 0) && (i != 0))
		{
			myfile << "\n";
		}
	}
	myfile.close();
}
