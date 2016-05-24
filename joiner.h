#pragma once
#include "main.h"
#include "player.h"
#include "environment.h"
class Joiner
{
public:
	Joiner();
	void LoadContent();
	void Update(int gameTime);
	void Render();
};