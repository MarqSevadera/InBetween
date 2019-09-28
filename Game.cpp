#include "stdafx.h"
#include "Game.h"

int main() {

	Game::Start();
	return 0;

}



bool Game::isExiting() {

	if (gameState == Game::Exiting)
		return true;
	else
		return false;

}

void Game::Start() {	

	if (gameState != Uninitialized)
		return;

	mainWindow.create(sf::VideoMode(1024, 768, 32), "In Between",sf::Style::Close);
	gameState = ShowingSplash;

	while (!isExiting()) {
		GameLoop();
	}

	mainWindow.close();
}

void Game::GameLoop() {
	sf::Event event;
	bool firstRun = true; // this will allow the loop below to run immidiately at the first time even if theres no event occured yet
	while (mainWindow.pollEvent(event) || firstRun) {
		firstRun = false;
		switch (gameState) {

		case Game::ShowingMenu:		 ShowMenu();
			break;
		case Game::ShowingSplash:	 ShowSplashScreen();
			break;
		case Game::PlayingRPS:		 PlayRPS();
			break;
		case Game::PlayingInBetween: PlayInBetween();
			break;

		}
	}
}

void Game::ShowSplashScreen() {

	SplashScreen splashScreen;

	splashScreen.Show(mainWindow);

	gameState = Game::ShowingMenu; 


}

void Game::ShowMenu() {
	Menu menu;
	Menu::MenuResult result = menu.Show(mainWindow);
	switch (result) {
	case Menu::Exit:
		gameState = Exiting;
		break;
	case Menu::Play:
		gameState = PlayingRPS;
		break;
	}
}

void Game::PlayRPS() {

	RockPaperScissor rps;
	RockPaperScissor::RPSWinner winner = rps.PlayRPS(mainWindow);

	if (winner == RockPaperScissor::RPSWinner::Quit)
		gameState = Exiting;
	else if (winner == RockPaperScissor::RPSWinner::Draw) {
		gameState = PlayingRPS;
	}
	else if (winner == RockPaperScissor::RPSWinner::Player) {
		gameState = PlayingInBetween;
		turn = Player;
	}
	else if (winner == RockPaperScissor::RPSWinner::CPU) {
		gameState = PlayingInBetween;
		turn = AI;
	}
	
}

void Game::PlayInBetween() {

	InBetween game;
	InBetween::Winner winner;

	if (turn == Game::Player)
		winner = game.Play(mainWindow,true);
	else
		winner = game.Play(mainWindow, false);


	if (winner == Player) {
		std::cout << "You win!" << std::endl;
		gameState = Exiting;
	}
	else if (winner == AI) {
		std::cout << "You lose!" << std::endl;
		gameState = Exiting;
	}
	else {
		std::cout << "Draw!" << std::endl;
		gameState = Exiting;
	}
}





Game::Turn Game::turn = Undecided;
Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
