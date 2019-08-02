#include <iostream>
#include "Menu.h"
#include "Options.h"
#include <SDL_image.h>
#include <SDL.h>
#include <fstream>
#include <string>
using namespace std;

//A variable to keep track which button is currently being hovered over (Keyboard and Mouse input)
int optionsSelect = 0;

//Setting main options to default temporarily
int tileNumber = 0;
int timerNumber = 3;

//Variable used to temporarily store a single character from the options.txt file
char read;

bool OptionsLoop;

//Get already existing variables; [width] and [height] for screen size
extern int width;
extern int height;

//Get already existing variables; [mouseX] and [mouseY] to test for mouse position
extern int mouseX;
extern int mouseY;

extern bool menuExitGame;

//Get already existing variables; [mSec] and [sec] to reset timer mechanic
extern int mSec;
extern int sec;

//Variable used to test if user wants to exit game from options menu
bool optionsExitGame;

//Get already existing variables; [window] and [renderer]
extern SDL_Window* window;
extern SDL_Renderer* renderer;

//Define rects for textures
SDL_Rect optionsTitleRect;
SDL_Rect optionsTilePresetsRect;
SDL_Rect optionsTimerRect;
SDL_Rect optionsTile3Rect;
SDL_Rect optionsTile4Rect;
SDL_Rect optionsTile5Rect;
SDL_Rect optionsTimerOnRect;
SDL_Rect optionsTimerOffRect;
SDL_Rect optionsBackRect;
SDL_Rect selectFadePreset;
SDL_Rect selectFade1Rect;
SDL_Rect selectFade2Rect;
SDL_Rect selectFade3Rect;

//Define all textures and set them to NULL
SDL_Texture* optionsTitle = NULL;
SDL_Texture* optionsTilePresets = NULL;
SDL_Texture* optionsTimer = NULL;
SDL_Texture* optionsTile3 = NULL;
SDL_Texture* optionsTileNumber = NULL; //TO CHANGE BETWEEN ALL THE PRESETS
SDL_Texture* optionsTile4 = NULL;
SDL_Texture* optionsTile5 = NULL;
SDL_Texture* optionsTimerOn = NULL;
SDL_Texture* optionsTimerOff = NULL;
SDL_Texture* optionsTimerNum = NULL;
SDL_Texture* optionsBack = NULL;
SDL_Texture* selectFade = NULL;

//Sets the textures to defined variables
void OptionsTextureSetup() {

	optionsTitle = IMG_LoadTexture(renderer, "Images/current_options.png");
	optionsTilePresets = IMG_LoadTexture(renderer, "Images/options_tile_presets.png");
	optionsTimer = IMG_LoadTexture(renderer, "Images/options_timer.png");
	optionsTile3 = IMG_LoadTexture(renderer, "Images/options_tile_3x3.png");
	optionsTile4 = IMG_LoadTexture(renderer, "Images/options_tile_4x4.png");
	optionsTile5 = IMG_LoadTexture(renderer, "Images/options_tile_5x5.png");
	optionsTimerOn = IMG_LoadTexture(renderer, "Images/options_timer_on.png");
	optionsTimerOff = IMG_LoadTexture(renderer, "Images/options_timer_off.png");
	optionsBack = IMG_LoadTexture(renderer, "Images/options_back.png");
	selectFade = IMG_LoadTexture(renderer, "Images/fade.png");

}

//Sets up the texture's rects (Positions, Sizes)
void OptionsSetupRects() {

	optionsTitleRect.x = width / 2 - 250;
	optionsTitleRect.y = 100;
	optionsTitleRect.w = 500;
	optionsTitleRect.h = 100;

	optionsTilePresetsRect.x = width / 4 - 200;
	optionsTilePresetsRect.y = height / 2 - 50;
	optionsTilePresetsRect.w = 200;
	optionsTilePresetsRect.h = 100;

	optionsTimerRect.x = width / 4 - 200;
	optionsTimerRect.y = height / 2 + 50;
	optionsTimerRect.w = 200;
	optionsTimerRect.h = 100;

	optionsTile3Rect.x = width / 3 - 50;
	optionsTile3Rect.y = height / 2 - 55;
	optionsTile3Rect.w = 100;
	optionsTile3Rect.h = 100;

	optionsTile4Rect.x = width / 3 - 50;
	optionsTile4Rect.y = height / 2 - 55;
	optionsTile4Rect.w = 100;
	optionsTile4Rect.h = 100;

	optionsTile5Rect.x = width / 3 - 50;
	optionsTile5Rect.y = height / 2 - 55;
	optionsTile5Rect.w = 100;
	optionsTile5Rect.h = 100;

	optionsTimerOnRect.x = width / 3 - 50;
	optionsTimerOnRect.y = height / 2 + 47;
	optionsTimerOnRect.w = 100;
	optionsTimerOnRect.h = 100;

	optionsTimerOffRect.x = width / 3 - 50;
	optionsTimerOffRect.y = height / 2 + 47;
	optionsTimerOffRect.w = 100;
	optionsTimerOffRect.h = 100;

	optionsBackRect.x = width / 4 - 200;
	optionsBackRect.y = height / 2 + 200;
	optionsBackRect.w = 110;
	optionsBackRect.h = 80;

	selectFade1Rect.x = width / 4 - 210;
	selectFade1Rect.y = height / 2 - 40;
	selectFade1Rect.w = 350;
	selectFade1Rect.h = 70;

	selectFade2Rect.x = width / 4 - 210;
	selectFade2Rect.y = height / 2 + 60;
	selectFade2Rect.w = 350;
	selectFade2Rect.h = 70;

	selectFade3Rect.x = width / 4 - 210;
	selectFade3Rect.y = height / 2 + 200;
	selectFade3Rect.w = 150;
	selectFade3Rect.h = 70;

}

//Main Code Class
Options::Options() {

	//Calls both methods
	OptionsTextureSetup();
	OptionsSetupRects();

	//Creates main event
	SDL_Event* mainEvent = new SDL_Event();

	//Sets optionsFile as input or output stream for files.
	fstream optionsFile;

	//Main loop
	while (optionsExitGame == false) {

		//Reseting timer
		mSec = 0;
		sec = 0;

		//Get mouse state and set mouseX and mouseY positions
		SDL_GetMouseState(&mouseX, &mouseY);

		//If player clicks the exit button on the window = exit game
		if (mainEvent->type == SDL_QUIT) {

			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			menuExitGame = true;
			SDL_Quit;

		}

		//Opens and reads the options.txt file holding settings (0 = 3x3 Tiles, 1 = 4x4 Tiles, 2 = 5x5 Tiles, 3 = Timer OFF, 4 = Timer ON)
		optionsFile.open("options.txt");
		while (OptionsLoop == false) {

			read = optionsFile.get();
			if (read == '0') {
				tileNumber = 0;
				cout << "0" << endl;
			}
			else if (read == '1') {
				tileNumber = 1;
				cout << "1" << endl;
			}
			else if (read == '2') {
				tileNumber = 2;
				cout << "2" << endl;
			}
			else if (read == '3') {
				timerNumber = 3;
				cout << "3" << endl;
				OptionsLoop = true;
			}
			else if (read == '4') {
				timerNumber = 4;
				cout << "4" << endl;
				OptionsLoop = true;
			}

		}
		optionsFile.close();

		//Test if any existing button has been hovered over or clicked on (Using mouse or keyboard input)
		if (mouseX >= selectFade1Rect.x && mouseX <= selectFade1Rect.w + selectFade1Rect.x && mouseY >= selectFade1Rect.y && mouseY <= selectFade1Rect.h + selectFade1Rect.y) {
			optionsSelect = 0;
			if (SDL_PollEvent(mainEvent) == 1) {
				if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
					if (mainEvent->button.button == SDL_BUTTON_LEFT) {

						if (tileNumber >= 2) {
							tileNumber = 0;
						}
						else {
							tileNumber += 1;
						}

					}
				}
			}
		}

		if (mouseX >= selectFade2Rect.x && mouseX <= selectFade2Rect.w + selectFade2Rect.x && mouseY >= selectFade2Rect.y && mouseY <= selectFade2Rect.h + selectFade2Rect.y) {
			optionsSelect = 1;
			if (SDL_PollEvent(mainEvent) == 1) {
				if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
					if (mainEvent->button.button == SDL_BUTTON_LEFT) {

						if (timerNumber >= 4) {
							timerNumber = 3;
						}
						else {
							timerNumber += 1;
						}

					}
				}
			}
		}

		if (mouseX >= selectFade3Rect.x && mouseX <= selectFade3Rect.w + selectFade3Rect.x && mouseY >= selectFade3Rect.y && mouseY <= selectFade3Rect.h + selectFade3Rect.y) {
			optionsSelect = 2;
			if (SDL_PollEvent(mainEvent) == 1) {
				if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
					if (mainEvent->button.button == SDL_BUTTON_LEFT) {

						optionsSelect = 0;
						optionsFile.open("options.txt");
						optionsFile << tileNumber;
						optionsFile << timerNumber;
						optionsFile.close();
						optionsExitGame = true;

					}
				}
			}
		}

		if (SDL_PollEvent(mainEvent) == 1) {

			if (mainEvent->type == SDL_KEYDOWN) {

				if (mainEvent->key.keysym.sym == SDLK_s) {

					if (optionsSelect >= 2) {
						optionsSelect = 0;
					}
					else {
						optionsSelect += 1;
					}

				}

				if (mainEvent->key.keysym.sym == SDLK_w) {

					if (optionsSelect <= 0) {
						optionsSelect = 2;
					}
					else {
						optionsSelect -= 1;
					}

				}
				
				if (mainEvent->key.keysym.sym == SDLK_RETURN && optionsSelect == 0) {
					if (tileNumber >= 2) {
						tileNumber = 0;
					}
					else {
						tileNumber += 1;
					}
				}

				if (mainEvent->key.keysym.sym == SDLK_RETURN && optionsSelect == 1) {
				
					if (timerNumber >= 4) {
						timerNumber = 3;
					}
					else {
						timerNumber += 1;
					}
				
				}

				if (mainEvent->key.keysym.sym == SDLK_RETURN && optionsSelect == 2) {

					optionsSelect = 0;
					optionsFile.open("options.txt");
					optionsFile << tileNumber;
					optionsFile << timerNumber;
					optionsFile.close();
					optionsExitGame = true;

				}


			}

		}

		//Show which button is being hovered over
		if (optionsSelect == 0) {
			selectFadePreset = selectFade1Rect;
		}
		else if (optionsSelect == 1) {
			selectFadePreset = selectFade2Rect;
		}
		else if (optionsSelect == 2) {
			selectFadePreset = selectFade3Rect;
		}

		//Show/Change tile setting
		if (tileNumber == 0) {
			optionsTileNumber = optionsTile3;
		}
		else if (tileNumber == 1) {
			optionsTileNumber = optionsTile4;
		}
		else if (tileNumber == 2) {
			optionsTileNumber = optionsTile5;
		}
		//Show/Change timer setting
		if (timerNumber == 3) {
			optionsTimerNum = optionsTimerOff;
		}
		else if (timerNumber == 4) {
			optionsTimerNum = optionsTimerOn;
		}

		//Main rendering system to render textures onto the screen
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, optionsTitle, NULL, &optionsTitleRect);
		SDL_RenderCopy(renderer, optionsTilePresets, NULL, &optionsTilePresetsRect);
		SDL_RenderCopy(renderer, optionsTimer, NULL, &optionsTimerRect);
		SDL_RenderCopy(renderer, optionsTileNumber, NULL, &optionsTile3Rect);
		SDL_RenderCopy(renderer, optionsTimerNum, NULL, &optionsTimerOffRect);
		SDL_RenderCopy(renderer, optionsBack, NULL, &optionsBackRect);
		SDL_RenderCopy(renderer, selectFade, NULL, &selectFadePreset);

		SDL_RenderPresent(renderer);
		//rendering stops here

	}

}

Options::~Options() {

}