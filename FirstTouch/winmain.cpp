
#include "Character.h"
#include <iostream>

// Global Variable;
X::TextureId gameOverTexture;
X::Math::Vector2 position1{ 25.0f,200.0f };
X::Math::Vector2 velocity1{ -200.0f,200.0f };
X::Math::Vector2 velocity2{ 500.0f,-500.0f };
X::Math::Vector2 movingVelocityRight{ 700.0f,0.0f };
X::Math::Vector2 movingVelocityleft{ -700.0f,0.0f };
X::Math::Vector2 movingVelocityUp{ 0.0f,700.0f };
X::Math::Vector2 movingVelocityDown{ 0.0f,-700.0f };
//Nodes
Character* myCharacters;
Character mainCharacter;
const int nodeCount = 36;

// Forward declaration:
void InitializeA();
bool GameLoopA(float deltaTime);
void TerminateA();
void InitializeB();
bool GameLoopB(float deltaTime);
void TerminateB();



int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//start up logic 
	X::Start();
	
	//InitializeA();
	InitializeB();

	
	//X::Run(GameLoopA);
	X::Run(GameLoopB);
	
	// clean up
	//TerminateA();
	TerminateB();

	X::Stop();
	return 0;
}

void InitializeA() {
	X::TextureId textureId1 = X::LoadTexture("mushroom.png");
	myCharacters = new Character[nodeCount];
	for (int i = 0; i < nodeCount; ++i)
	{
		X::Math::Vector2 posDifferent = Vector2{ 100.0f,100.0f } *(float)i;
		myCharacters[i] = Character(position1 + posDifferent, velocity1, true, textureId1, i);
	}
}
void TerminateA() {
	X::ClearAllTextures();
	delete[] myCharacters;
}

void InitializeB() {
	gameOverTexture = X::LoadTexture("gameOver.png");
	X::TextureId texture = X::LoadTexture("zelda.png");
	mainCharacter = Character(position1, {0.0f,0.0f}, true, texture, 0);

}
void TerminateB() {
	X::ClearAllTextures();
}

bool GameLoopA(float deltaTime) {

	for (int i = 0; i < nodeCount; ++i)
	{
		myCharacters[i].respondContact(myCharacters, nodeCount);

	}
	for (int i = 0; i < nodeCount; ++i)
	{
		myCharacters[i].move(deltaTime);
		myCharacters[i].draw();
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

bool GameLoopB(float deltaTime) {

	if (X::IsKeyDown(X::Keys::LEFT)) {
		mainCharacter.setVelocity(movingVelocityleft);
		mainCharacter.move(deltaTime);

	}
	else if (X::IsKeyDown(X::Keys::RIGHT)) {
		mainCharacter.setVelocity(movingVelocityRight);
		mainCharacter.move(deltaTime);
	}

	if (X::IsKeyDown(X::Keys::UP)) {
		mainCharacter.setVelocity(movingVelocityUp);
		mainCharacter.move(deltaTime);

	}
	else if (X::IsKeyDown(X::Keys::DOWN)) {
		mainCharacter.setVelocity(movingVelocityDown);
		mainCharacter.move(deltaTime);
	}

	mainCharacter.draw();

	X::Math::Vector2 gameOverPostion = X::Math::Vector2{ (float)(X::GetScreenWidth() / 2)
										,(float)(X::GetScreenHeight() / 2) };
	X::DrawSprite(gameOverTexture, gameOverPostion);
	return X::IsKeyPressed(X::Keys::ESCAPE);
}