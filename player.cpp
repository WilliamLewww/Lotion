#include "player.h"

Player player;

void DrawPlayer() {
	GLint texture = LoadTexture("../Content/player.bmp");
	DrawRect(texture, player.position, player.width, player.height);
}