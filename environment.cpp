#include "environment.h"

SpawnTile spawnTile;

std::vector<Tile> tileMap;
std::vector<PushTile> pushTileMap;

void GenerateTileMap() {
	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			Tile tempTile;
			PushTile tempPushTile;

			if (tileMapGrid[y][x] == 1) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 1; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 2) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = false; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 3) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = true; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 4) { spawnTile.position = Vector2(x * spawnTile.width, y * spawnTile.height); spawnTile.tileID = 4; }
			if (tileMapGrid[y][x] == 5) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 5; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 6) { tempTile.position = Vector2(x * tempTile.width, (y * tempTile.height) + 5); tempTile.tileID = 6; tempTile.height = 5; tileMap.push_back(tempTile); }
		}
	}
}

void DrawTile(Tile tile, int color[]) {
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap() {
	int color[3] = { 0, 0, 255 };
	for (auto &tile : tileMap) {
		if (tile.tileID == 1) { color[0] = 0; color[1] = 0; color[2] = 255; }
		if (tile.tileID == 5) { color[0] = 255; color[1] = 0; color[2] = 0; }
		if (tile.tileID == 6) { color[0] = 255; color[1] = 0; color[2] = 255; }
		DrawTile(tile, color);
	}
}