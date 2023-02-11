#include "Character.h"

Character::Character()
	: position(Vector2{ 0.0f,0.0f })
	, velocity(Vector2{ 0.0f,0.0f })
	, isAlive(true)
	, texture(NULL)
	, id(0)
	, distroiable(false) {


}

Character::Character(Vector2 aPosition, Vector2 aVelocity, bool live, X::TextureId textureId, int numInArray)
	:position(aPosition)
	, velocity(aVelocity)
	, isAlive(live)
	, texture(textureId)
	, id(numInArray)
	, distroiable(false) {

}

Vector2 Character::getPosition() const {
	return position;
}
void Character::setPosition(Vector2 newPosition) {
	position = newPosition;
}
Vector2 Character::getVelocity() const {
	return velocity;
}
void Character::setVelocity(Vector2 newVelocity) {
	velocity = newVelocity;
}
bool Character::getIsAlive() const {
	return isAlive;
}
void Character::setIsAlive(bool aBool) {
	isAlive = aBool;
}
X::TextureId Character::getTexture() const {
	return texture;
}
void Character::setTexture(X::TextureId textureId) {
	texture = textureId;
}
int Character::getId() const {
	return id;
}
int Character::getLastContactId() const {
	return lastContactNodeId;
}
void Character::setLastContactId(int newId) {
	lastContactNodeId = newId;
}
bool Character::isDistoriable() const {
	return distroiable;
}
void Character::setDistoriable(bool isDistoriable) {
	distroiable = isDistoriable;
}
void Character::move(float deltaTime) {
	if (isAlive)
	{
		position += velocity * deltaTime;
	}

}
void Character::draw() const {
	if (isAlive)
	{
		X::DrawSprite(texture, position);
	}

}
void Character::respondContact(Character* allNodes, int nodeCount) {

	if (position.x <= 0.0f) {
		if (velocity.x > 0) {

		}
		else {
			velocity.x *= -1.0f;
		}
		lastContactNodeId = -1;
	}
	else if (position.x + X::GetSpriteWidth(texture) >= X::GetScreenWidth())
	{
		if (velocity.x > 0) {
			velocity.x *= -1.0f;
		}
		else {

		}
		lastContactNodeId = -1;
	}
	if (position.y <= 0.0f) {
		if (velocity.y > 0) {

		}
		else {
			velocity.y *= -1.0f;
		}
		lastContactNodeId = -1;
	}
	else if (position.y + X::GetSpriteHeight(texture) >= X::GetScreenHeight()) {
		if (velocity.y > 0) {
			velocity.y *= -1.0f;
		}
		else {

		}
		lastContactNodeId = -1;
	}



	Vector2 nodeALeftBottom = Vector2{ position.x,position.y + X::GetSpriteHeight(texture) };
	Vector2 nodeAUpRight = Vector2{ position.x + X::GetSpriteWidth(texture) ,position.y };
	Vector2 nodeBLeftBottom = Vector2{ 0,0 };
	Vector2 nodeBUpRight = Vector2{ 0,0 };

	for (int i = 0; i < nodeCount; ++i)
	{
		nodeBLeftBottom = Vector2{ allNodes[i].getPosition().x,allNodes[i].getPosition().y + X::GetSpriteHeight(allNodes[i].getTexture()) };
		nodeBUpRight = Vector2{ allNodes[i].getPosition().x + X::GetSpriteWidth(allNodes[i].getTexture()),allNodes[i].getPosition().y };
		if ((id != i) && ((i != lastContactNodeId) || (allNodes[i].getLastContactId() != id))) {
			if ((nodeAUpRight.y <= nodeBLeftBottom.y) && (nodeALeftBottom.y >= nodeBUpRight.y)) {
				if ((nodeAUpRight.x >= nodeBLeftBottom.x) && (nodeALeftBottom.x <= nodeBUpRight.x)) {
					float xDifferent = X::Math::Abs(nodeAUpRight.x - nodeBUpRight.x);
					float yDifferent = X::Math::Abs(nodeAUpRight.y - nodeBUpRight.y);
					if (xDifferent < yDifferent) {
						//reflect Y
						velocity.y *= -1.0f;
						lastContactNodeId = i;
					}
					else if (xDifferent > yDifferent) {
						//reflect X
						velocity.x *= -1.0f;
						lastContactNodeId = i;


					}
					else {
						//reflect X and Y
						velocity.x *= -1.0f;
						velocity.y *= -1.0f;
						lastContactNodeId = i;
					}
				}
			}
		}
	}

}