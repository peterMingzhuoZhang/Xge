#pragma once
#include <XEngine.h>

using X::Math::Vector2;
class Character
{
public:
	Character();

	Character(Vector2 aPosition, Vector2 aVelocity, bool live, X::TextureId textureId, int numInArray);




	Vector2 getPosition() const;
	void setPosition(Vector2 newPosition);
	Vector2 getVelocity() const;
	void setVelocity(Vector2 newVelocity);
	bool getIsAlive() const;
	void setIsAlive(bool aBool);
	X::TextureId getTexture() const;
	void setTexture(X::TextureId textureId);
	int getId() const;
	int getLastContactId() const;
	void setLastContactId(int newId);
	bool isDistoriable() const;
	void setDistoriable(bool isDistoriable);
	void draw() const;
	void move(float deltaTime);
	void respondContact(Character* allNodes, int nodeCount);
private:
	Vector2 position;
	Vector2 velocity;
	bool isAlive;
	bool distroiable;
	X::TextureId texture;
	int id;
	int lastContactNodeId = -1;

};