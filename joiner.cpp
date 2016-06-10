#include "joiner.h"

Joiner::Joiner() {

}

void Joiner::LoadContent() {
	GenerateTileMap();
	player.position = Vector2(spawnTile.position.x, spawnTile.position.y);
}

void Joiner::Update(int gameTime) {
	UpdateTile(gameTime);
	UpdatePlayer(gameTime);
}

void Joiner::Render() {
	DrawPlayer();
	DrawMap();
}