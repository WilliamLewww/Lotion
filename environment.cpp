#include "environment.h"

SpawnTile spawnTile;

std::vector<Tile> tileMap;
std::vector<PushTile> pushTileMap;
std::vector<Trampoline> trampolineMap;
std::vector<HarmfulTile> harmfulTileMap;

void GenerateTileMap() {
	Tile tempTile;
	PushTile tempPushTile;
	Trampoline tempTrampoline;
	HarmfulTile tempharmfulTile;

	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			if (tileMapGrid[y][x] == 1) { tempTile.position = Vector2(x * tempTile.width, y * tempTile.height); tempTile.tileID = 1; tileMap.push_back(tempTile); }
			if (tileMapGrid[y][x] == 2) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = false; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 3) { tempPushTile.tile.position = Vector2(x * tempPushTile.tile.width, y * tempPushTile.tile.height); tempPushTile.tile.tileID = 2; tempPushTile.end = true; pushTileMap.push_back(tempPushTile); }
			if (tileMapGrid[y][x] == 4) { spawnTile.position = Vector2(x * spawnTile.width, y * spawnTile.height); spawnTile.tileID = 4; }
			if (tileMapGrid[y][x] == 5) { tempharmfulTile.tile.position = Vector2(x * tempharmfulTile.tile.width, y * tempharmfulTile.tile.height); tempharmfulTile.tile.tileID = 5; harmfulTileMap.push_back(tempharmfulTile); }
			if (tileMapGrid[y][x] == 6) { tempTrampoline.tile.position = Vector2(x * tempTrampoline.tile.width, (y * tempTrampoline.tile.height) + 5); tempTrampoline.tile.tileID = 6; tempTrampoline.tile.height = 5; trampolineMap.push_back(tempTrampoline); }
		}
	}
}

void DrawTile(Tile tile, int color[]) {
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap() {
	int color[3] = { 0, 0, 255 };
	for (auto &tile : tileMap) {
		DrawTile(tile, color);
	}

	color[0] = 255; color[2] = 0;
	for (auto &tile : harmfulTileMap) {
		DrawTile(tile.tile, color);
	}

	color[0] = 255; color[2] = 255;
	for (auto &tile : trampolineMap) {
		DrawTile(tile.tile, color);
	}
}