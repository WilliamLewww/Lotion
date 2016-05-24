#pragma once
#include "vector2.h"
#include "spritebatch.h"

struct Player {
	Vector2 position;
	int width = 15, height = 15;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }

	bool onGround = false;
	double velocityX, velocityY;

	double speed = 100;
};

extern Player player;
void DrawPlayer();