#include "environment.h"

std::vector<AirTile> airTileMap;

SpawnTile spawnTile;

std::vector<Tile> tileMap;
std::vector<PushTile> pushTileMap;
std::vector<Turret> turretMap;
std::vector<MovingTile> movingTileMap;

void GenerateTileMap() {
	std::ifstream file("../Content/TileMap.txt");
	std::string str;

	std::string intString = "";
	int incrementX = 0, incrementY = 0;
	while (std::getline(file, str))
	{
		for (int x = 0; x < str.length(); x++) {
			if (str[x] == ',' || (x == str.length() - 1 && str[x] == '}')) {
				tileMapGrid[incrementY][incrementX] = std::stoi(intString);
				intString.clear();
				incrementX += 1;
			}
			else {
				if (str[x] != '{' && str[x] != '}') {
					intString += str[x];
				}
			}
		}
		incrementX = 0;
		incrementY += 1;
	}

	for (int y = 0; y < MAPSIZEY; y++) {
		for (int x = 0; x < MAPSIZEX; x++) {
			Turret tempTurret;

			Tile tempTile;
			AirTile tempAirTile;
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
			if (tileMapGrid[y][x] == 12) { tempAirTile.tile.position = Vector2(x * tempAirTile.tile.width, y * tempAirTile.tile.height); tempAirTile.direction = 1; airTileMap.push_back(tempAirTile); }
			if (tileMapGrid[y][x] == 13) { tempAirTile.tile.position = Vector2(x * tempAirTile.tile.width, y * tempAirTile.tile.height); tempAirTile.direction = 2; airTileMap.push_back(tempAirTile); }
			if (tileMapGrid[y][x] == 14) { tempAirTile.tile.position = Vector2(x * tempAirTile.tile.width, y * tempAirTile.tile.height); tempAirTile.direction = 3; airTileMap.push_back(tempAirTile); }
			if (tileMapGrid[y][x] == 15) { tempAirTile.tile.position = Vector2(x * tempAirTile.tile.width, y * tempAirTile.tile.height); tempAirTile.direction = 4; airTileMap.push_back(tempAirTile); }
			if (tileMapGrid[y][x] == 16) { tempTurret.tile.position = Vector2(x * tempTurret.tile.width, y * tempTurret.tile.height); turretMap.push_back(tempTurret); }
		}
	}

	for (auto &turret : turretMap) { turret.GetDirectionX(); turret.GetDirectionY(); }
}

bool CheckCollision(Tile tileA, Tile tileB) {
	if (tileA.left() <= tileB.right() &&
		tileA.right() >= tileB.left() &&
		tileA.top() < tileB.bottom() &&
		tileA.bottom() > tileB.top()) {
		return true;
	}

	return false;
}

bool CheckCollisionRight(Tile tileA, Tile tileB) {
	if (tileA.left() <= tileB.right() && tileA.left() >= tileB.right() - 5 && tileA.top() <= tileB.bottom() - 3 && tileA.bottom() >= tileB.top() + 3) return true;
	return false;
}

bool CheckCollisionLeft(Tile tileA, Tile tileB) {
	if (tileA.right() >= tileB.left() && tileA.right() <= tileB.left() + 5 && tileA.top() <= tileB.bottom() - 3 && tileA.bottom() >= tileB.top() + 3) return true;
	return false;
}

void UpdateTile(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	for (auto &tile : movingTileMap) {
		for (auto &tileB : tileMap) {
			if (CheckCollision(tile.tile, tileB)) { 
				if (CheckCollisionLeft(tile.tile, tileB)) { tile.movingLeft = true; }
				if (CheckCollisionRight(tile.tile, tileB)) { tile.movingLeft = false; }
			}
		}
		if (tile.movingLeft == true) { tile.tile.position.x -= tile.speed * deltaTimeS; }
		else { tile.tile.position.x += tile.speed * deltaTimeS; }
	}
}

void DrawTile(Tile tile, float color[]) {
	DrawRect(tile.position, tile.width, tile.height, color);
}

void DrawMap() {
	float color[3] = { 0, 0, 0 };
	for (auto &tile : tileMap) {
		if (tile.tileID == 1) { color[0] = 0; color[1] = 0; color[2] = 1; }
		if (tile.tileID == 5) { color[0] = 1; color[1] = 0; color[2] = 0; }
		if (tile.tileID == 6) { color[0] = 1; color[1] = 0; color[2] = 1; }
		if (tile.tileID == 7) { color[0] = 1; color[1] = 0; color[2] = 1; }
		DrawTile(tile, color);
	}

	for (auto &tile : movingTileMap) {
		if (tile.tile.tileID == 8) { color[0] = 1; color[1] = 1; color[2] = 0; }
		DrawTile(tile.tile, color);
	}

	color[0] = .6; color[1] = 0; color[2] = .3;
	for (auto &turret : turretMap) {
		DrawTile(turret.tile, color);
	}
}