#pragma once
#include "vector2.h"
#include "spritebatch.h"

struct Player {
	Vector2 position;
	int width = 5, height = 5;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }

	bool onGround = false;
	double velocityX, velocityY;

	double speed = 50;
	double jumpSpeed = 2.5;
};

extern Player player;
void UpdatePlayer(int gameTime);
void DrawPlayer();