#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SplashScreen.h"
#include "Menu.h"
#include "RockPaperScissor.h"
#include "InBetween.h"


class Game
{
public:
	static void Start();
private:
	static bool isExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void PlayRPS();
	static void PlayInBetween();
	
	enum GameState{ Uninitialized , ShowingSplash , ShowingMenu ,PlayingRPS , Paused, PlayingInBetween , Exiting};
	enum Turn {Undecided, AI , Player};

	//global variables
	static GameState gameState;
	static Turn turn;
	static sf::RenderWindow mainWindow;
};

