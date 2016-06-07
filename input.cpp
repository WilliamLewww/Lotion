#include "input.h"
#include <iostream>

std::vector<SDL_Keycode> keyList;
std::vector<SDL_Keycode> pressKeyList;

bool leftButtonDown;
int mouseX, mouseY;

void GetKeys(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		if (std::find(keyList.begin(), keyList.end(), event.key.keysym.sym) == keyList.end()) {
			pressKeyList.push_back(event.key.keysym.sym);
			keyList.push_back(event.key.keysym.sym);
		}
	}

	if (event.type == SDL_KEYUP) {
		keyList.erase(std::remove(keyList.begin(), keyList.end(), event.key.keysym.sym), keyList.end());
	}
}

void RemoveInitialPress() {
	pressKeyList.clear();
}

void GetButtons(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftButtonDown = true;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftButtonDown = false;
		}
	}

	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.motion.x;
		mouseY = event.motion.y;
	}
}