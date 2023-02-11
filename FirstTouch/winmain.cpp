
#include "Character.h"
#include <iostream>

// Global Variable;
X::TextureId gameOverTexture;
X::TextureId youwinTexture;
X::SoundId hit_id;
X::Math::Vector2 position1{ 25.0f,200.0f };
X::Math::Vector2 velocity1{ -200.0f,200.0f };
X::Math::Vector2 velocity2{ 500.0f,-500.0f };
float base_height = 700;
bool fired = false;
X::Math::Vector2 ball_ini_pos;
float ball_cur_x_pos;
float ball_cur_y_pos;
float ball_x_move = 1;
float ball_y_move = -1;
//Nodes
Character* Bricks;
Character Bat;
Character Ball;
const int columnCount = 10;
const int rowCount = 4;
int alive_bricks = rowCount * columnCount;
float pre_ball_x_pos;
float pre_ball_y_pos;

// Forward declaration:
bool CheckBatCollision(Character attacker, X::TextureId b_texture);
int CheckBrickCollision(const Character& attacker, Character brick, X::TextureId b_texture);
void InitializeC();
bool GameLoopC(float deltaTime);
void TerminateC();


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//start up logic 
	X::Start();
	
	InitializeC();

	
	X::Run(GameLoopC);
	
	// clean up
	TerminateC();
	
	X::Stop();
	return 0;
}

void InitializeC() {
	X::TextureId bat_texture = X::LoadTexture("hummer.png");
	Bat = Character(position1, { 0.0f,0.0f }, true, bat_texture, 0);

	X::TextureId ball_texture = X::LoadTexture("enemy_0_1_0.png");
	Ball = Character(position1, { 300.0f,-300.0f }, true, ball_texture, 0);

	X::TextureId bricks_id = X::LoadTexture("mushroom.png");
	Bricks = new Character[columnCount*rowCount];

	hit_id = X::LoadSound("laser.wav");

	gameOverTexture = X::LoadTexture("gameOver.png");
	youwinTexture = X::LoadTexture("youwin.jpg");

	float x_axis_gap = X::GetScreenWidth() / columnCount;
	float brick_x_start_point = 0.5 * X::GetSpriteWidth(bricks_id);
	float brick_y_start_point = 0.5 * X::GetSpriteHeight(bricks_id);


	for (int i = 0; i < columnCount; ++i)
	{
		for (int j = 0; j < rowCount; ++j) {
			Bricks[j*10 + i] = Character(Vector2{ x_axis_gap/2 + x_axis_gap * i + brick_x_start_point, 100.0f * j + brick_y_start_point }, { 0.0f,0.0f }, true, bricks_id, i);
		}
	}
}

void TerminateC() {
	X::ClearAllTextures();
	X::ClearAllSounds();
}

bool GameLoopC(float deltaTime) {
	float mouse_x_pos = (float)(X::GetMouseScreenX());
	float mouse_y_pos = (float)(X::GetMouseScreenY());
	Bat.setPosition(X::Math::Vector2{ mouse_x_pos,base_height });
	X::TextureId ball_texture = X::LoadTexture("enemy_0_1_0.png");
	X::TextureId bat_texture = X::LoadTexture("hummer.png");
	X::TextureId bricks_id = X::LoadTexture("mushroom.png");

	Bat.move(deltaTime);
	Bat.draw();

	if (!fired && X::IsKeyDown(X::Keys::SPACE)) {
		fired = true;
		ball_cur_x_pos = mouse_x_pos;
		ball_cur_y_pos = base_height - 0.5 * X::GetSpriteHeight(bat_texture);
		Ball.setPosition(X::Math::Vector2{ ball_cur_x_pos,ball_cur_y_pos  });
		pre_ball_x_pos = ball_cur_x_pos;
		pre_ball_y_pos = ball_cur_y_pos;
	}
	for (int i = 0; i < rowCount * columnCount; ++i)
	{
		if (Bricks[i].getIsAlive()) {
			Bricks[i].draw();
		}
		
	}
	if (fired && Ball.getIsAlive()) {
		ball_cur_x_pos = Ball.getPosition().x;
		ball_cur_y_pos = Ball.getPosition().y;

		if (ball_cur_x_pos + 0.5 * X::GetSpriteWidth(ball_texture) > X::GetScreenWidth() || ball_cur_x_pos - 0.5 * X::GetSpriteWidth(ball_texture) < 0) {
			Vector2 pre_velocity = Ball.getVelocity();
			pre_velocity.x *= -1.0f;
			Ball.setVelocity(pre_velocity);
		}
		if (ball_cur_y_pos - 0.5 * X::GetSpriteWidth(ball_texture) < 0) {
			Vector2 pre_velocity = Ball.getVelocity();
			pre_velocity.y *= -1.0f;
			Ball.setVelocity(pre_velocity);
		}

		
		if (CheckBatCollision(Ball, bat_texture)) {
			Vector2 pre_velocity = Ball.getVelocity();
			pre_velocity.y *= -1.0f;
			Ball.setVelocity(pre_velocity);
		}

		for (int i = 0; i < columnCount*rowCount && alive_bricks!=0; ++i)
		{
			int collision_result = CheckBrickCollision(Ball, Bricks[i], bricks_id);
			if (Bricks[i].getIsAlive() && collision_result!=0) {
				Vector2 pre_velocity = Ball.getVelocity();
				if (collision_result == 1) {
					pre_velocity.y *= -1.0f;
				}
				else if (collision_result == 2) {
					pre_velocity.x *= -1.0f;
				}
				Ball.setVelocity(pre_velocity);
				Bricks[i].setIsAlive(false); 
				alive_bricks--;
				X::PlaySoundOneShot(hit_id);
			}
		}
		if (ball_cur_y_pos + 0.5 * X::GetSpriteWidth(ball_texture) > X::GetScreenHeight()) {
			Ball.setIsAlive(false);
		}
		pre_ball_x_pos = Ball.getPosition().x;
		pre_ball_y_pos = Ball.getPosition().y;
		Ball.move(deltaTime);
		Ball.draw();
	}
	if (alive_bricks == 0) {
		X::Math::Vector2 youwinPostion = X::Math::Vector2{ (float)(X::GetScreenWidth() / 2)
									,(float)(X::GetScreenHeight() / 2) };
		X::DrawSprite(youwinTexture, youwinPostion);
	}
	if (!Ball.getIsAlive()) {
		X::Math::Vector2 gameOverPostion = X::Math::Vector2{ (float)(X::GetScreenWidth() / 2)
									,(float)(X::GetScreenHeight() / 2) };
		X::DrawSprite(gameOverTexture, gameOverPostion);
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
bool CheckBatCollision(Character attacker, X::TextureId b_texture) {
	float attacker_cur_x_pos = attacker.getPosition().x;
	float attacker_cur_y_pos = attacker.getPosition().y; 

	if ((attacker_cur_y_pos >= base_height - 0.5 * X::GetSpriteHeight(b_texture)) &&					//top side check
		(attacker_cur_y_pos <= base_height + 0.5 * X::GetSpriteHeight(b_texture)) &&					//down side check
		(attacker_cur_x_pos <= (float)(X::GetMouseScreenX()) + 0.5 * X::GetSpriteWidth(b_texture)) &&	//right side check
		(attacker_cur_x_pos >= (float)(X::GetMouseScreenX()) - 0.5 * X::GetSpriteWidth(b_texture))) {	//left side check
		return true;
	}
	
	return false;
}
int CheckBrickCollision(const Character& attacker, Character brick, X::TextureId b_texture) {
	float attacker_cur_x_pos = attacker.getPosition().x;
	float attacker_cur_y_pos = attacker.getPosition().y;
	int result = 0;

	if ((attacker_cur_y_pos >= brick.getPosition().y - 0.5 * X::GetSpriteHeight(b_texture)) &&					//top side check
		(attacker_cur_y_pos <= brick.getPosition().y + 0.5 * X::GetSpriteHeight(b_texture)) &&					//down side check
		(attacker_cur_x_pos <= brick.getPosition().x + 0.5 * X::GetSpriteWidth(b_texture)) &&	//right side check
		(attacker_cur_x_pos >= brick.getPosition().x - 0.5 * X::GetSpriteWidth(b_texture))) {	//left side check
		if ((pre_ball_x_pos <= brick.getPosition().x + 0.5 * X::GetSpriteWidth(b_texture)) &&
			(pre_ball_x_pos >= brick.getPosition().x - 0.5 * X::GetSpriteWidth(b_texture))) {
			result = 1;//ball touched brich from top or bottom
		}
		
		if ((pre_ball_y_pos <= brick.getPosition().y - 0.5 * X::GetSpriteHeight(b_texture)) &&
				(pre_ball_y_pos >= brick.getPosition().y  + 0.5 * X::GetSpriteHeight(b_texture))) {
			result = 2;//ball touched brich from left or right
		}
		
	}

	return result;
}