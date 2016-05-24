#include "environment.h"

SpawnTile spawnTile;

std::vector<Tile> tileMap;
std::vector<PushTile> pushTileMap;

void GenerateTileMap() {
	Tile tempTile;
	PushTile tempPushTile;

	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			if (tileMapGrid[y][x] == 1) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 1; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 2) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = false; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 3) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = true; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 4) { spawnTile.position = Vector2(x * spawnTile.width, y * spawnTile.height); spawnTile.tileID = 4; }
		}
	}
}

void DrawTile(Tile tile) {
	int color[3] = { 255, 0, 0 };
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap() {
	for (auto &tile : tileMap) {
		DrawTile(tile);
	}
}