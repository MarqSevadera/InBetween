#pragma once
#include "Deck.h"

#include <math.h>
#include <queue>
class Martha
{

public:

	int Martha::SearchTree(Deck& deck, Deck::Card* firstCard, Deck::Card* secondCard);
private:

	std::queue<Deck::Card*> cardQ;

	void Martha::ResetVisitedNodes(Deck::Card* root);
};



