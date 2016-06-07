#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>

void GetKeys(SDL_Event event);
void RemoveInitialPress();
extern std::vector<SDL_Keycode> keyList;
extern std::vector<SDL_Keycode> pressKeyList;

void GetButtons(SDL_Event event);
extern bool leftButtonDown;
extern int mouseX, mouseY;