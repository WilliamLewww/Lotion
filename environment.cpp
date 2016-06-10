#include "environment.h"

SpawnTile spawnTile;

std::vector<Tile> tileMap;
std::vector<PushTile> pushTileMap;
std::vector<MovingTile> movingTileMap;

void GenerateTileMap() {
	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			Tile tempTile;
			PushTile tempPushTile;
			MovingTile tempMovingTile;

			if (tileMapGrid[y][x] == 1) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 1; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 2) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = false; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 3) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = true; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 4) { spawnTile.position = Vector2(x * spawnTile.width, y * spawnTile.height); spawnTile.tileID = 4; }
			if (tileMapGrid[y][x] == 5) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 5; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 6) { tempTile.position = Vector2(x * tempTile.width, (y * tempTile.height) + 5); tempTile.tileID = 6; tempTile.height = 5; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 7) { tempTile.position = Vector2(x * tempTile.width, (y * tempTile.height) + 5); tempTile.tileID = 7; tempTile.height = 5; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 8) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 7; tempTile.height = 5; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 9) { tempMovingTile.tile.position = Vector2(x * tempMovingTile.tile.width, y * tempMovingTile.tile.height); tempMovingTile.tile.tileID = 8; movingTileMap.push_back(tempMovingTile); }
			if (tileMapGrid[y][x] == 10) { tempMovingTile.tile.position = Vector2(x * tempMovingTile.tile.width, (y * tempMovingTile.tile.height) + 5); tempMovingTile.tile.height = 5; tempMovingTile.tile.tileID = 8; movingTileMap.push_back(tempMovingTile); }
			if (tileMapGrid[y][x] == 11) { tempMovingTile.tile.position = Vector2(x * tempMovingTile.tile.width, y * tempMovingTile.tile.height); tempMovingTile.tile.height = 5; tempMovingTile.tile.tileID = 8; movingTileMap.push_back(tempMovingTile); }
		}
	}
}

bool CheckCollision(Tile tileA, Tile tileB) {
	if (tileA.left() <= tileB.right() &&
		tileA.right() >= tileB.left() &&
		tileA.top() <= tileB.bottom() &&
		tileA.bottom() >= tileB.top()) {
		return true;
	}

	return false;
}

void UpdateTile(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	for (auto &tile : movingTileMap) {
		for (auto &tileB : tileMap) {
			if (CheckCollision(tile.tile, tileB)) { tile.movingLeft = !tile.movingLeft; }
		}
		if (tile.movingLeft == true) { tile.tile.position.x -= tile.speed * deltaTimeS; }
		else { tile.tile.position.x += tile.speed * deltaTimeS; }
	}
}

void DrawTile(Tile tile, int color[]) {
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap() {
	int color[3] = { 0, 0, 0 };
	for (auto &tile : tileMap) {
		if (tile.tileID == 1) { color[0] = 0; color[1] = 0; color[2] = 255; }
		if (tile.tileID == 5) { color[0] = 255; color[1] = 0; color[2] = 0; }
		if (tile.tileID == 6) { color[0] = 255; color[1] = 0; color[2] = 255; }
		if (tile.tileID == 7) { color[0] = 255; color[1] = 0; color[2] = 255; }
		DrawTile(tile, color);
	}

	for (auto &tile : movingTileMap) {
		if (tile.tile.tileID == 8) { color[0] = 255; color[1] = 255; color[2] = 0; }
		DrawTile(tile.tile, color);
	}
}