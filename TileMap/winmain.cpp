
#include <iostream>
#include <XEngine.h>
#include "TileMap.h"

TileMap tileMap;

void Init() {
	tileMap.Load("level00.txt", "tiles.txt");
}

bool GameLoop(float dt) 
{
	tileMap.Draw();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void Terminate() {
	
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	X::Start();

	Init();
	X::Run(GameLoop);
	Terminate();
	X::Stop();
	return 0;
}