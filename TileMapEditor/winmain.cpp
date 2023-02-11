#include <XEngine.h>

#include "EditorCursor.h"

const char* levelFile = "level01.txt";
const char* tileFile = "tileset01.txt";

void Initialize();
void Terminate();

TileMap myTileMap;
EditorCursor myEditor;
PTCamera dudeCamera;

bool GameLoop(float deltaTime)
{

	
	dudeCamera.SetViewPos(myEditor.getPostion());
	myEditor.Update(myTileMap, dudeCamera, deltaTime);

	myTileMap.Render(dudeCamera);
	
	myEditor.Render(dudeCamera);
	

	char fps[128];
	sprintf_s(fps, 128, "%.2f", 1.0f / deltaTime);
	X::DrawScreenText(fps, 10.0f, 10.0f, 15.0f, X::Math::Vector4::White());

	if (X::IsKeyPressed(X::Keys::S))
	{
		myTileMap.SaveMap(levelFile);
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	Initialize();
	X::Run(GameLoop);
	Terminate();
	X::Stop();
	return 0;
}

void Initialize()
{
	myTileMap.Load(levelFile,tileFile);
	myEditor.Load(myTileMap);
	myEditor.setPostion({ 500.0f,500.0f });

	dudeCamera.SetViewPos(myEditor.getPostion());

}

void Terminate()
{
	myTileMap.Unload();
	myEditor.Unload();
}