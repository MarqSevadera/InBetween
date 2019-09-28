#include "stdafx.h"
#include "Martha.h"

int  Martha::SearchTree(Deck& deck, Deck::Card* firstCard, Deck::Card* secondCard) {

	int difference = static_cast<Deck::CardRank>(abs(firstCard->rank - secondCard->rank)) - 1; //ex: your card is A and K ; 13 - 1 - 1 = 11 (11 cards in the middle: 2 ,3 ,4,5,6,7,8,9,10,11,12)

	if (difference  <= 0 ) return 0; //no chance of winning

	int totalWinningCard = difference * deck.TOTAL_SUIT; //multiply it by 4(total suit)  that's your total winning card
	int usedWinningCards = 0;



	

	deck.currentNode = deck.rootNode; //set the current node to the rootNode because we will start searching at the top


	Deck::Card* currentCardPtr = deck.currentNode;

	cardQ.push(currentCardPtr);	 //enqueue the root node 

	currentCardPtr->visited = true; //set this to visited



	while (!cardQ.empty()) {

		

		currentCardPtr = cardQ.front();

		if (currentCardPtr == nullptr) return 0;


		cardQ.pop(); //pop the currentNode

	
		if (currentCardPtr != nullptr && deck.isInBetween(firstCard, secondCard, currentCardPtr)) {
			usedWinningCards += currentCardPtr->suitUsed;  //add the total suitUsed in the current Card Rank to the useWinningCards
			std::cout << "Checking if " << currentCardPtr->rank + 1 << " is in between " << firstCard->rank + 1 << " and " << secondCard->rank + 1 << std::endl;

		}



		//now check if the leftChild of the current node is not empty and not visited yet
		if (currentCardPtr->leftChild != nullptr && currentCardPtr->leftChild->visited != true)
		{
			cardQ.push(currentCardPtr->leftChild);  //enqueue it if not empty
			currentCardPtr->leftChild->visited = true; //mark as visited
	
		}
			
		
		//the same as the righChild
		if (currentCardPtr->rightChild != nullptr && currentCardPtr->rightChild->visited != true) {
			cardQ.push(currentCardPtr->rightChild);
			currentCardPtr->rightChild->visited = true; //mark as visited
		}


	

	}


	ResetVisitedNodes(deck.rootNode);

	return totalWinningCard - usedWinningCards;



}


void Martha::ResetVisitedNodes(Deck::Card* root) {

	if (root != NULL) {

		root->visited = false;
		ResetVisitedNodes(root->leftChild);
		ResetVisitedNodes(root->rightChild);
	}


}