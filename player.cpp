#include "player.h"

Player player;

void ResetPlayer();

bool CheckCollisionTop(Tile tile);
bool CheckCollisionBottom(Tile tile);
bool CheckCollisionLeft(Tile tile);
bool CheckCollisionRight(Tile tile);

bool CheckCollision(Tile tile);
void HandleCollision(Tile tile);
void HandleBasicCollision(Tile tile);
void FloatingMovement(float deltaTimeS);

std::vector<Tile> groundTileList;
bool jumpPress = false;
bool floatingMovement = false;
void UpdatePlayer(int gameTime) {
	float deltaTimeS = (float)(gameTime) / 1000;

	for (auto &tile : pushTileMap) {
		if (CheckCollision(tile.tile) == true) {
			//0=up 1=down 2=right 3=left
			if (tile.GetDirection(pushTileMap) == 0) { player.velocityY = tile.force * deltaTimeS; player.velocityX = 0; }
			if (tile.GetDirection(pushTileMap) == 1) { player.velocityY = -tile.force * deltaTimeS; player.velocityX = 0; }
			if (tile.GetDirection(pushTileMap) == 2) { player.velocityX = tile.force * deltaTimeS; player.velocityY = 0; }
			if (tile.GetDirection(pushTileMap) == 3) { player.velocityX = -tile.force * deltaTimeS; player.velocityY = 0; }
		}
	}

	if (floatingMovement) FloatingMovement(deltaTimeS);

	player.position.x += player.velocityX;
	player.position.y += player.velocityY;
	player.velocityX = 0;

	if (std::find(pressKeyList.begin(), pressKeyList.end(), SDLK_r) != pressKeyList.end()) { ResetPlayer(); }
	if (std::find(pressKeyList.begin(), pressKeyList.end(), SDLK_f) != pressKeyList.end()) floatingMovement = !floatingMovement;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) { player.speed = 65; }
	else { player.speed = 50; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) player.velocityX = -player.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) player.velocityX = player.speed * deltaTimeS;

	for (auto &tile : airTileMap) {
		if (CheckCollision(tile.tile) == true) {
			if (tile.direction == 1) { player.position.y -= tile.speed; }
			if (tile.direction == 2) { player.position.y += tile.speed; }
			if (tile.direction == 3) { player.position.x -= tile.speed; }
			if (tile.direction == 4) { player.position.x += tile.speed; }
		}
	}

	if (player.onGround == true) {
		if (jumpPress == false) {
			if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end()) {
				player.velocityY = -player.jumpSpeed; player.onGround = false; jumpPress = true;
			}
		}
	}
	else {
		player.velocityY += 9.8 * deltaTimeS;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) == keyList.end()) {
		if (player.velocityY < 0 && player.onGround == false) player.velocityY += 9.8 * deltaTimeS;
		if (player.onGround == true) jumpPress = false;
	}

	bool trampolineCollison = false;
	for (auto &tile : tileMap) {
		if (CheckCollision(tile) == true) {
			if (tile.tileID == 1) { HandleCollision(tile); }
			if (tile.tileID == 5) { ResetPlayer(); }

			if (tile.tileID == 6) { 
				if (CheckCollisionTop(tile) && trampolineCollison == false) { if (player.velocityY != 0) { player.velocityY = -player.velocityY; } }
				else { HandleCollision(tile); }

				trampolineCollison = true;
			}

			if (tile.tileID == 7) {
				if (CheckCollision(tile) && trampolineCollison == false) {
					player.velocityY = (-player.velocityY / abs(player.velocityY)) * 2.5;
				}

				trampolineCollison = true;
			}
		}
	}

	bool movingTileCollision = false;
	for (auto &tile : movingTileMap) {
		if (CheckCollision(tile.tile) == true) {
			movingTileCollision = true;
			HandleBasicCollision(tile.tile);

			if (CheckCollisionLeft(tile.tile) == true) { tile.movingLeft = false; }
			if (CheckCollisionRight(tile.tile) == true) { tile.movingLeft = true; }
			if (CheckCollisionLeft(tile.tile) == false && CheckCollisionRight(tile.tile) == false) {
				if (tile.movingLeft == true) {
					player.position.x -= tile.speed * deltaTimeS;
				}
				else {
					player.position.x += tile.speed * deltaTimeS;
				}
			}
		}
	}

	std::vector<Tile> tempGroundTileList;
	for (auto &tile : groundTileList) {
		if (CheckCollision(tile) == false) {
			tempGroundTileList.push_back(tile);
		}
	}

	for (auto &tile : tempGroundTileList) {
		groundTileList.erase(std::remove(groundTileList.begin(), groundTileList.end(), tile), groundTileList.end());
	}
	tempGroundTileList.clear();

	if (groundTileList.size() == 0 && movingTileCollision == false) player.onGround = false;
}

void ResetPlayer() {
	player.velocityX = 0; 
	player.velocityY = 0; 
	player.position = Vector2(spawnTile.position.x, spawnTile.position.y);
}

void FloatingMovement(float deltaTimeS) {
	player.velocityX = 0;
	player.velocityY = 0;
	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) player.velocityX = -player.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) player.velocityX = player.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_UP) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_DOWN) == keyList.end()) player.velocityY = -player.speed * deltaTimeS;
	if (std::find(keyList.begin(), keyList.end(), SDLK_DOWN) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_UP) == keyList.end()) player.velocityY = player.speed * deltaTimeS;
}

//player.Left <= rectangle.Right &&
//player.Right >= rectangle.Left &&
//player.Top <= rectangle.Bottom &&
//player.Bottom >= rectangle.Top

bool CheckCollision(Tile tile) {
	if (player.left() <= tile.right() &&
		player.right() >= tile.left() &&
		player.top() <= tile.bottom() &&
		player.bottom() >= tile.top()) {
		return true;
	}

	return false;
}

//player.top <= tile.bottom && player.top >= tile.bottom - 5 && player.left <= tile.right - 5 && player.right >= tile.left + 5:
bool CheckCollisionBottom(Tile tile) {
	if (player.top() <= tile.bottom() && player.top() >= tile.bottom() - 5 && player.left() <= tile.right() - 3 && player.right() >= tile.left() + 3) return true;
	return false;
}

bool CheckCollisionTop(Tile tile) {
	if (player.bottom() >= tile.top() && player.bottom() <= tile.top() + 5 && player.left() <= tile.right() + 3 && player.right() >= tile.left() + 3) return true;
	return false;
}

bool CheckCollisionRight(Tile tile) {
	if (player.left() <= tile.right() && player.left() >= tile.right() - 5 && player.top() <= tile.bottom() - 3 && player.bottom() >= tile.top() + 3) return true;
	return false;
}

bool CheckCollisionLeft(Tile tile) {
	if (player.right() >= tile.left() && player.right() <= tile.left() + 5 && player.top() <= tile.bottom() - 3 && player.bottom() >= tile.top() + 3) return true;
	return false;
}

void HandleBasicCollision(Tile tile) {
	double overlapX, overlapY;
	if (player.midpoint().x > tile.midpoint().x) overlapX = tile.right() - player.left();
	else overlapX = -(player.right() - tile.left());
	if (player.midpoint().y > tile.midpoint().y) overlapY = tile.bottom() - player.top();
	else overlapY = -(player.bottom() - tile.top());

	if (overlapX != 0 && overlapY != 0) {
		if (abs(overlapY) < abs(overlapX)) {
			if (overlapY < 0) {
				if (player.velocityY > 0) {
					player.onGround = true;
					player.position.y += overlapY; player.velocityY = 0;
				}
			}
			else {
				if (player.velocityY < 0) {
					if (CheckCollisionBottom(tile)) { player.position.y += overlapY; player.velocityY = 0; }
				}
			}
		}
		else {
			player.position.x += overlapX; player.velocityX = 0;
		}
	}
}

void HandleCollision(Tile tile) {
	double overlapX, overlapY;
	if (player.midpoint().x > tile.midpoint().x) overlapX = tile.right() - player.left();
	else overlapX = -(player.right() - tile.left());
	if (player.midpoint().y > tile.midpoint().y) overlapY = tile.bottom() - player.top();
	else overlapY = -(player.bottom() - tile.top());

	if (overlapX != 0 && overlapY != 0) {
		if (abs(overlapY) < abs(overlapX)) {
			if (overlapY < 0) {
				if (player.velocityY > 0) {
					player.onGround = true;
					player.position.y += overlapY; player.velocityY = 0;
					if (std::find(groundTileList.begin(), groundTileList.end(), tile) == groundTileList.end()) groundTileList.push_back(tile);
				}
			}
			else {
				if (player.velocityY < 0) {
					if (CheckCollisionBottom(tile)) { player.position.y += overlapY; player.velocityY = 0; }
				}
			}
		}
		else {
			player.position.x += overlapX; player.velocityX = 0;
		}
	}
}

void DrawPlayer() {
	GLint texture = LoadTexture("../Content/player.bmp");
	DrawRect(texture, player.position, player.width, player.height);
}