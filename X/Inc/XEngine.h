//====================================================================================================
// Filename:	XEngine.h
// Created by:	Peter Chan
//====================================================================================================

#ifndef INCLUDED_XENGINE_H
#define INCLUDED_XENGINE_H

#include "XCore.h"
#include "XMath.h"
#include "XInputTypes.h"

namespace X {

void Start(const char* configFileName = nullptr);
void Run(bool (*GameLoop)(float));
void Stop();

// Config Functions
int ConfigGetInt(const char* key, int defaultValue = 0);
bool ConfigGetBool(const char* key, bool defaultValue = false);
float ConfigGetFloat(const char* key, float defaultValue = 0.0f);
const char* ConfigGetString(const char* key, const char* defaultValue = "");

// Camera Functions
void SetCameraPosition(const Math::Vector3& position);
void SetCameraDirection(const Math::Vector3& direction);
void SetCameraTarget(const Math::Vector3& target);

// Resource Functions
SoundId LoadSound(const char* fileName);
void ClearAllSounds();
TextureId LoadTexture(const char* fileName);
void ClearAllTextures();

// Audio Functions
void PlaySoundOneShot(SoundId soundId);
void PlaySoundLoop(SoundId soundId);
void StopSoundLoop(SoundId soundId);

// Graphics Functions
void DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, const Math::Vector4& color);
void DrawAABB(const Math::AABB& aabb, const Math::Vector4& color);
void DrawAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Math::Vector4& color);
void DrawOBB(const Math::OBB& obb, const Math::Vector4& color);
void DrawSphere(const Math::Vector3& center, float radius, const Math::Vector4& color, uint32_t slices = 8, uint32_t rings = 4);
void DrawSphere(float x, float y, float z, float radius, const Math::Vector4& color, uint32_t slices = 8, uint32_t rings = 4);
void DrawScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Math::Vector4& color);
void DrawScreenLine(float x0, float y0, float x1, float y1, const Math::Vector4& color);
void DrawScreenRect(const Math::Rect& rect, const Math::Vector4& color);
void DrawScreenRect(float l, float t, float r, float b, const Math::Vector4& color);
void DrawScreenCircle(const Math::Circle& circle, const Math::Vector4& color);
void DrawScreenCircle(const Math::Vector2& center, float r, const Math::Vector4& color);
void DrawScreenCircle(float x, float y, float r, const Math::Vector4& color);
void DrawScreenDiamond(const Math::Vector2& center, float size, const Math::Vector4& color);
void DrawScreenDiamond(float x, float y, float size, const Math::Vector4& color);
void DrawScreenText(const char* str, float x, float y, float size, const Math::Vector4& color);
void DrawSprite(TextureId textureId, const Math::Vector2& position);
void DrawSprite(TextureId textureId, const Math::Vector2& position, float rotation);
void DrawSprite(TextureId textureId, const Math::Rect& sourceRect, const Math::Vector2& position);
uint32_t GetSpriteWidth(TextureId textureId);
uint32_t GetSpriteHeight(TextureId textureId);
uint32_t GetScreenWidth();
uint32_t GetScreenHeight();

// Random Functions
int Random();
int Random(int min, int max);
float RandomFloat();
float RandomFloat(float min, float max);
Math::Vector2 RandomVector2();
Math::Vector2 RandomVector2(const Math::Vector2& min, const Math::Vector2& max);
Math::Vector2 RandomUnitCircle();
Math::Vector3 RandomVector3();
Math::Vector3 RandomVector3(const Math::Vector3& min, const Math::Vector3& max);
Math::Vector3 RandomUnitSphere();

// Keyboard Functions
bool IsKeyDown(int key);
bool IsKeyPressed(int key);

// Mouse Functions
bool IsMouseDown(int button);
bool IsMousePressed(int button);
int GetMouseMoveX();
int GetMouseMoveY();
int GetMouseScreenX();
int GetMouseScreenY();
bool IsMouseLeftEdge();
bool IsMouseRightEdge();
bool IsMouseTopEdge();
bool IsMouseBottomEdge();

void ShowSystemCursor(bool show);
void SetMouseClipToWindow(bool clip);
bool IsMouseClipToWindow();

Math::Ray GetMouseRay();
Math::Ray GetScreenRay(int screenX, int screenY);

} // namespace X

#endif // #ifndef INCLUDED_XENGINE_H