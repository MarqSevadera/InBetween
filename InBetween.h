#pragma once
#include "SFML\Graphics.hpp"
#include "Deck.h"
#include "Martha.h"
#include <list>
#include<iostream>
#include <string>
class InBetween
{
public:
	
	enum Winner{Undecided , Player , CPU , Draw};

	Winner Play(sf::RenderWindow& window , bool playerTurn);

	enum Press{Nothing , Up , Down , PlaceBet};

	struct Button {
		sf::Rect <int> rect;
		Press type;
	};




private:

	bool playerTurn;
	bool cardGiven = false;
	int playerCoin = 50;
	int aiCoin = 50;
	int totalPot = 0;
	int minBet = 5;
	int playerBet = minBet;
	int aiBet = minBet;
	int cardLeft = 52;
	int usedCards = 0;



	//images
	sf::Texture bgImg; //the background image of the maingame
	sf::Texture downImg,upImg, placeBetImg, upGlow, downGlow, placeBetGlow; //up , down , and placeBet buttons img
	sf::Texture marthaImg, youImg, disabledImg, freshImg;	// prompt images
	sf::Texture cardBackImg; // card img back side

	//sprites
	sf::Sprite bgSprite;
	sf::Sprite upSprite, downSprite, placeBetSprite;
	sf::Sprite marthaSprite, youSprite, disabledSprite, freshSprite;


	sf::Sprite cardSprite[3]; // we neeed 3 for left , middle and right card place
	const int L_CARD_POSX = 262; // the position where we will place the first card (left side)
	const int R_CARD_POSX = 627; // the position where we will place the second card (right side)
	const int M_CARD_POSX = 450; // the position where we will place the last card ( middle card )
	
	


	//texts & font
	sf::Text playerCoinTxt , aiCoinTxt, playerBetTxt, aiBetTxt, potTxt , cardsLeftTxt , usedCardsTxt;
	sf::Font font;

	//event
	sf::Event event;

	//Buttons
	std::list<Button> buttons;


	//Deck
	Deck deck;

	//Initializations
	void InBetween::LoadImages();
	void InBetween::InitializeSprites();
	void InBetween::InitalizeButtons();
	void InBetween::InitializeTexts();
	void InBetween::InitalizeBackCardPosition();

	//Drawing of Sprites to the screen
	void InBetween::DrawSprites(sf::RenderWindow& window);



	//Funtions called when the pot is empty or less than minimum bet
	void InBetween::PayMinBet();


	//Functions called when it is the players turn
	bool InBetween::GetPlayerBet(sf::RenderWindow& window, sf::Event event);
	InBetween::Press InBetween::HandleClicks(int x, int y);
	void InBetween::PerformAction(InBetween::Press);
	

	
	//functions responsible for animations
	void InBetween::ApplyPressAnimation(InBetween::Press button);
	void InBetween::UpdateTextValue(sf::Text &text, int newValue);
	void InBetween::FlipCard(int card);
	void InBetween::MoveCard(sf::RenderWindow& window , int cardIndex , int desiredPosition);
	void InBetween::GiveLastCard(sf::RenderWindow& window);
	
	
	//functions responsible for calculations
	void InBetween::IncreaseCoins();
	void InBetween::DecreaseCoins();
	void InBetween::ComputeAIBet();

	//Martha
	Martha martha;
	bool InBetween::GetAIBet(sf::RenderWindow& window);


	//Check if theres a winner already
	InBetween::Winner InBetween::GetWinner();

};

