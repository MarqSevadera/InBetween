#pragma once
#include "SFML\Graphics.hpp"
#include<iostream>
#include <vector>
#include <queue>
class Deck
{
public:
	
	enum CardSuit{Flower , Spade , Heart , Diamond};
	enum CardRank{Ace , Two , Three , Four , Five , Six , Seven , Eight , Nine , Ten , Jack , Queen , King};


	struct Suit {
		bool isUsed = false;
		sf::Texture img;
	};


	struct Card {
		CardSuit currentSuit;
		CardRank	rank;
		Suit suit[4]; //hearts , spade , flower , diamonds
		int suitUsed = 0;
		bool visited;
		struct Card* leftChild;
		struct Card* rightChild;
	
	};


	struct Card* rootNode;
	struct Card* currentNode;

	struct Card remainingCards[13];

	void InitializeCards();
	void Deck::ResetDeck();

	Deck::Card* Deck::DrawRandomCard();

	bool Deck::isInBetween(Card* firstCard, Card*secondCard, Card* lastCard);

	const int TOTAL_SUIT = 4;
	const int TOTAL_RANK = 13;
	const int TOTAL_CARDS = 52;


	Deck::Card* CardPointer[3];

	//index of the CardPointer in the array
	const int FIRST_CARD = 0;
	const int SECOND_CARD = 1;
	const int LAST_CARD = 2;



private:


	const double CARD_WIDTH = 140.5;
	const double CARD_HEIGHT = 190;

	std::vector<CardRank> remainingRank;

	

	Deck::CardSuit Deck::RandomSuit();
	Deck::CardRank Deck::RandomRank();
	bool Deck::alreadyInTree(Deck::Card* node);
	void Deck::InsertToTree(Deck::Card* card);


};

