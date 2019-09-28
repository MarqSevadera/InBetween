#include "stdafx.h"
#include "Deck.h"

void Deck::InitializeCards() {

	for (int rankCounter = Ace; rankCounter <= King; rankCounter++) {

		remainingCards[rankCounter].rank = static_cast<CardRank>(rankCounter);

		for (int suitCounter = Flower; suitCounter <= Diamond; suitCounter++) {
			Suit* cardSuit = &remainingCards[rankCounter].suit[suitCounter];
			cardSuit -> isUsed = false;
			cardSuit -> img.loadFromFile("images/cards-spritesheet.png", sf::IntRect(rankCounter*CARD_WIDTH, suitCounter*CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT));	
		}

		remainingRank.push_back(static_cast<CardRank>(rankCounter));	//push current rank to remainingRank vector

	}


	


}



void Deck::ResetDeck() {


	Card* card;
	remainingRank.clear();

	for (int rankCounter = Ace; rankCounter <= King ; rankCounter++) {

		card = &remainingCards[rankCounter];
		card->rank = static_cast<CardRank>(rankCounter);

		for (int suitCounter = Flower; suitCounter <= Diamond; suitCounter++) {

			Suit*cardSuit = &remainingCards[rankCounter].suit[suitCounter];

			cardSuit->isUsed = false;
			
		}

		card->suitUsed = 0;

		remainingRank.push_back(static_cast<CardRank>(rankCounter));
	}



}



Deck::Card* Deck::DrawRandomCard() {
		
	CardSuit suit;
	CardRank rank;
	Deck::Card* cardDrawn;



	
	rank = RandomRank();
	printf("rank = %d \n", rank + 1);
	

	// random ng suit , pag yung suit na narandom di pa gamit break na eto na yung gagamiting suit
	while (true) {

		suit = RandomSuit();
		if (!remainingCards[rank].suit[suit].isUsed)
				break;

	}

	cardDrawn = &remainingCards[rank];			//lagay naten sya sa pointer var para di ganun kahaba yung code

	cardDrawn -> suit[suit].isUsed = true;	 // syempre kailangan nateng i mark as used yung naradom nateng suit para di na sya marandom ulit mamaya
	cardDrawn->suitUsed++;					 //dagdagan yan syempre
	cardDrawn -> currentSuit = suit;		// kailangan naten iset ung currentSuit naten sa suit na narandom para makuha naten yung desired img

	InsertToTree(cardDrawn);		//syempre lagay mo na yung card na narandom sa ating tree

	return cardDrawn; //kailangan nating ibalik yung pointer, para maaccess yung ateng mga fields kasi kung hindi pointer e copy lang yan di yan yung mismong variable

}


Deck::CardSuit Deck::RandomSuit() {

	return static_cast<CardSuit>(rand() % TOTAL_SUIT);

}


Deck::CardRank Deck::RandomRank() {

	for (int i = 0; i < remainingRank.size(); i++) {
		if (remainingCards[remainingRank[i]].suitUsed == 4) {
			remainingRank.erase(remainingRank.begin() + i);
			printf("erased! rank %d \n", remainingCards[i].rank + 1);
		}
			
	}


	return static_cast<CardRank> (remainingRank[rand() %  remainingRank.size()]);
	
}


void Deck::InsertToTree(Card* card)	 {

	
	struct Card* current;
	struct Card* parent;

	if (alreadyInTree(card))return;


	// yung mga node , lalagay naten sa binary tree 

	if (rootNode == NULL) { //pag null yung root node , gawin mong root node yung card na iinsert mo ngayon
		rootNode = card;
		rootNode->leftChild = NULL;
		rootNode->rightChild = NULL;
		
	}
	else {	

		
		current = rootNode;	
		parent = current;

		

		while (true) {

			if (card->rank < current->rank) { 
				parent = current;
				current = current->leftChild;
			
				if (current == NULL) {
					parent->leftChild = card;
					return;
				}
			}


			else {
				parent = current;
				current = current->rightChild;
				if (current == NULL) {
					parent->rightChild = card;
					return;
				}
				

			}

		}

	}

}


bool Deck::alreadyInTree(Card* card) {

	if (rootNode == NULL) return false;

	Card* current = rootNode;

	while (true) {
		
		if (current->rank == card->rank) { return true; } // is in the tree


		if (card->rank < current->rank) current = current->leftChild;
	
		else  current = current->rightChild;


		if (current == NULL) return false; //not yet in the tree

	}


}

bool Deck::isInBetween(Card* firstCard, Card*secondCard, Card* lastCard) {


	if (firstCard->rank > secondCard->rank) {

		if (lastCard->rank > secondCard->rank && lastCard->rank < firstCard->rank)
			return true;
		else
			return false;
	}
	else {

		if (lastCard->rank > firstCard->rank && lastCard->rank < secondCard->rank)
			return true;
		else
			return false;
	}


}




