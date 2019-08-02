#include <iostream>
#include "Menu.h"
#include "Game.h"
#include <SDL_image.h>
#include <SDL.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
using namespace std;

//Get already existing variables; [window] and [renderer]
extern SDL_Window* window;
extern SDL_Renderer* renderer;

//Get already existing variables; [width] and [height] for screen size
extern int width;
extern int height;

//Get already existing variable; [read] to use the same process as from the Options menu (read file and setup the game with the settings given)
extern char read;

//Get already existing variables; [mouseX] and [mouseY] to test for mouse position
extern int mouseX;
extern int mouseY;

//Variable "read" sets [gamemode] up depending on what it reads (gamemode 0 = 3x3 Tiles, etc..)
int gamemode = 0;

//Variable is set based on the button you press in main menu (vs Player = opponent 0, etc..)
int opponent = 0;

//Variable "read" sets [timer] up depending on what it read (timer 0 = timer OFF, etc..)
int timer = 0;

//Randomisation value for AI to play
int randomNum;

//Variable for "read" loop to continue unless it has gotten all the information required for the game to run (e.g. gamemode, timer, etc..)
bool readLoop;

//Loop variable so the AI only places a tile in a free space.
bool aiLoop;

//Setting board sizes
int currentPosition3[9]{1,2,3,4,5,6,7,8,9};
int currentPosition4[16]{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int currentPosition5[25]{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};

//Variables that hold which player is currently playing on each tile setting (playerTurn3 = 3x3 Tiles)
int playerTurn3 = 0;
int playerTurn4 = 0;
int playerTurn5 = 0;

//Variable to show if game has come to an end (WIN or DRAW)
int endGame = 0;

//Variable to reset the counter of how many plays have been made per match (counter3 being 9 = DRAW only if a player hasn't won)
int counter3 = 0;
int counter4 = 0;
int counter5 = 0;

//Variable used to test if boardPosition hasn't been taken on their respective gamemode (3x3 Tiles = three)
int three = 0;
int four = 0;
int five = 0;

//Variables used for the timer
int mSec = 0;
int sec = 0;

//Define rects for textures
SDL_Rect whoWonRect;
SDL_Rect fadeRect;
SDL_Rect boardRect;
SDL_Rect currentPlayerRect;
SDL_Rect playersMarkerRect;

SDL_Rect board3Pos0Rect;
SDL_Rect board3Pos1Rect;
SDL_Rect board3Pos2Rect;
SDL_Rect board3Pos3Rect;
SDL_Rect board3Pos4Rect;
SDL_Rect board3Pos5Rect;
SDL_Rect board3Pos6Rect;
SDL_Rect board3Pos7Rect;
SDL_Rect board3Pos8Rect;

SDL_Rect board4Pos0Rect;
SDL_Rect board4Pos1Rect;
SDL_Rect board4Pos2Rect;
SDL_Rect board4Pos3Rect;
SDL_Rect board4Pos4Rect;
SDL_Rect board4Pos5Rect;
SDL_Rect board4Pos6Rect;
SDL_Rect board4Pos7Rect;
SDL_Rect board4Pos8Rect;
SDL_Rect board4Pos9Rect;
SDL_Rect board4Pos10Rect;
SDL_Rect board4Pos11Rect;
SDL_Rect board4Pos12Rect;
SDL_Rect board4Pos13Rect;
SDL_Rect board4Pos14Rect;
SDL_Rect board4Pos15Rect;


SDL_Rect board5Pos0Rect;
SDL_Rect board5Pos1Rect;
SDL_Rect board5Pos2Rect;
SDL_Rect board5Pos3Rect;
SDL_Rect board5Pos4Rect;
SDL_Rect board5Pos5Rect;
SDL_Rect board5Pos6Rect;
SDL_Rect board5Pos7Rect;
SDL_Rect board5Pos8Rect;
SDL_Rect board5Pos9Rect;
SDL_Rect board5Pos10Rect;
SDL_Rect board5Pos11Rect;
SDL_Rect board5Pos12Rect;
SDL_Rect board5Pos13Rect;
SDL_Rect board5Pos14Rect;
SDL_Rect board5Pos15Rect;
SDL_Rect board5Pos16Rect;
SDL_Rect board5Pos17Rect;
SDL_Rect board5Pos18Rect;
SDL_Rect board5Pos19Rect;
SDL_Rect board5Pos20Rect;
SDL_Rect board5Pos21Rect;
SDL_Rect board5Pos22Rect;
SDL_Rect board5Pos23Rect;
SDL_Rect board5Pos24Rect;


//Define all textures and set them to NULL
SDL_Texture* fadeWin = NULL;
SDL_Texture* gameEnd = NULL;
SDL_Texture* whoWon = NULL;
SDL_Texture* draw = NULL;
SDL_Texture* player1Wins = NULL;
SDL_Texture* player2Wins = NULL;

SDL_Texture* board3x3 = NULL;
SDL_Texture* board4x4 = NULL;
SDL_Texture* board5x5 = NULL;

SDL_Texture* boardPosition3[9]{ NULL };
SDL_Texture* boardPosition4[16]{ NULL };
SDL_Texture* boardPosition5[25]{ NULL };

SDL_Texture* currentPlayer = NULL;
SDL_Texture* currentMarker = NULL;

SDL_Texture* player1 = NULL;
SDL_Texture* player1X = NULL;
SDL_Texture* player2O = NULL;
SDL_Texture* player2 = NULL;

SDL_Texture* player1Marker = NULL;
SDL_Texture* player2Marker = NULL;

//Variable used to test if user wants to exit game
bool gameExitGame;

//Sets optionsFile as input or output stream for files.
fstream optionsFile;

//Sets the textures to defined variables
void GameTextureSetup() {

	fadeWin = IMG_LoadTexture(renderer, "Images/fade.png");
	draw = IMG_LoadTexture(renderer, "Images/players_draw.png");
	player1Wins = IMG_LoadTexture(renderer, "Images/player1_win.png");
	player2Wins = IMG_LoadTexture(renderer, "Images/player2_win.png");
	board3x3 = IMG_LoadTexture(renderer, "Images/grid3x3.png");
	board4x4 = IMG_LoadTexture(renderer, "Images/grid4x4.png");
	board5x5 = IMG_LoadTexture(renderer, "Images/grid5x5.png");
	player1 = IMG_LoadTexture(renderer, "Images/player_1.png");
	player1X = IMG_LoadTexture(renderer, "Images/player1_X.png");
	player2O = IMG_LoadTexture(renderer, "Images/player2_O.png");
	player2 = IMG_LoadTexture(renderer, "Images/player_2.png");
	player1Marker = IMG_LoadTexture(renderer, "Images/player1_marker.png");
	player2Marker = IMG_LoadTexture(renderer, "Images/player2_marker.png");
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}

//Sets up the texture's rects (Positions, Sizes)
void GameSetupRects() {

	whoWonRect.x = (width / 2) - 300;
	whoWonRect.y = (height / 2) - 200;
	whoWonRect.w = 600;
	whoWonRect.h = 400;

	fadeRect.x = 0;
	fadeRect.y = 0;
	fadeRect.w = width;
	fadeRect.h = height;

	boardRect.x = (width / 2) - 350;
	boardRect.y = 170;
	boardRect.w = 700;
	boardRect.h = 700;

	currentPlayerRect.x = (width / 2) - 50;
	currentPlayerRect.y = 30;
	currentPlayerRect.w = 100;
	currentPlayerRect.h = 30;

	playersMarkerRect.x = boardRect.x + 5;
	playersMarkerRect.y = boardRect.y + 5;
	playersMarkerRect.w = 220;
	playersMarkerRect.h = 220;

	//GRID 3x3
	board3Pos0Rect.x = boardRect.x + 5;
	board3Pos0Rect.y = boardRect.y + 5;
	board3Pos0Rect.w = 220;
	board3Pos0Rect.h = 220;

	board3Pos1Rect.x = boardRect.x + 240;
	board3Pos1Rect.y = boardRect.y + 5;
	board3Pos1Rect.w = 220;
	board3Pos1Rect.h = 220;

	board3Pos2Rect.x = boardRect.x + 475;
	board3Pos2Rect.y = boardRect.y + 5;
	board3Pos2Rect.w = 220;
	board3Pos2Rect.h = 220;

	board3Pos3Rect.x = boardRect.x + 5;
	board3Pos3Rect.y = boardRect.y + 240;
	board3Pos3Rect.w = 220;
	board3Pos3Rect.h = 220;

	board3Pos4Rect.x = boardRect.x + 240;
	board3Pos4Rect.y = boardRect.y + 240;
	board3Pos4Rect.w = 220;
	board3Pos4Rect.h = 220;

	board3Pos5Rect.x = boardRect.x + 475;
	board3Pos5Rect.y = boardRect.y + 240;
	board3Pos5Rect.w = 220;
	board3Pos5Rect.h = 220;

	board3Pos6Rect.x = boardRect.x + 5;
	board3Pos6Rect.y = boardRect.y + 475;
	board3Pos6Rect.w = 220;
	board3Pos6Rect.h = 220;

	board3Pos7Rect.x = boardRect.x + 240;
	board3Pos7Rect.y = boardRect.y + 475;
	board3Pos7Rect.w = 220;
	board3Pos7Rect.h = 220;

	board3Pos8Rect.x = boardRect.x + 475;
	board3Pos8Rect.y = boardRect.y + 475;
	board3Pos8Rect.w = 220;
	board3Pos8Rect.h = 220;

	//GRID 4x4
	board4Pos0Rect.x = boardRect.x + 5;
	board4Pos0Rect.y = boardRect.y + 5;
	board4Pos0Rect.w = 163;
	board4Pos0Rect.h = 163;

	board4Pos1Rect.x = boardRect.x + 180;
	board4Pos1Rect.y = boardRect.y + 5;
	board4Pos1Rect.w = 163;
	board4Pos1Rect.h = 163;

	board4Pos2Rect.x = boardRect.x + 355;
	board4Pos2Rect.y = boardRect.y + 5;
	board4Pos2Rect.w = 163;
	board4Pos2Rect.h = 163;

	board4Pos3Rect.x = boardRect.x + 530;
	board4Pos3Rect.y = boardRect.y + 5;
	board4Pos3Rect.w = 163;
	board4Pos3Rect.h = 163;

	board4Pos4Rect.x = boardRect.x + 5;
	board4Pos4Rect.y = boardRect.y + 180;
	board4Pos4Rect.w = 163;
	board4Pos4Rect.h = 163;

	board4Pos5Rect.x = boardRect.x + 180;
	board4Pos5Rect.y = boardRect.y + 180;
	board4Pos5Rect.w = 163;
	board4Pos5Rect.h = 163;

	board4Pos6Rect.x = boardRect.x + 355;
	board4Pos6Rect.y = boardRect.y + 180;
	board4Pos6Rect.w = 163;
	board4Pos6Rect.h = 163;

	board4Pos7Rect.x = boardRect.x + 530;
	board4Pos7Rect.y = boardRect.y + 180;
	board4Pos7Rect.w = 163;
	board4Pos7Rect.h = 163;

	board4Pos8Rect.x = boardRect.x + 5;
	board4Pos8Rect.y = boardRect.y + 355;
	board4Pos8Rect.w = 163;
	board4Pos8Rect.h = 163;

	board4Pos9Rect.x = boardRect.x + 180;
	board4Pos9Rect.y = boardRect.y + 355;
	board4Pos9Rect.w = 163;
	board4Pos9Rect.h = 163;

	board4Pos10Rect.x = boardRect.x + 355;
	board4Pos10Rect.y = boardRect.y + 355;
	board4Pos10Rect.w = 163;
	board4Pos10Rect.h = 163;

	board4Pos11Rect.x = boardRect.x + 530;
	board4Pos11Rect.y = boardRect.y + 355;
	board4Pos11Rect.w = 163;
	board4Pos11Rect.h = 163;

	board4Pos12Rect.x = boardRect.x + 5;
	board4Pos12Rect.y = boardRect.y + 530;
	board4Pos12Rect.w = 163;
	board4Pos12Rect.h = 163;

	board4Pos13Rect.x = boardRect.x + 180;
	board4Pos13Rect.y = boardRect.y + 530;
	board4Pos13Rect.w = 163;
	board4Pos13Rect.h = 163;

	board4Pos14Rect.x = boardRect.x + 355;
	board4Pos14Rect.y = boardRect.y + 530;
	board4Pos14Rect.w = 163;
	board4Pos14Rect.h = 163;

	board4Pos15Rect.x = boardRect.x + 530;
	board4Pos15Rect.y = boardRect.y + 530;
	board4Pos15Rect.w = 163;
	board4Pos15Rect.h = 163;

	//GRID 5x5
	board5Pos0Rect.x = boardRect.x + 5;
	board5Pos0Rect.y = boardRect.y + 5;
	board5Pos0Rect.w = 130;
	board5Pos0Rect.h = 130;

	board5Pos1Rect.x = boardRect.x + 144;
	board5Pos1Rect.y = boardRect.y + 5;
	board5Pos1Rect.w = 130;
	board5Pos1Rect.h = 130;

	board5Pos2Rect.x = boardRect.x + 284;
	board5Pos2Rect.y = boardRect.y + 5;
	board5Pos2Rect.w = 130;
	board5Pos2Rect.h = 130;

	board5Pos3Rect.x = boardRect.x + 424;
	board5Pos3Rect.y = boardRect.y + 5;
	board5Pos3Rect.w = 130;
	board5Pos3Rect.h = 130;

	board5Pos4Rect.x = boardRect.x + 554;
	board5Pos4Rect.y = boardRect.y + 5;
	board5Pos4Rect.w = 130;
	board5Pos4Rect.h = 130;

	board5Pos5Rect.x = boardRect.x + 5;
	board5Pos5Rect.y = boardRect.y + 144;
	board5Pos5Rect.w = 130;
	board5Pos5Rect.h = 130;

	board5Pos6Rect.x = boardRect.x + 144;
	board5Pos6Rect.y = boardRect.y + 144;
	board5Pos6Rect.w = 130;
	board5Pos6Rect.h = 130;

	board5Pos7Rect.x = boardRect.x + 284;
	board5Pos7Rect.y = boardRect.y + 144;
	board5Pos7Rect.w = 130;
	board5Pos7Rect.h = 130;

	board5Pos8Rect.x = boardRect.x + 424;
	board5Pos8Rect.y = boardRect.y + 144;
	board5Pos8Rect.w = 130;
	board5Pos8Rect.h = 130;

	board5Pos9Rect.x = boardRect.x + 565;
	board5Pos9Rect.y = boardRect.y + 144;
	board5Pos9Rect.w = 130;
	board5Pos9Rect.h = 130;

	board5Pos10Rect.x = boardRect.x + 5;
	board5Pos10Rect.y = boardRect.y + 284;
	board5Pos10Rect.w = 130;
	board5Pos10Rect.h = 130;

	board5Pos11Rect.x = boardRect.x + 144;
	board5Pos11Rect.y = boardRect.y + 284;
	board5Pos11Rect.w = 130;
	board5Pos11Rect.h = 130;

	board5Pos12Rect.x = boardRect.x + 284;
	board5Pos12Rect.y = boardRect.y + 284;
	board5Pos12Rect.w = 130;
	board5Pos12Rect.h = 130;

	board5Pos13Rect.x = boardRect.x + 424;
	board5Pos13Rect.y = boardRect.y + 284;
	board5Pos13Rect.w = 130;
	board5Pos13Rect.h = 130;

	board5Pos14Rect.x = boardRect.x + 565;
	board5Pos14Rect.y = boardRect.y + 284;
	board5Pos14Rect.w = 130;
	board5Pos14Rect.h = 130;

	board5Pos15Rect.x = boardRect.x + 5;
	board5Pos15Rect.y = boardRect.y + 424;
	board5Pos15Rect.w = 130;
	board5Pos15Rect.h = 130;

	board5Pos16Rect.x = boardRect.x + 144;
	board5Pos16Rect.y = boardRect.y + 424;
	board5Pos16Rect.w = 130;
	board5Pos16Rect.h = 130;

	board5Pos17Rect.x = boardRect.x + 284;
	board5Pos17Rect.y = boardRect.y + 424;
	board5Pos17Rect.w = 130;
	board5Pos17Rect.h = 130;

	board5Pos18Rect.x = boardRect.x + 424;
	board5Pos18Rect.y = boardRect.y + 424;
	board5Pos18Rect.w = 130;
	board5Pos18Rect.h = 130;

	board5Pos19Rect.x = boardRect.x + 565;
	board5Pos19Rect.y = boardRect.y + 424;
	board5Pos19Rect.w = 130;
	board5Pos19Rect.h = 130;

	board5Pos20Rect.x = boardRect.x + 5;
	board5Pos20Rect.y = boardRect.y + 565;
	board5Pos20Rect.w = 130;
	board5Pos20Rect.h = 130;

	board5Pos21Rect.x = boardRect.x + 144;
	board5Pos21Rect.y = boardRect.y + 565;
	board5Pos21Rect.w = 130;
	board5Pos21Rect.h = 130;

	board5Pos22Rect.x = boardRect.x + 284;
	board5Pos22Rect.y = boardRect.y + 565;
	board5Pos22Rect.w = 130;
	board5Pos22Rect.h = 130;

	board5Pos23Rect.x = boardRect.x + 424;
	board5Pos23Rect.y = boardRect.y + 565;
	board5Pos23Rect.w = 130;
	board5Pos23Rect.h = 130;

	board5Pos24Rect.x = boardRect.x + 565;
	board5Pos24Rect.y = boardRect.y + 565;
	board5Pos24Rect.w = 130;
	board5Pos24Rect.h = 130;
}

//Main Code Class
Game::Game()
{
	//Calls both methods
	GameTextureSetup();
	GameSetupRects();

	//Creates main event
	SDL_Event* mainEvent = new SDL_Event();

	//Set currentMarker to be player1 (Green Square used to show which tile the player is currently on)
	currentMarker = player1Marker;

	//Creating seed for timer
	srand(time(0));

	//Main loop
	while (mainEvent->type != SDL_QUIT) {

		//Get mouse state and set mouseX and mouseY positions
		SDL_GetMouseState(&mouseX, &mouseY);

		//Opens and reads the options.txt file holding settings (0 = 3x3 Tiles, 1 = 4x4 Tiles, 2 = 5x5 Tiles, 3 = Timer OFF, 4 = Timer ON)
		optionsFile.open("options.txt");
		while (readLoop == false) {

			read = optionsFile.get();
			if (read == '0') {
				cout << "Tiles: 3x3 | ";
				currentPlayer = player1;
				currentMarker = player1Marker;
				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 5;
				gamemode = 0;
			}
			else if (read == '1') {
				cout << "Tiles: 4x4 | ";
				currentPlayer = player1;
				currentMarker = player1Marker;
				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 5;
				gamemode = 1;
			}
			else if (read == '2') {
				cout << "Tiles: 5x5 | ";
				currentPlayer = player1;
				currentMarker = player1Marker;
				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 5;
				gamemode = 2;
			}
			else if (read == '3') {
				cout << "Timer: OFF | Opponent: " << opponent << endl;
				timer = 0;
				readLoop = true;
			}
			else if (read == '4') {
				cout << "Timer: ON | Opponent: " << opponent << endl;
				timer = 1;
				readLoop = true;
			}
		}
		optionsFile.close();

		//Handles all the code for 3x3 Tile game (Whether it's vs Player or vs Pc)
		if (gamemode == 0) {

			//Setting Marker Size for player1 & player2
			playersMarkerRect.w = 220;
			playersMarkerRect.h = 220;

			//Reseting counters for other tile presets (4x4 and 5x5)
			counter4 = 0;
			counter5 = 0;

			//Change marker positions (Green Square to show where the player is hovering over)
			if (currentPosition3[three] == 1) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition3[three] == 2) {

				playersMarkerRect.x = boardRect.x + 240;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition3[three] == 3) {

				playersMarkerRect.x = boardRect.x + 475;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition3[three] == 4) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 240;

			}
			else if (currentPosition3[three] == 5) {

				playersMarkerRect.x = boardRect.x + 240;
				playersMarkerRect.y = boardRect.y + 240;

			}
			else if (currentPosition3[three] == 6) {

				playersMarkerRect.x = boardRect.x + 475;
				playersMarkerRect.y = boardRect.y + 240;

			}
			else if (currentPosition3[three] == 7) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 475;

			}
			else if (currentPosition3[three] == 8) {

				playersMarkerRect.x = boardRect.x + 240;
				playersMarkerRect.y = boardRect.y + 475;

			}
			else if (currentPosition3[three] == 9) {

				playersMarkerRect.x = boardRect.x + 475;
				playersMarkerRect.y = boardRect.y + 475;

			}

			//Timer for PLAYER vs PLAYER games (After 10 seconds of a player being idle, give control to the other player)
			if (timer == 1 && opponent != 1) {

				if (mSec == 60) {
					sec++;
					cout << "Secs: " << sec << endl;
					mSec = 0;
				}
				if (sec == 10) {
					if (playerTurn3 == 0) {
						currentMarker = player2Marker;
						mSec = 0;
						sec = 0;
						playerTurn3 = 1;
					}
					else if (playerTurn3 == 1) {
						currentMarker = player1Marker;
						mSec = 0;
						sec = 0;
						playerTurn3 = 0;
					}
				}
				mSec++;

			}

			//Test if any existing button has been hovered over or clicked on (Using mouse or keyboard input)
			if (SDL_PollEvent(mainEvent) == 1) {

			if (mouseX >= board3Pos0Rect.x && mouseX <= board3Pos0Rect.w + board3Pos0Rect.x && mouseY >= board3Pos0Rect.y && mouseY <= board3Pos0Rect.h + board3Pos0Rect.y) {
				three = 0;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;
									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos1Rect.x && mouseX <= board3Pos1Rect.w + board3Pos1Rect.x && mouseY >= board3Pos1Rect.y && mouseY <= board3Pos1Rect.h + board3Pos1Rect.y) {
				three = 1;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;
									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos2Rect.x && mouseX <= board3Pos2Rect.w + board3Pos2Rect.x && mouseY >= board3Pos2Rect.y && mouseY <= board3Pos2Rect.h + board3Pos2Rect.y) {
				three = 2;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;
									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
				}
			}

			if (mouseX >= board3Pos3Rect.x && mouseX <= board3Pos3Rect.w + board3Pos3Rect.x && mouseY >= board3Pos3Rect.y && mouseY <= board3Pos3Rect.h + board3Pos3Rect.y) {
				three = 3;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;

									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;

									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos4Rect.x && mouseX <= board3Pos4Rect.w + board3Pos4Rect.x && mouseY >= board3Pos4Rect.y && mouseY <= board3Pos4Rect.h + board3Pos4Rect.y) {
				three = 4;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;
									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;

									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos5Rect.x && mouseX <= board3Pos5Rect.w + board3Pos5Rect.x && mouseY >= board3Pos5Rect.y && mouseY <= board3Pos5Rect.h + board3Pos5Rect.y) {
				three = 5;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;

									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;

									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos6Rect.x && mouseX <= board3Pos6Rect.w + board3Pos6Rect.x && mouseY >= board3Pos6Rect.y && mouseY <= board3Pos6Rect.h + board3Pos6Rect.y) {
				three = 6;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;

									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;

									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos7Rect.x && mouseX <= board3Pos7Rect.w + board3Pos7Rect.x && mouseY >= board3Pos7Rect.y && mouseY <= board3Pos7Rect.h + board3Pos7Rect.y) {
				three = 7;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;

									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;

									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			if (mouseX >= board3Pos8Rect.x && mouseX <= board3Pos8Rect.w + board3Pos8Rect.x && mouseY >= board3Pos8Rect.y && mouseY <= board3Pos8Rect.h + board3Pos8Rect.y) {
				three = 8;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn3 == 0) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player1X;
										counter3 += 1;
										currentMarker = player2Marker;
										playerTurn3 = 1;
									}
								}
								else if (playerTurn3 == 1) {

									if (currentPosition3[three] && boardPosition3[three] == NULL) {
										boardPosition3[three] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										playerTurn3 = 0;

									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									aiLoop = false;
									boardPosition3[three] = player1X;
									counter3 += 1;
									currentMarker = NULL;
									randomNum = rand() % 9;
								}
								while (aiLoop == false && counter3 != 9) {
									if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
										boardPosition3[randomNum] = player2O;
										counter3 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 9;
								}

							}

						}
					}
			}

			//Tests for a press after the game has finished (To resume the game when it announces the player that has won)
				if (endGame == 1) {

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							boardPosition3[0] = NULL;
							boardPosition3[1] = NULL;
							boardPosition3[2] = NULL;
							boardPosition3[3] = NULL;
							boardPosition3[4] = NULL;
							boardPosition3[5] = NULL;
							boardPosition3[6] = NULL;
							boardPosition3[7] = NULL;
							boardPosition3[8] = NULL;
							currentPlayer = player1;
							currentMarker = player1Marker;
							playersMarkerRect.x = boardRect.x + 5;
							playersMarkerRect.y = boardRect.y + 5;
							gameEnd = NULL;
							whoWon = NULL;
							three = 0;
							four = 0;
							five = 0;
							counter3 = 0;
							playerTurn3 = 0;
							endGame = 0;

						}

					}

				}

				if (mainEvent->type == SDL_KEYDOWN) {

					if (mainEvent->key.keysym.sym == SDLK_w) {

						if (three == 0 || three == 1 || three == 2) {
						}
						else {
							three -= 3;
						}

					}

					if (mainEvent->key.keysym.sym == SDLK_s) {

						if (three == 6 || three == 7 || three == 8) {
						}
						else {
							three += 3;
						}

					}

					if (mainEvent->key.keysym.sym == SDLK_a) {

						if (three == 0 || three == 3 || three == 6) {
						}
						else {

							three -= 1;

						}

					}

					if (mainEvent->key.keysym.sym == SDLK_d) {

						if (three == 2 || three == 5 || three == 8) {
						}
						else {

							three += 1;

						}

					}


					//SET CURRENT TILE WITH PLAYERS SYMBOL (X or O)

					if (mainEvent->key.keysym.sym == SDLK_RETURN) {

						if (opponent == 0) {

							mSec = 0;
							sec = 0;

							if (playerTurn3 == 0) {

								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									boardPosition3[three] = player1X;
									currentMarker = player2Marker;
									counter3 += 1;
									playerTurn3 = 1;
								}
							}
							else if (playerTurn3 == 1) {

								if (currentPosition3[three] && boardPosition3[three] == NULL) {
									boardPosition3[three] = player2O;
									counter3 += 1;
									currentMarker = player1Marker;
									playerTurn3 = 0;
								}

							}

						}

						else if (opponent == 1 && endGame != 1) {
							if (currentPosition3[three] && boardPosition3[three] == NULL) {
								aiLoop = false;
								boardPosition3[three] = player1X;
								counter3 += 1;
								currentMarker = NULL;
								randomNum = rand() % 9;
							}
							while (aiLoop == false && counter3 != 9) {
								if (currentPosition3[randomNum] && boardPosition3[randomNum] == NULL) {
									boardPosition3[randomNum] = player2O;
									counter3 += 1;
									currentMarker = player1Marker;
									aiLoop = true;
								}
								randomNum = rand() % 9;
							}

						}
					}

					if (mainEvent->key.keysym.sym == SDLK_RETURN && endGame == 1) {

						boardPosition3[0] = NULL;
						boardPosition3[1] = NULL;
						boardPosition3[2] = NULL;
						boardPosition3[3] = NULL;
						boardPosition3[4] = NULL;
						boardPosition3[5] = NULL;
						boardPosition3[6] = NULL;
						boardPosition3[7] = NULL;
						boardPosition3[8] = NULL;
						currentPlayer = player1;
						currentMarker = player1Marker;
						playersMarkerRect.x = boardRect.x + 5;
						playersMarkerRect.y = boardRect.y + 5;
						gameEnd = NULL;
						whoWon = NULL;
						three = 0;
						four = 0;
						five = 0;
						counter3 = 0;
						playerTurn3 = 0;
						endGame = 0;


					}

				}

			}

			//Change current player's texture to player1 or player2
			if (playerTurn3 == 0) {
				currentPlayer = player1;

			}
			else if (playerTurn3 == 1) {
				currentPlayer = player2;

			}

			//Check for a player1 win
			if (boardPosition3[0] == player1X && boardPosition3[1] == player1X && boardPosition3[2] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[3] == player1X && boardPosition3[4] == player1X && boardPosition3[5] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[6] == player1X && boardPosition3[7] == player1X && boardPosition3[8] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[0] == player1X && boardPosition3[3] == player1X && boardPosition3[6] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[1] == player1X && boardPosition3[4] == player1X && boardPosition3[7] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[2] == player1X && boardPosition3[5] == player1X && boardPosition3[8] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[0] == player1X && boardPosition3[4] == player1X && boardPosition3[8] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition3[2] == player1X && boardPosition3[4] == player1X && boardPosition3[6] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}

			//Check for a player2 win
			if (boardPosition3[0] == player2O && boardPosition3[1] == player2O && boardPosition3[2] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[3] == player2O && boardPosition3[4] == player2O && boardPosition3[5] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[6] == player2O && boardPosition3[7] == player2O && boardPosition3[8] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[0] == player2O && boardPosition3[3] == player2O && boardPosition3[6] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[1] == player2O && boardPosition3[4] == player2O && boardPosition3[7] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[2] == player2O && boardPosition3[5] == player2O && boardPosition3[8] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[0] == player2O && boardPosition3[4] == player2O && boardPosition3[8] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition3[2] == player2O && boardPosition3[4] == player2O && boardPosition3[6] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}

			//Check for a draw if no player wins
			if (counter3 == 9 && endGame == 0) {
				gameEnd = fadeWin;
				whoWon = draw;
				endGame = 1;
			}

		}

		/*  Handles all the code for 4x4 Tile game (Whether it's vs Player or vs Pc) 
			***See if statement "gamemode == 0" for a detailed description of what the code does (All code structures are the same just different variables and more code based on size of grid)***
		*/
		else if (gamemode == 1) {
			playersMarkerRect.w = 163;
			playersMarkerRect.h = 163;
			counter3 = 0;
			counter5 = 0;

			if (currentPosition4[four] == 1) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition4[four] == 2) {

				playersMarkerRect.x = boardRect.x + 180;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition4[four] == 3) {

				playersMarkerRect.x = boardRect.x + 355;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition4[four] == 4) {

				playersMarkerRect.x = boardRect.x + 530;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition4[four] == 5) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 180;

			}
			else if (currentPosition4[four] == 6) {

				playersMarkerRect.x = boardRect.x + 180;
				playersMarkerRect.y = boardRect.y + 180;

			}
			else if (currentPosition4[four] == 7) {

				playersMarkerRect.x = boardRect.x + 355;
				playersMarkerRect.y = boardRect.y + 180;

			}
			else if (currentPosition4[four] == 8) {

				playersMarkerRect.x = boardRect.x + 530;
				playersMarkerRect.y = boardRect.y + 180;

			}
			else if (currentPosition4[four] == 9) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 355;

			}
			else if (currentPosition4[four] == 10) {

				playersMarkerRect.x = boardRect.x + 180;
				playersMarkerRect.y = boardRect.y + 355;

			}
			else if (currentPosition4[four] == 11) {

				playersMarkerRect.x = boardRect.x + 355;
				playersMarkerRect.y = boardRect.y + 355;

			}
			else if (currentPosition4[four] == 12) {

				playersMarkerRect.x = boardRect.x + 530;
				playersMarkerRect.y = boardRect.y + 355;

			}
			else if (currentPosition4[four] == 13) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 530;

			}
			else if (currentPosition4[four] == 14) {

				playersMarkerRect.x = boardRect.x + 180;
				playersMarkerRect.y = boardRect.y + 530;

			}
			else if (currentPosition4[four] == 15) {

				playersMarkerRect.x = boardRect.x + 355;
				playersMarkerRect.y = boardRect.y + 530;

			}
			else if (currentPosition4[four] == 16) {

				playersMarkerRect.x = boardRect.x + 530;
				playersMarkerRect.y = boardRect.y + 530;

			}

			if (timer == 1 && opponent != 1) {

				if (mSec == 60) {
					sec++;
					cout << "Secs: " << sec << endl;
					mSec = 0;
				}
				if (sec == 10) {
					if (playerTurn4 == 0) {
						currentMarker = player2Marker;
						mSec = 0;
						sec = 0;
						playerTurn4 = 1;
					}
					else if (playerTurn4 == 1) {
						currentMarker = player1Marker;
						mSec = 0;
						sec = 0;
						playerTurn4 = 0;
					}
				}
				mSec++;

			}

			//MOVE MARKER ON BOARD
			if (SDL_PollEvent(mainEvent) == 1) {

				if (mouseX >= board4Pos0Rect.x && mouseX <= board4Pos0Rect.w + board4Pos0Rect.x && mouseY >= board4Pos0Rect.y && mouseY <= board4Pos0Rect.h + board4Pos0Rect.y) {
					four = 0;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos1Rect.x && mouseX <= board4Pos1Rect.w + board4Pos1Rect.x && mouseY >= board4Pos1Rect.y && mouseY <= board4Pos1Rect.h + board4Pos1Rect.y) {
					four = 1;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos2Rect.x && mouseX <= board4Pos2Rect.w + board4Pos2Rect.x && mouseY >= board4Pos2Rect.y && mouseY <= board4Pos2Rect.h + board4Pos2Rect.y) {
					four = 2;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos3Rect.x && mouseX <= board4Pos3Rect.w + board4Pos3Rect.x && mouseY >= board4Pos3Rect.y && mouseY <= board4Pos3Rect.h + board4Pos3Rect.y) {
					four = 3;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos4Rect.x && mouseX <= board4Pos4Rect.w + board4Pos4Rect.x && mouseY >= board4Pos4Rect.y && mouseY <= board4Pos4Rect.h + board4Pos4Rect.y) {
					four = 4;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos5Rect.x && mouseX <= board4Pos5Rect.w + board4Pos5Rect.x && mouseY >= board4Pos5Rect.y && mouseY <= board4Pos5Rect.h + board4Pos5Rect.y) {
					four = 5;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos6Rect.x && mouseX <= board4Pos6Rect.w + board4Pos6Rect.x && mouseY >= board4Pos6Rect.y && mouseY <= board4Pos6Rect.h + board4Pos6Rect.y) {
					four = 6;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos7Rect.x && mouseX <= board4Pos7Rect.w + board4Pos7Rect.x && mouseY >= board4Pos7Rect.y && mouseY <= board4Pos7Rect.h + board4Pos7Rect.y) {
					four = 7;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos8Rect.x && mouseX <= board4Pos8Rect.w + board4Pos8Rect.x && mouseY >= board4Pos8Rect.y && mouseY <= board4Pos8Rect.h + board4Pos8Rect.y) {
					four = 8;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos9Rect.x && mouseX <= board4Pos9Rect.w + board4Pos9Rect.x && mouseY >= board4Pos9Rect.y && mouseY <= board4Pos9Rect.h + board4Pos9Rect.y) {
					four = 9;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos10Rect.x && mouseX <= board4Pos10Rect.w + board4Pos10Rect.x && mouseY >= board4Pos10Rect.y && mouseY <= board4Pos10Rect.h + board4Pos10Rect.y) {
					four = 10;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos11Rect.x && mouseX <= board4Pos11Rect.w + board4Pos11Rect.x && mouseY >= board4Pos11Rect.y && mouseY <= board4Pos11Rect.h + board4Pos11Rect.y) {
					four = 11;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos12Rect.x && mouseX <= board4Pos12Rect.w + board4Pos12Rect.x && mouseY >= board4Pos12Rect.y && mouseY <= board4Pos12Rect.h + board4Pos12Rect.y) {
					four = 12;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos13Rect.x && mouseX <= board4Pos13Rect.w + board4Pos13Rect.x && mouseY >= board4Pos13Rect.y && mouseY <= board4Pos13Rect.h + board4Pos13Rect.y) {
					four = 13;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos14Rect.x && mouseX <= board4Pos14Rect.w + board4Pos14Rect.x && mouseY >= board4Pos14Rect.y && mouseY <= board4Pos14Rect.h + board4Pos14Rect.y) {
					four = 14;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (mouseX >= board4Pos15Rect.x && mouseX <= board4Pos15Rect.w + board4Pos15Rect.x && mouseY >= board4Pos15Rect.y && mouseY <= board4Pos15Rect.h + board4Pos15Rect.y) {
					four = 15;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn4 == 0) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player1X;
										playerTurn4 = 1;
										counter4 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn4 == 1) {

									if (currentPosition4[four] && boardPosition4[four] == NULL) {
										boardPosition4[four] = player2O;
										playerTurn4 = 0;
										counter4 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									aiLoop = false;
									boardPosition4[four] = player1X;
									counter4 += 1;
									currentMarker = NULL;
									randomNum = rand() % 16;
								}
								while (aiLoop == false && counter4 != 16) {
									if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
										boardPosition4[randomNum] = player2O;
										counter4 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									randomNum = rand() % 16;
								}

							}

						}
					}
				}

				if (endGame == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							boardPosition4[0] = NULL;
							boardPosition4[1] = NULL;
							boardPosition4[2] = NULL;
							boardPosition4[3] = NULL;
							boardPosition4[4] = NULL;
							boardPosition4[5] = NULL;
							boardPosition4[6] = NULL;
							boardPosition4[7] = NULL;
							boardPosition4[8] = NULL;
							boardPosition4[9] = NULL;
							boardPosition4[10] = NULL;
							boardPosition4[11] = NULL;
							boardPosition4[12] = NULL;
							boardPosition4[13] = NULL;
							boardPosition4[14] = NULL;
							boardPosition4[15] = NULL;
							currentPlayer = player1;
							currentMarker = player1Marker;
							playersMarkerRect.x = boardRect.x + 5;
							playersMarkerRect.y = boardRect.y + 5;
							gameEnd = NULL;
							whoWon = NULL;
							three = 0;
							four = 0;
							five = 0;
							counter4 = 0;
							playerTurn4 = 0;
							endGame = 0;

						}

					}

				}

				if (mainEvent->type == SDL_KEYDOWN) {

			if (mainEvent->key.keysym.sym == SDLK_w) {

				if (four == 0 || four == 1 || four == 2 || four == 3) {
				}
				else {
					four -= 4;
				}

			}

			if (mainEvent->key.keysym.sym == SDLK_s) {

				if (four == 12 || four == 13 || four == 14 || four == 15) {
				}
				else {
					four += 4;
				}

			}

			if (mainEvent->key.keysym.sym == SDLK_a) {

				if (four == 0 || four == 4 || four == 8 || four == 12) {
				}
				else {

					four -= 1;

				}

			}

			if (mainEvent->key.keysym.sym == SDLK_d) {

				if (four == 3 || four == 7 || four == 11 || four == 15) {
				}
				else {

					four += 1;

				}

			}

			//SET CURRENT TILE WITH PLAYERS SYMBOL (X or O)

					if (mainEvent->key.keysym.sym == SDLK_RETURN) {

						if (opponent == 0) {

							mSec = 0;
							sec = 0;

							if (playerTurn4 == 0) {

								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									boardPosition4[four] = player1X;
									playerTurn4 = 1;
									counter4 += 1;
									currentMarker = player2Marker;
								}
							}
							else if (playerTurn4 == 1) {

								if (currentPosition4[four] && boardPosition4[four] == NULL) {
									boardPosition4[four] = player2O;
									playerTurn4 = 0;
									counter4 += 1;
									currentMarker = player1Marker;
								}

							}

						}

						else if (opponent == 1) {
							if (currentPosition4[four] && boardPosition4[four] == NULL) {
								aiLoop = false;
								boardPosition4[four] = player1X;
								counter4 += 1;
								currentMarker = NULL;
								randomNum = rand() % 16;
							}
							while (aiLoop == false && counter4 != 16) {
								if (currentPosition4[randomNum] && boardPosition4[randomNum] == NULL) {
									boardPosition4[randomNum] = player2O;
									counter4 += 1;
									currentMarker = player1Marker;
									aiLoop = true;
								}
								randomNum = rand() % 16;
							}

						}
					}

					if (mainEvent->key.keysym.sym == SDLK_RETURN && endGame == 1) {

						boardPosition4[0] = NULL;
						boardPosition4[1] = NULL;
						boardPosition4[2] = NULL;
						boardPosition4[3] = NULL;
						boardPosition4[4] = NULL;
						boardPosition4[5] = NULL;
						boardPosition4[6] = NULL;
						boardPosition4[7] = NULL;
						boardPosition4[8] = NULL;
						boardPosition4[9] = NULL;
						boardPosition4[10] = NULL;
						boardPosition4[11] = NULL;
						boardPosition4[12] = NULL;
						boardPosition4[13] = NULL;
						boardPosition4[14] = NULL;
						boardPosition4[15] = NULL;
						currentPlayer = player1;
						currentMarker = player1Marker;
						playersMarkerRect.x = boardRect.x + 5;
						playersMarkerRect.y = boardRect.y + 5;
						gameEnd = NULL;
						whoWon = NULL;
						three = 0;
						four = 0;
						five = 0;
						counter4 = 0;
						playerTurn4 = 0;
						endGame = 0;


					}
				}
			}
			if (playerTurn4 == 0) {
				currentPlayer = player1; //Change current player's texture to player1

			}
			else if (playerTurn4 == 1) {
				currentPlayer = player2; //Change current player's texture to player2

			}


			if (boardPosition4[0] == player1X && boardPosition4[1] == player1X && boardPosition4[2] == player1X && boardPosition4[3] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[4] == player1X && boardPosition4[5] == player1X && boardPosition4[6] == player1X && boardPosition4[7] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[8] == player1X && boardPosition4[9] == player1X && boardPosition4[10] == player1X && boardPosition4[11] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[12] == player1X && boardPosition4[13] == player1X && boardPosition4[14] == player1X && boardPosition4[15] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[0] == player1X && boardPosition4[4] == player1X && boardPosition4[8] == player1X && boardPosition4[12] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[1] == player1X && boardPosition4[5] == player1X && boardPosition4[9] == player1X && boardPosition4[13] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[2] == player1X && boardPosition4[6] == player1X && boardPosition4[10] == player1X && boardPosition4[14] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[3] == player1X && boardPosition4[7] == player1X && boardPosition4[11] == player1X && boardPosition4[15] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[0] == player1X && boardPosition4[5] == player1X && boardPosition4[10] == player1X && boardPosition4[15] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition4[3] == player1X && boardPosition4[6] == player1X && boardPosition4[9] == player1X && boardPosition4[12] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}

			if (boardPosition4[0] == player2O && boardPosition4[1] == player2O && boardPosition4[2] == player2O && boardPosition4[3] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[4] == player2O && boardPosition4[5] == player2O && boardPosition4[6] == player2O && boardPosition4[7] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[8] == player2O && boardPosition4[9] == player2O && boardPosition4[10] == player2O && boardPosition4[11] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[12] == player2O && boardPosition4[13] == player2O && boardPosition4[14] == player2O && boardPosition4[15] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[0] == player2O && boardPosition4[4] == player2O && boardPosition4[8] == player2O && boardPosition4[12] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[1] == player2O && boardPosition4[5] == player2O && boardPosition4[9] == player2O && boardPosition4[13] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[2] == player2O && boardPosition4[6] == player2O && boardPosition4[10] == player2O && boardPosition4[14] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[3] == player2O && boardPosition4[7] == player2O && boardPosition4[11] == player2O && boardPosition4[15] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[0] == player2O && boardPosition4[5] == player2O && boardPosition4[10] == player2O && boardPosition4[15] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition4[3] == player2O && boardPosition4[6] == player2O && boardPosition4[9] == player2O && boardPosition4[12] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}


			if (counter4 == 16 && endGame == 0) {
				gameEnd = fadeWin;
				whoWon = draw;
				endGame = 1;
			}
		}

		/*  Handles all the code for 4x4 Tile game (Whether it's vs Player or vs Pc)
		***See if statement "gamemode == 0" for a detailed description of what the code does (All code structures are the same just different variables and more code based on size of grid)***
		*/
		else if (gamemode == 2) {
			playersMarkerRect.w = 130;
			playersMarkerRect.h = 130;
			counter3 = 0;
			counter4 = 0;

			if (currentPosition5[five] == 1) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition5[five] == 2) {

				playersMarkerRect.x = boardRect.x + 144;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition5[five] == 3) {

				playersMarkerRect.x = boardRect.x + 284;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition5[five] == 4) {

				playersMarkerRect.x = boardRect.x + 424;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition5[five] == 5) {

				playersMarkerRect.x = boardRect.x + 565;
				playersMarkerRect.y = boardRect.y + 5;

			}
			else if (currentPosition5[five] == 6) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 144;

			}
			else if (currentPosition5[five] == 7) {

				playersMarkerRect.x = boardRect.x + 144;
				playersMarkerRect.y = boardRect.y + 144;

			}
			else if (currentPosition5[five] == 8) {

				playersMarkerRect.x = boardRect.x + 282;
				playersMarkerRect.y = boardRect.y + 144;

			}
			else if (currentPosition5[five] == 9) {

				playersMarkerRect.x = boardRect.x + 424;
				playersMarkerRect.y = boardRect.y + 144;

			}
			else if (currentPosition5[five] == 10) {

				playersMarkerRect.x = boardRect.x + 565;
				playersMarkerRect.y = boardRect.y + 144;

			}
			else if (currentPosition5[five] == 11) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 284;

			}
			else if (currentPosition5[five] == 12) {

				playersMarkerRect.x = boardRect.x + 144;
				playersMarkerRect.y = boardRect.y + 284;

			}
			else if (currentPosition5[five] == 13) {

				playersMarkerRect.x = boardRect.x + 284;
				playersMarkerRect.y = boardRect.y + 284;

			}
			else if (currentPosition5[five] == 14) {

				playersMarkerRect.x = boardRect.x + 424;
				playersMarkerRect.y = boardRect.y + 284;

			}
			else if (currentPosition5[five] == 15) {

				playersMarkerRect.x = boardRect.x + 565;
				playersMarkerRect.y = boardRect.y + 284;

			}
			else if (currentPosition5[five] == 16) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 424;

			}
			else if (currentPosition5[five] == 17) {

				playersMarkerRect.x = boardRect.x + 144;
				playersMarkerRect.y = boardRect.y + 424;

			}
			else if (currentPosition5[five] == 18) {

				playersMarkerRect.x = boardRect.x + 284;
				playersMarkerRect.y = boardRect.y + 424;

			}
			else if (currentPosition5[five] == 19) {

				playersMarkerRect.x = boardRect.x + 424;
				playersMarkerRect.y = boardRect.y + 424;

			}
			else if (currentPosition5[five] == 20) {

				playersMarkerRect.x = boardRect.x + 565;
				playersMarkerRect.y = boardRect.y + 424;

			}
			else if (currentPosition5[five] == 21) {

				playersMarkerRect.x = boardRect.x + 5;
				playersMarkerRect.y = boardRect.y + 565;

			}
			else if (currentPosition5[five] == 22) {

				playersMarkerRect.x = boardRect.x + 144;
				playersMarkerRect.y = boardRect.y + 565;

			}
			else if (currentPosition5[five] == 23) {

				playersMarkerRect.x = boardRect.x + 284;
				playersMarkerRect.y = boardRect.y + 565;

			}
			else if (currentPosition5[five] == 24) {

				playersMarkerRect.x = boardRect.x + 424;
				playersMarkerRect.y = boardRect.y + 565;

			}
			else if (currentPosition5[five] == 25) {

				playersMarkerRect.x = boardRect.x + 565;
				playersMarkerRect.y = boardRect.y + 565;

			}

			if (timer == 1 && opponent != 1) {

				if (mSec == 60) {
					sec++;
					cout << "Secs: " << sec << endl;
					mSec = 0;
				}
				if (sec == 10) {
					if (playerTurn5 == 0) {
						currentMarker = player2Marker;
						mSec = 0;
						sec = 0;
						playerTurn5 = 1;
					}
					else if (playerTurn5 == 1) {
						currentMarker = player1Marker;
						mSec = 0;
						sec = 0;
						playerTurn5 = 0;
					}
				}
				mSec++;

			}

			//MOVE MARKER ON BOARD
			if (SDL_PollEvent(mainEvent) == 1) {

				if (mouseX >= board5Pos0Rect.x && mouseX <= board5Pos0Rect.w + board5Pos0Rect.x && mouseY >= board5Pos0Rect.y && mouseY <= board5Pos0Rect.h + board5Pos0Rect.y) {
					five = 0;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos1Rect.x && mouseX <= board5Pos1Rect.w + board5Pos1Rect.x && mouseY >= board5Pos1Rect.y && mouseY <= board5Pos1Rect.h + board5Pos1Rect.y) {
					five = 1;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos2Rect.x && mouseX <= board5Pos2Rect.w + board5Pos2Rect.x && mouseY >= board5Pos2Rect.y && mouseY <= board5Pos2Rect.h + board5Pos2Rect.y) {
					five = 2;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos3Rect.x && mouseX <= board5Pos3Rect.w + board5Pos3Rect.x && mouseY >= board5Pos3Rect.y && mouseY <= board5Pos3Rect.h + board5Pos3Rect.y) {
					five = 3;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos4Rect.x && mouseX <= board5Pos4Rect.w + board5Pos4Rect.x && mouseY >= board5Pos4Rect.y && mouseY <= board5Pos4Rect.h + board5Pos4Rect.y) {
					five = 4;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos5Rect.x && mouseX <= board5Pos5Rect.w + board5Pos5Rect.x && mouseY >= board5Pos5Rect.y && mouseY <= board5Pos5Rect.h + board5Pos5Rect.y) {
					five = 5;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos6Rect.x && mouseX <= board5Pos6Rect.w + board5Pos6Rect.x && mouseY >= board5Pos6Rect.y && mouseY <= board5Pos6Rect.h + board5Pos6Rect.y) {
					five = 6;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos7Rect.x && mouseX <= board5Pos7Rect.w + board5Pos7Rect.x && mouseY >= board5Pos7Rect.y && mouseY <= board5Pos7Rect.h + board5Pos7Rect.y) {
					five = 7;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos8Rect.x && mouseX <= board5Pos8Rect.w + board5Pos8Rect.x && mouseY >= board5Pos8Rect.y && mouseY <= board5Pos8Rect.h + board5Pos8Rect.y) {
					five = 8;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos9Rect.x && mouseX <= board5Pos9Rect.w + board5Pos9Rect.x && mouseY >= board5Pos9Rect.y && mouseY <= board5Pos9Rect.h + board5Pos9Rect.y) {
					five = 9;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos10Rect.x && mouseX <= board5Pos10Rect.w + board5Pos10Rect.x && mouseY >= board5Pos10Rect.y && mouseY <= board5Pos10Rect.h + board5Pos10Rect.y) {
					five = 10;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos11Rect.x && mouseX <= board5Pos11Rect.w + board5Pos11Rect.x && mouseY >= board5Pos11Rect.y && mouseY <= board5Pos11Rect.h + board5Pos11Rect.y) {
					five = 11;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos12Rect.x && mouseX <= board5Pos12Rect.w + board5Pos12Rect.x && mouseY >= board5Pos12Rect.y && mouseY <= board5Pos12Rect.h + board5Pos12Rect.y) {
					five = 12;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos13Rect.x && mouseX <= board5Pos13Rect.w + board5Pos13Rect.x && mouseY >= board5Pos13Rect.y && mouseY <= board5Pos13Rect.h + board5Pos13Rect.y) {
					five = 13;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos14Rect.x && mouseX <= board5Pos14Rect.w + board5Pos14Rect.x && mouseY >= board5Pos14Rect.y && mouseY <= board5Pos14Rect.h + board5Pos14Rect.y) {
					five = 14;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos15Rect.x && mouseX <= board5Pos15Rect.w + board5Pos15Rect.x && mouseY >= board5Pos15Rect.y && mouseY <= board5Pos15Rect.h + board5Pos15Rect.y) {
					five = 15;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos16Rect.x && mouseX <= board5Pos16Rect.w + board5Pos16Rect.x && mouseY >= board5Pos16Rect.y && mouseY <= board5Pos16Rect.h + board5Pos16Rect.y) {
					five = 16;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos17Rect.x && mouseX <= board5Pos17Rect.w + board5Pos17Rect.x && mouseY >= board5Pos17Rect.y && mouseY <= board5Pos17Rect.h + board5Pos17Rect.y) {
					five = 17;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos18Rect.x && mouseX <= board5Pos18Rect.w + board5Pos18Rect.x && mouseY >= board5Pos18Rect.y && mouseY <= board5Pos18Rect.h + board5Pos18Rect.y) {
					five = 18;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos19Rect.x && mouseX <= board5Pos19Rect.w + board5Pos19Rect.x && mouseY >= board5Pos19Rect.y && mouseY <= board5Pos19Rect.h + board5Pos19Rect.y) {
					five = 19;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos20Rect.x && mouseX <= board5Pos20Rect.w + board5Pos20Rect.x && mouseY >= board5Pos20Rect.y && mouseY <= board5Pos20Rect.h + board5Pos20Rect.y) {
					five = 20;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos21Rect.x && mouseX <= board5Pos21Rect.w + board5Pos21Rect.x && mouseY >= board5Pos21Rect.y && mouseY <= board5Pos21Rect.h + board5Pos21Rect.y) {
					five = 21;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos22Rect.x && mouseX <= board5Pos22Rect.w + board5Pos22Rect.x && mouseY >= board5Pos22Rect.y && mouseY <= board5Pos22Rect.h + board5Pos22Rect.y) {
					five = 22;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos23Rect.x && mouseX <= board5Pos23Rect.w + board5Pos23Rect.x && mouseY >= board5Pos23Rect.y && mouseY <= board5Pos23Rect.h + board5Pos23Rect.y) {
					five = 23;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (mouseX >= board5Pos24Rect.x && mouseX <= board5Pos24Rect.w + board5Pos24Rect.x && mouseY >= board5Pos24Rect.y && mouseY <= board5Pos24Rect.h + board5Pos24Rect.y) {
					five = 24;

					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							if (opponent == 0) {

								mSec = 0;
								sec = 0;

								if (playerTurn5 == 0) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player1X;
										playerTurn5 = 1;
										counter5 += 1;
										currentMarker = player2Marker;
									}
								}
								else if (playerTurn5 == 1) {

									if (currentPosition5[five] && boardPosition5[five] == NULL) {
										boardPosition5[five] = player2O;
										playerTurn5 = 0;
										counter5 += 1;
										currentMarker = player1Marker;
									}

								}

							}
							else if (opponent == 1 && endGame != 1) {
								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									aiLoop = false;
									boardPosition5[five] = player1X;
									counter5 += 1;
									currentMarker = NULL;
									randomNum = rand() % 25;
								}
								while (aiLoop == false && counter5 != 25) {
									if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
										boardPosition5[randomNum] = player2O;
										counter5 += 1;
										currentMarker = player1Marker;
										aiLoop = true;
									}
									//else if(boardPosition3[randomNum] != NULL) {
									//	aiLoop = true;
									//}
									randomNum = rand() % 25;
								}

							}

						}
					}
				}

				if (endGame == 1) {
					if (mainEvent->type == SDL_MOUSEBUTTONDOWN) {
						if (mainEvent->button.button == SDL_BUTTON_LEFT) {

							boardPosition5[0] = NULL;
							boardPosition5[1] = NULL;
							boardPosition5[2] = NULL;
							boardPosition5[3] = NULL;
							boardPosition5[4] = NULL;
							boardPosition5[5] = NULL;
							boardPosition5[6] = NULL;
							boardPosition5[7] = NULL;
							boardPosition5[8] = NULL;
							boardPosition5[9] = NULL;
							boardPosition5[10] = NULL;
							boardPosition5[11] = NULL;
							boardPosition5[12] = NULL;
							boardPosition5[13] = NULL;
							boardPosition5[14] = NULL;
							boardPosition5[15] = NULL;
							boardPosition5[16] = NULL;
							boardPosition5[17] = NULL;
							boardPosition5[18] = NULL;
							boardPosition5[19] = NULL;
							boardPosition5[20] = NULL;
							boardPosition5[21] = NULL;
							boardPosition5[22] = NULL;
							boardPosition5[23] = NULL;
							boardPosition5[24] = NULL;
							currentPlayer = player1;
							currentMarker = player1Marker;
							playersMarkerRect.x = boardRect.x + 5;
							playersMarkerRect.y = boardRect.y + 5;
							gameEnd = NULL;
							whoWon = NULL;
							three = 0;
							four = 0;
							five = 0;
							counter5 = 0;
							playerTurn5 = 0;
							endGame = 0;

						}

					}

				}

				if (mainEvent->type == SDL_KEYDOWN) {

			if (mainEvent->key.keysym.sym == SDLK_w) {

				if (five == 0 || five == 1 || five == 2 || five == 3 || five == 4) {
				}
				else {
					five -= 5;
				}

			}

			if (mainEvent->key.keysym.sym == SDLK_s) {

				if (five == 20 || five == 21 || five == 22 || five == 23 || five == 24) {
				}
				else {
					five += 5;
				}

			}

			if (mainEvent->key.keysym.sym == SDLK_a) {

				if (five == 0 || five == 5 || five == 10 || five == 15 || five == 20) {
				}
				else {

					five -= 1;

				}

			}

			if (mainEvent->key.keysym.sym == SDLK_d) {

				if (five == 4 || five == 9 || five == 14 || five == 19 || five == 24) {
				}
				else {

					five += 1;

				}

			}

			//SET CURRENT TILE WITH PLAYERS SYMBOL (X or O)

					if (mainEvent->key.keysym.sym == SDLK_RETURN) {

						if (opponent == 0) {

							mSec = 0;
							sec = 0;

							if (playerTurn5 == 0) {

								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									boardPosition5[five] = player1X;
									playerTurn5 = 1;
									counter5 += 1;
									currentMarker = player2Marker;
								}
							}
							else if (playerTurn5 == 1) {

								if (currentPosition5[five] && boardPosition5[five] == NULL) {
									boardPosition5[five] = player2O;
									playerTurn5 = 0;
									counter5 += 1;
									currentMarker = player1Marker;
								}

							}

						}

						else if (opponent == 1 && endGame != 1) {
							if (currentPosition5[five] && boardPosition5[five] == NULL) {
								aiLoop = false;
								boardPosition5[five] = player1X;
								counter5 += 1;
								currentMarker = NULL;
								randomNum = rand() % 25;
							}
							while (aiLoop == false && counter5 != 25) {
								if (currentPosition5[randomNum] && boardPosition5[randomNum] == NULL) {
									boardPosition5[randomNum] = player2O;
									counter5 += 1;
									currentMarker = player1Marker;
									aiLoop = true;
								}
								//else if(boardPosition3[randomNum] != NULL) {
								//	aiLoop = true;
								//}
								randomNum = rand() % 25;
							}

						}
					}

					if (mainEvent->key.keysym.sym == SDLK_RETURN && endGame == 1) {

						boardPosition5[0] = NULL;
						boardPosition5[1] = NULL;
						boardPosition5[2] = NULL;
						boardPosition5[3] = NULL;
						boardPosition5[4] = NULL;
						boardPosition5[5] = NULL;
						boardPosition5[6] = NULL;
						boardPosition5[7] = NULL;
						boardPosition5[8] = NULL;
						boardPosition5[9] = NULL;
						boardPosition5[10] = NULL;
						boardPosition5[11] = NULL;
						boardPosition5[12] = NULL;
						boardPosition5[13] = NULL;
						boardPosition5[14] = NULL;
						boardPosition5[15] = NULL;
						boardPosition5[16] = NULL;
						boardPosition5[17] = NULL;
						boardPosition5[18] = NULL;
						boardPosition5[19] = NULL;
						boardPosition5[20] = NULL;
						boardPosition5[21] = NULL;
						boardPosition5[22] = NULL;
						boardPosition5[23] = NULL;
						boardPosition5[24] = NULL;
						currentPlayer = player1;
						currentMarker = player1Marker;
						playersMarkerRect.x = boardRect.x + 5;
						playersMarkerRect.y = boardRect.y + 5;
						gameEnd = NULL;
						whoWon = NULL;
						three = 0;
						four = 0;
						five = 0;
						counter5 = 0;
						playerTurn5 = 0;
						endGame = 0;


					}

				}
			}
			if (playerTurn5 == 0) {
				currentPlayer = player1; //Change current player's texture to player1

			}
			else if (playerTurn5 == 1) {
				currentPlayer = player2; //Change current player's texture to player2

			}


			if (boardPosition5[0] == player1X && boardPosition5[1] == player1X && boardPosition5[2] == player1X && boardPosition5[3] == player1X && boardPosition5[4] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[5] == player1X && boardPosition5[6] == player1X && boardPosition5[7] == player1X && boardPosition5[8] == player1X && boardPosition5[9] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[10] == player1X && boardPosition5[11] == player1X && boardPosition5[12] == player1X && boardPosition5[13] == player1X && boardPosition5[14] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[15] == player1X && boardPosition5[16] == player1X && boardPosition5[17] == player1X && boardPosition5[18] == player1X && boardPosition5[19] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[20] == player1X && boardPosition5[21] == player1X && boardPosition5[22] == player1X && boardPosition5[23] == player1X && boardPosition5[24] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[0] == player1X && boardPosition5[5] == player1X && boardPosition5[10] == player1X && boardPosition5[15] == player1X && boardPosition5[20] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[1] == player1X && boardPosition5[6] == player1X && boardPosition5[11] == player1X && boardPosition5[16] == player1X && boardPosition5[21] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[2] == player1X && boardPosition5[7] == player1X && boardPosition5[12] == player1X && boardPosition5[17] == player1X && boardPosition5[22] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[3] == player1X && boardPosition5[8] == player1X && boardPosition5[13] == player1X && boardPosition5[18] == player1X && boardPosition5[23] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[4] == player1X && boardPosition5[9] == player1X && boardPosition5[14] == player1X && boardPosition5[19] == player1X && boardPosition5[24] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[0] == player1X && boardPosition5[6] == player1X && boardPosition5[12] == player1X && boardPosition5[18] == player1X && boardPosition5[24] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			else if (boardPosition5[4] == player1X && boardPosition5[8] == player1X && boardPosition5[12] == player1X && boardPosition5[16] == player1X && boardPosition5[20] == player1X) {
				gameEnd = fadeWin;
				whoWon = player1Wins;
				endGame = 1;
			}
			//
			if (boardPosition5[0] == player2O && boardPosition5[1] == player2O && boardPosition5[2] == player2O && boardPosition5[3] == player2O && boardPosition5[4] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[5] == player2O && boardPosition5[6] == player2O && boardPosition5[7] == player2O && boardPosition5[8] == player2O && boardPosition5[9] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[10] == player2O && boardPosition5[11] == player2O && boardPosition5[12] == player2O && boardPosition5[13] == player2O && boardPosition5[14] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[15] == player2O && boardPosition5[16] == player2O && boardPosition5[17] == player2O && boardPosition5[18] == player2O && boardPosition5[19] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[20] == player2O && boardPosition5[21] == player2O && boardPosition5[22] == player2O && boardPosition5[23] == player2O && boardPosition5[24] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[0] == player2O && boardPosition5[5] == player2O && boardPosition5[10] == player2O && boardPosition5[15] == player2O && boardPosition5[20] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[1] == player2O && boardPosition5[6] == player2O && boardPosition5[11] == player2O && boardPosition5[16] == player2O && boardPosition5[21] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[2] == player2O && boardPosition5[7] == player2O && boardPosition5[12] == player2O && boardPosition5[17] == player2O && boardPosition5[22] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[3] == player2O && boardPosition5[8] == player2O && boardPosition5[13] == player2O && boardPosition5[18] == player2O && boardPosition5[23] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[4] == player2O && boardPosition5[9] == player2O && boardPosition5[14] == player2O && boardPosition5[19] == player2O && boardPosition5[24] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[0] == player2O && boardPosition5[6] == player2O && boardPosition5[12] == player2O && boardPosition5[18] == player2O && boardPosition5[24] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}
			else if (boardPosition5[4] == player2O && boardPosition5[8] == player2O && boardPosition5[12] == player2O && boardPosition5[16] == player2O && boardPosition5[20] == player2O) {
				gameEnd = fadeWin;
				whoWon = player2Wins;
				endGame = 1;
			}

			if (counter5 == 25 && endGame == 0) {
				gameEnd = fadeWin;
				whoWon = draw;
				endGame = 1;
			}
		}

		//Main rendering system to render textures onto the screen
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(renderer);
		
		//Handles the rendering for 3x3 tiles gamemode
		if (gamemode == 0) {
			SDL_RenderCopy(renderer, board3x3, NULL, &boardRect);
			SDL_RenderCopy(renderer, boardPosition3[0], NULL, &board3Pos0Rect);
			SDL_RenderCopy(renderer, boardPosition3[1], NULL, &board3Pos1Rect);
			SDL_RenderCopy(renderer, boardPosition3[2], NULL, &board3Pos2Rect);
			SDL_RenderCopy(renderer, boardPosition3[3], NULL, &board3Pos3Rect);
			SDL_RenderCopy(renderer, boardPosition3[4], NULL, &board3Pos4Rect);
			SDL_RenderCopy(renderer, boardPosition3[5], NULL, &board3Pos5Rect);
			SDL_RenderCopy(renderer, boardPosition3[6], NULL, &board3Pos6Rect);
			SDL_RenderCopy(renderer, boardPosition3[7], NULL, &board3Pos7Rect);
			SDL_RenderCopy(renderer, boardPosition3[8], NULL, &board3Pos8Rect);
		}

		//Handles the rendering for 4x4 tiles gamemode
		else if (gamemode == 1) {
			SDL_RenderCopy(renderer, board4x4, NULL, &boardRect);
			SDL_RenderCopy(renderer, boardPosition4[0], NULL, &board4Pos0Rect);
			SDL_RenderCopy(renderer, boardPosition4[1], NULL, &board4Pos1Rect);
			SDL_RenderCopy(renderer, boardPosition4[2], NULL, &board4Pos2Rect);
			SDL_RenderCopy(renderer, boardPosition4[3], NULL, &board4Pos3Rect);
			SDL_RenderCopy(renderer, boardPosition4[4], NULL, &board4Pos4Rect);
			SDL_RenderCopy(renderer, boardPosition4[5], NULL, &board4Pos5Rect);
			SDL_RenderCopy(renderer, boardPosition4[6], NULL, &board4Pos6Rect);
			SDL_RenderCopy(renderer, boardPosition4[7], NULL, &board4Pos7Rect);
			SDL_RenderCopy(renderer, boardPosition4[8], NULL, &board4Pos8Rect);
			SDL_RenderCopy(renderer, boardPosition4[9], NULL, &board4Pos9Rect);
			SDL_RenderCopy(renderer, boardPosition4[10], NULL, &board4Pos10Rect);
			SDL_RenderCopy(renderer, boardPosition4[11], NULL, &board4Pos11Rect);
			SDL_RenderCopy(renderer, boardPosition4[12], NULL, &board4Pos12Rect);
			SDL_RenderCopy(renderer, boardPosition4[13], NULL, &board4Pos13Rect);
			SDL_RenderCopy(renderer, boardPosition4[14], NULL, &board4Pos14Rect);
			SDL_RenderCopy(renderer, boardPosition4[15], NULL, &board4Pos15Rect);
		}

		//Handles the rendering for 5x5 tiles gamemode
		else if (gamemode == 2) {
			SDL_RenderCopy(renderer, board5x5, NULL, &boardRect);
			SDL_RenderCopy(renderer, boardPosition5[0], NULL, &board5Pos0Rect);
			SDL_RenderCopy(renderer, boardPosition5[1], NULL, &board5Pos1Rect);
			SDL_RenderCopy(renderer, boardPosition5[2], NULL, &board5Pos2Rect);
			SDL_RenderCopy(renderer, boardPosition5[3], NULL, &board5Pos3Rect);
			SDL_RenderCopy(renderer, boardPosition5[4], NULL, &board5Pos4Rect);
			SDL_RenderCopy(renderer, boardPosition5[5], NULL, &board5Pos5Rect);
			SDL_RenderCopy(renderer, boardPosition5[6], NULL, &board5Pos6Rect);
			SDL_RenderCopy(renderer, boardPosition5[7], NULL, &board5Pos7Rect);
			SDL_RenderCopy(renderer, boardPosition5[8], NULL, &board5Pos8Rect);
			SDL_RenderCopy(renderer, boardPosition5[9], NULL, &board5Pos9Rect);
			SDL_RenderCopy(renderer, boardPosition5[10], NULL, &board5Pos10Rect);
			SDL_RenderCopy(renderer, boardPosition5[11], NULL, &board5Pos11Rect);
			SDL_RenderCopy(renderer, boardPosition5[12], NULL, &board5Pos12Rect);
			SDL_RenderCopy(renderer, boardPosition5[13], NULL, &board5Pos13Rect);
			SDL_RenderCopy(renderer, boardPosition5[14], NULL, &board5Pos14Rect);
			SDL_RenderCopy(renderer, boardPosition5[15], NULL, &board5Pos15Rect);
			SDL_RenderCopy(renderer, boardPosition5[16], NULL, &board5Pos16Rect);
			SDL_RenderCopy(renderer, boardPosition5[17], NULL, &board5Pos17Rect);
			SDL_RenderCopy(renderer, boardPosition5[18], NULL, &board5Pos18Rect);
			SDL_RenderCopy(renderer, boardPosition5[19], NULL, &board5Pos19Rect);
			SDL_RenderCopy(renderer, boardPosition5[20], NULL, &board5Pos20Rect);
			SDL_RenderCopy(renderer, boardPosition5[21], NULL, &board5Pos21Rect);
			SDL_RenderCopy(renderer, boardPosition5[22], NULL, &board5Pos22Rect);
			SDL_RenderCopy(renderer, boardPosition5[23], NULL, &board5Pos23Rect);
			SDL_RenderCopy(renderer, boardPosition5[24], NULL, &board5Pos24Rect);
		}

		SDL_RenderCopy(renderer, currentMarker, NULL, &playersMarkerRect);
		SDL_RenderCopy(renderer, currentPlayer, NULL, &currentPlayerRect);
		SDL_RenderCopy(renderer, gameEnd, NULL, &fadeRect);
		SDL_RenderCopy(renderer, whoWon, NULL, &whoWonRect);

		SDL_RenderPresent(renderer);
		//rendering stops here

	}

}


Game::~Game()
{
}
