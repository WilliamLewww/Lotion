#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "vector2.h"
#include "spritebatch.h"

const int MAPSIZEX = 80, MAPSIZEY = 60;
static int tileMapGrid[MAPSIZEY][MAPSIZEX];

struct Tile {
	Vector2 position;
	int width = 10, height = 10;
	int tileID = -1;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	int operator==(const Tile& tile)const {
		return (position.x == tile.position.x) && (position.y == tile.position.y);
	}

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};
extern std::vector<Tile> tileMap;

struct Turret {
	Tile tile;

	double projectileSpeed = 5;
	double interval = 2.5;

	int directionX = 0, directionY = 0;

	// 0 = both; 1 = right; 2 = left; 3 = null
	inline void GetDirectionX() {
		int direction = 0;

		for (auto &tileB : tileMap) {
			if (tile.position.y == tileB.position.y && tile.position.x - tile.width == tileB.position.x) { direction += 1; }
			if (tile.position.y == tileB.position.y && tile.position.x + tile.width == tileB.position.x) { direction += 2; }
		}

		directionX = direction;
	}

	// 0 = both; 1 = bottom; 2 = top; 3 = null;
	inline void GetDirectionY() {
		int direction = 0;

		for (auto &tileB : tileMap) {
			if (tile.position.x == tileB.position.x && tile.position.y - tile.height == tileB.position.y) { direction += 1; }
			if (tile.position.x == tileB.position.x && tile.position.y + tile.height == tileB.position.y) { direction += 2; }
		}

		directionY = direction;
	}
};
extern std::vector<Turret> turretMap;

struct MovingTile {
	Tile tile;

	double speed = 25;
	bool movingLeft = false;
};
extern std::vector<MovingTile> movingTileMap;

struct AirTile {
	Tile tile;

	// 1 = up; 2 = down; 3 = left; 4 = right;
	int direction = -1;
	double speed = .5;
};
extern std::vector<AirTile> airTileMap;

struct SpawnTile {
	Vector2 position;
	int width = 10, height = 10;
	int tileID = -1;

	inline Vector2 midpoint() { return Vector2(position.x + (position.x / 2), position.y + (position.y / 2)); }

	int operator==(const Tile& tile)const {
		return (position.x == tile.position.x) && (position.y == tile.position.y);
	}

	inline double top() { return position.y; }
	inline double bottom() { return position.y + height; }
	inline double left() { return position.x; }
	inline double right() { return position.x + width; }
};
extern SpawnTile spawnTile;

struct PushTile {
	Tile tile;
	double force = 100;
	int initialDirection = -1;
	bool end = false;

	//0=up 1=down 2=right 3=left
	inline int GetDirection(std::vector<PushTile> tileMap) {
		for (auto &otherTile : tileMap) {
			//othertile = left
			if (otherTile.tile.position.x == (tile.position.x - tile.width) && (otherTile.tile.position.y == tile.position.y)) {
				if (end == true) return 2;
				otherTile.initialDirection = 2;
				if (initialDirection == -1) return 3;
				if (initialDirection != 2) return 3;
			}
			//othertile = right
			if (otherTile.tile.position.x == (tile.position.x + tile.width) && (otherTile.tile.position.y == tile.position.y)) {
				if (end == true) return 3;
				otherTile.initialDirection = 3;
				if (initialDirection == -1) return 2;
				if (initialDirection != 3) return 2;
			}
			//othertile = down
			if (otherTile.tile.position.y == (tile.position.y - tile.height) && (otherTile.tile.position.x == tile.position.x)) {
				if (end == true) return 0;
				otherTile.initialDirection = 0;
				if (initialDirection == -1) return 1;
				if (initialDirection != 0) return 1;
			}
			//othertile = up
			if (otherTile.tile.position.y == (tile.position.y + tile.height) && (otherTile.tile.position.x == tile.position.x)) {
				if (end == true) return 1;
				otherTile.initialDirection = 1;
				if (initialDirection == -1) return 0;
				if (initialDirection != 1) return 0;
			}
		}

		return -1;
	};
};
extern std::vector<PushTile> pushTileMap;

void GenerateTileMap();
void UpdateTile(int gameTime);
void DrawMap();