#include "Menu.h"
#include "Game.h"
#include "Options.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

//Get already existing variables; window and renderer
 extern SDL_Window* window;
 extern SDL_Renderer* renderer;

 //Get mouse coordinates; mouseX and mouseY
 int mouseX;
 int mouseY;

 //Get already existing variable; [opponent] to test if game is against player or pc/ai
 extern int opponent;

 //Define all textures and set them to NULL
SDL_Texture* title = NULL;
SDL_Texture* button1 = NULL;
SDL_Texture* button2 = NULL;
SDL_Texture* button3 = NULL;
SDL_Texture* button4 = NULL;
SDL_Texture* button5 = NULL;

SDL_Texture* playButton = NULL;
SDL_Texture* optionsButton = NULL;
SDL_Texture* quitButton = NULL;

SDL_Texture* currentPlayButton = NULL;
SDL_Texture* currentOptionsButton = NULL;
SDL_Texture* currentQuitButton = NULL;

SDL_Texture* vsPlayerButton = NULL;
SDL_Texture* vsPCButton = NULL;

SDL_Texture* currentVsPlayerButton = NULL;
SDL_Texture* currentVsPcButton = NULL;

//Get already existing variables; [width] and [height] for screen size
extern int width;
extern int height;

//Variable used to test if user wants to exit game from menu
bool menuExitGame = false;

//Get already existing variable; [optionsExitGame] to reset the variable so it can run again
extern bool optionsExitGame;

//Get already existing variables; [readLoop] and [OptionsLoop] to reset them so they can be used again
extern bool readLoop;
extern bool OptionsLoop;

//Sets up the window and renderer
void SDLSetup() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		cerr << "SDL failed to initialize.\n";
	}
	else {

		window = SDL_CreateWindow("Tic-Tac-Toe Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_RENDERER_PRESENTVSYNC);
		if (window == NULL) {
			cerr << "Failed to create window.";
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			cerr << "Failed to create renderer.";
		}

	}

}

//Sets the textures to defined variables
void MenuTextureSetup() {

	title = IMG_LoadTexture(renderer, "Images/title.png");

	playButton = IMG_LoadTexture(renderer, "Images/play.png");
	optionsButton = IMG_LoadTexture(renderer, "Images/options.png");
	quitButton = IMG_LoadTexture(renderer, "Images/quit.png");

	currentPlayButton = IMG_LoadTexture(renderer, "Images/current_play.png");
	currentOptionsButton = IMG_LoadTexture(renderer, "Images/current_options.png");
	currentQuitButton = IMG_LoadTexture(renderer, "Images/current_quit.png");

	vsPlayerButton = IMG_LoadTexture(renderer, "Images/vs_player.png");
	vsPCButton = IMG_LoadTexture(renderer, "Images/vs_pc.png");

	currentVsPlayerButton = IMG_LoadTexture(renderer, "Images/current_vs_player.png");
	currentVsPcButton = IMG_LoadTexture(renderer, "Images/current_vs_pc.png");

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}

//Main Code Class
Menu::Menu()
{
	//Variable used to know which button is highlighted
	int current = 0;

	//Variable used to toggle between stages of the menu (See/Unsee "vs Player" or "vs Pc"
	int menuStage = 0;

	//Calls both methods
	SDLSetup();
	MenuTextureSetup();

	//Creates main event
	SDL_Event* mainEvent = new SDL_Event();

	//Pre-defining all rects for textures (Positions, Sizes)
	SDL_Rect titleRect;
	titleRect.x = width / 2 - 300;
	titleRect.y = 250;
	titleRect.w = 600;
	titleRect.h = 150;

	SDL_Rect playButtonRect;
	playButtonRect.x = 30;
	playButtonRect.y = height - 350;
	playButtonRect.w = 150;
	playButtonRect.h = 50;

	SDL_Rect optionsButtonRect;
	optionsButtonRect.x = 30;
	optionsButtonRect.y = height - 250;
	optionsButtonRect.w = 250;
	optionsButtonRect.h = 50;

	SDL_Rect quitButtonRect;
	quitButtonRect.x = 30;
	quitButtonRect.y = height - 150;
	quitButtonRect.w = 150;
	quitButtonRect.h = 50;

	SDL_Rect vsPlayerRect;
	vsPlayerRect.x = 350;
	vsPlayerRect.y = height - 350;
	vsPlayerRect.w = 240;
	vsPlayerRect.h = 50;

	SDL_Rect vsPcRect;
	vsPcRect.x = 350;
	vsPcRect.y = height - 250;
	vsPcRect.w = 240;
	vsPcRect.h = 50;

	//Main loop
	while (menuExitGame == false) {

		//Get mouse state and set mouseX and mouseY positions
		SDL_GetMouseState(&mouseX, &mouseY);

		//If player clicks the exit button on the window = exit game
		if (mainEvent->type == SDL_QUIT) {
			menuExitGame = true;
		}

		//Test if either Play, Options or Exit button has been hovered over or clicked on (Using mouse or keyboard input)
		if (menuStage == 0) {

			if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.w + playButtonRect.x && mouseY >= playButtonRect.y && mouseY <= playButtonRect.h + playButtonRect.y) {
				current = 0;
				if (SDL_PollEvent(mainEvent) == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							current = 0;
							menuStage = 1;
							button1 = playButton;
							button4 = currentVsPlayerButton;
							button5 = vsPCButton;

						}
					}
				}
			}

			if (mouseX >= optionsButtonRect.x && mouseX <= optionsButtonRect.w + optionsButtonRect.x && mouseY >= optionsButtonRect.y && mouseY <= optionsButtonRect.h + optionsButtonRect.y) {
				current = 1;
				if (SDL_PollEvent(mainEvent) == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							optionsExitGame = false;
							OptionsLoop = false;
							Options Options;
							current = 0;

						}
					}
				}
			}

			if (mouseX >= quitButtonRect.x && mouseX <= quitButtonRect.w + quitButtonRect.x && mouseY >= quitButtonRect.y && mouseY <= quitButtonRect.h + quitButtonRect.y) {
				current = 2;
				if (SDL_PollEvent(mainEvent) == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							menuExitGame = true;

						}
					}
				}
			}

			//Makes buttons highlight depending on where the mouse cursor is or which state the keyboard is at
			if (current == 0) {

				button1 = currentPlayButton;
				button2 = optionsButton;
				button3 = quitButton;

			}
			else if (current == 1) {

				button1 = playButton;
				button2 = currentOptionsButton;
				button3 = quitButton;

			}
			else if (current == 2) {

				button1 = playButton;
				button2 = optionsButton;
				button3 = currentQuitButton;

			}

			//If an event is passed
			if (SDL_PollEvent(mainEvent) == 1) {
			
				//Following code inside "SDL_KEYDOWN" is keyboard input to navigate through the menu system
				if (mainEvent->type == SDL_KEYDOWN) {
				
					if (mainEvent->key.keysym.sym == SDLK_s) {

						if (current <= 1) {

							current += 1;

						}
						else if (current == 2) {

							current = 0;

						}

					}

					if (mainEvent->key.keysym.sym == SDLK_w) {

						if (current >= 1) {

							current -= 1;

						}
						else if (current == 0) {

							current = 2;

						}

					}
					//EXIT BUTTON
					if (mainEvent->key.keysym.sym == SDLK_RETURN && current == 2) {

						menuExitGame = true;

					}
					//PLAY BUTTON
					else if (mainEvent->key.keysym.sym == SDLK_RETURN && current == 0) {

						current = 0;
						menuStage = 1;
						button1 = playButton;
						button4 = currentVsPlayerButton;
						button5 = vsPCButton;

					}
					//OPTIONS BUTTON
					else if (mainEvent->key.keysym.sym == SDLK_RETURN && current == 1) {
						optionsExitGame = false;
						OptionsLoop = false;
						Options Options;
						current = 0;

					}
				
				}

			}

		}
		//Test if either vsPlayer or vsPc button has been hovered over or clicked on (Using mouse or keyboard input)
		if (menuStage == 1) {

			if (mouseX >= vsPlayerRect.x && mouseX <= vsPlayerRect.w + vsPlayerRect.x && mouseY >= vsPlayerRect.y && mouseY <= vsPlayerRect.h + vsPlayerRect.y) {
				current = 0;
				if (SDL_PollEvent(mainEvent) == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							opponent = 0;
							Game Game;
							readLoop = false;

						}
					}
				}
			}

			else if (mouseX >= vsPcRect.x && mouseX <= vsPcRect.w + vsPcRect.x && mouseY >= vsPcRect.y && mouseY <= vsPcRect.h + vsPcRect.y) {
				current = 1;
				if (SDL_PollEvent(mainEvent) == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							opponent = 1;
							Game Game;
							readLoop = false;

						}
					}
				}
			}

			if (current == 0) {

				button4 = currentVsPlayerButton;
				button5 = vsPCButton;

			}
			else if (current == 1) {

				button4 = vsPlayerButton;
				button5 = currentVsPcButton;

			}

			if (SDL_PollEvent(mainEvent) == 1) {

				if (mainEvent->type == SDL_KEYDOWN) {

					if (mainEvent->key.keysym.sym == SDLK_s) {


						if (current == 0) {

							current = 1;

						}
						else if (current == 1) {

							current = 0;

						}

					}

					if (mainEvent->key.keysym.sym == SDLK_w) {

						if (current == 0) {

							current = 1;

						}
						else if (current == 1) {

							current = 0;

						}
					}
					
					if (mainEvent->key.keysym.sym == SDLK_RETURN && current == 0) {
						opponent = 0;
						Game Game;
						readLoop = false;
					}
					else if (mainEvent->key.keysym.sym == SDLK_RETURN && current == 1) {
						opponent = 1;
						Game Game;
						readLoop = false;
					}
					if (mainEvent->key.keysym.sym == SDLK_BACKSPACE && menuStage == 1) {

						menuStage = 0;
						current = 0;
						button4 = NULL;
						button5 = NULL;

					}

				}
			}
		}

		//Main rendering system to render textures onto the screen
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, title, NULL, &titleRect);
		SDL_RenderCopy(renderer, button1, NULL, &playButtonRect);
		SDL_RenderCopy(renderer, button2, NULL, &optionsButtonRect);
		SDL_RenderCopy(renderer, button3, NULL, &quitButtonRect);
		SDL_RenderCopy(renderer, button4, NULL, &vsPlayerRect);
		SDL_RenderCopy(renderer, button5, NULL, &vsPcRect);

		SDL_RenderPresent(renderer);
		//rendering stops here
	}
	//If user exits the game, run this
	if (menuExitGame == true) {
		
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		delete mainEvent;
		SDL_Quit;

	}

}


Menu::~Menu()
{
}
