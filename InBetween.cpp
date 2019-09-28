#include "stdafx.h"
#include "InBetween.h"



InBetween::Winner InBetween::Play(sf::RenderWindow& window , bool turn){
	
	InBetween::playerTurn = turn;

	LoadImages();
	InitializeSprites();  
	InitalizeBackCardPosition();
	InitalizeButtons();
	InitializeTexts(); 
	deck.InitializeCards();
		
	window.clear();
	window.draw(bgSprite);
	window.draw(disabledSprite);
	window.display();



	Winner winner;

	while (true) {


		DrawSprites(window);//Draw lang ng draw kada loop



		if (!cardGiven) {
			MoveCard(window, deck.FIRST_CARD, L_CARD_POSX);
			MoveCard(window, deck.SECOND_CARD, R_CARD_POSX);
			FlipCard(deck.FIRST_CARD);
			FlipCard(deck.SECOND_CARD);
			cardGiven = !cardGiven;

		}


		if (playerTurn) {

			if (GetPlayerBet(window, event) == true)
				playerTurn = !playerTurn;


		}
		else {
	
			if (GetAIBet(window)) {
				DrawSprites(window);
				sf::sleep(sf::seconds(2));
				playerTurn = !playerTurn;
			}

		}
		
			
		winner = GetWinner();
		if (winner != Undecided) return winner;

	

	}
	
}




InBetween::Winner InBetween::GetWinner() {
	if (aiCoin < minBet && playerCoin < minBet) return Draw;
	else if (aiCoin < minBet && playerCoin >= minBet) return Player;
	else if (playerCoin < minBet && aiCoin >= minBet) return CPU;
	else return Undecided;
}

bool InBetween::GetPlayerBet(sf::RenderWindow& window, sf::Event event) {

	InBetween::Press button = Nothing;

	while (window.pollEvent(event)) {

		if (event.type == sf::Event::MouseButtonPressed) {

			button = HandleClicks(event.mouseButton.x, event.mouseButton.y);
			ApplyPressAnimation(button);
			PerformAction(button);
			DrawSprites(window);
			return false;

		}

		else if (event.type == sf::Event::MouseButtonReleased) {

			button = HandleClicks(event.mouseButton.x, event.mouseButton.y);
			InitializeSprites();

			if (button == PlaceBet) {
				GiveLastCard(window);
				DrawSprites(window);
				sf::sleep(sf::seconds(2));
				InitalizeBackCardPosition();
				cardGiven = false; //set ulit naten to sa false kasi ai na yung mag tuturn

				return true;
			}

		}
		
	}


	return false;
}

bool InBetween::GetAIBet(sf::RenderWindow& window) {

	ComputeAIBet();
	DrawSprites(window);
	sf::sleep(sf::seconds(1));

	GiveLastCard(window);
	DrawSprites(window);
	sf::sleep(sf::seconds(2));
	InitalizeBackCardPosition();
	cardGiven = false;
	return true;


}


void InBetween::ComputeAIBet() {

	int winningHand = martha.SearchTree(deck, deck.CardPointer[deck.FIRST_CARD], deck.CardPointer[deck.SECOND_CARD]);

	
	double probability = (float)winningHand / cardLeft;

	if (probability == 0.0) {
		aiBet = minBet;
		UpdateTextValue(aiBetTxt, aiBet);

		return;
	}


	if (probability > .5) {

		if (aiCoin >= totalPot) aiBet = totalPot;
		else aiBet = aiCoin;
	
	}
	else {

		if (aiCoin >= probability*totalPot) {
			aiBet = probability*totalPot;
			if (aiBet < minBet) aiBet = minBet;
		}
		else	aiBet = aiCoin;
	
	}

	UpdateTextValue(aiBetTxt, aiBet);
	return;

	

}

void InBetween::GiveLastCard(sf::RenderWindow& window) {

	MoveCard(window , deck.LAST_CARD , M_CARD_POSX); // place the last card at the center

	FlipCard(deck.LAST_CARD);

	DrawSprites(window);

	sf::seconds(2);


		if (deck.isInBetween(deck.CardPointer[deck.FIRST_CARD], deck.CardPointer[deck.SECOND_CARD], deck.CardPointer[deck.LAST_CARD]))
			IncreaseCoins();
		else
			DecreaseCoins();



}

void InBetween::InitalizeButtons() {

	Button up;
	up.type = Up;
	up.rect.top = 583;
	up.rect.height = 661;
	up.rect.left = 718;
	up.rect.width = 795;


	Button down;
	down.type = Down;
	down.rect.top = 678;
	down.rect.height = 761;
	down.rect.left = 713;
	down.rect.width = 797;



	Button placeBet;
	placeBet.type = PlaceBet;
	placeBet.rect.top = 585;
	placeBet.rect.height = 744;
	placeBet.rect.left = 852;
	placeBet.rect.width = 1000;

	buttons.push_back(up);
	buttons.push_back(down);
	buttons.push_back(placeBet);

}

void InBetween::LoadImages() {

	//without glow
	bgImg.loadFromFile("images/main-game.png");
	upImg.loadFromFile("images/up.png");
	downImg.loadFromFile("images/down.png");
	placeBetImg.loadFromFile("images/bet.png");
	marthaImg.loadFromFile("images/martha.png");
	youImg.loadFromFile("images/you.png");
	disabledImg.loadFromFile("images/disabled.png");
	freshImg.loadFromFile("images/fresh.png");
	cardBackImg.loadFromFile("images/back-card.png");

	//with glow
	upGlow.loadFromFile("images/up-glow.png");
	downGlow.loadFromFile("images/down-glow.png");
	placeBetGlow.loadFromFile("images/bet-glow.png");
	

}

void InBetween::InitializeSprites() {
	//bg
	bgSprite.setTexture(bgImg);

	//buttons
	placeBetSprite.setTexture(placeBetImg);
	upSprite.setTexture(upImg);
	downSprite.setTexture(downImg);

	//prompts
	marthaSprite.setTexture(marthaImg);
	youSprite.setTexture(youImg);
	disabledSprite.setTexture(disabledImg);
	freshSprite.setTexture(freshImg);

}

void InBetween::InitalizeBackCardPosition() {

	//cards
	for (int i = 0; i < 3; i++) {
		cardSprite[i].setTexture(cardBackImg);
		cardSprite[i].setPosition(sf::Vector2f(44, 297));
	}

}

void InBetween::InitializeTexts() {

	font.loadFromFile("fonts/jersey.ttf");

	aiCoinTxt.setString(std::to_string(aiCoin));
	aiCoinTxt.setFont(font);
	aiCoinTxt.setCharacterSize(70);
	aiCoinTxt.setPosition(sf::Vector2f(885, 265));

	playerCoinTxt.setString(std::to_string(playerCoin));
	playerCoinTxt.setFont(font);
	playerCoinTxt.setCharacterSize(70);	
	playerCoinTxt.setPosition(sf::Vector2f(885, 445));


	playerBetTxt.setString(std::to_string(playerBet));
	playerBetTxt.setFont(font);
	playerBetTxt.setCharacterSize(70);
	playerBetTxt.setPosition(sf::Vector2f(250, 635));


	aiBetTxt.setString(std::to_string(aiBet));
	aiBetTxt.setFont(font);
	aiBetTxt.setCharacterSize(30);
	aiBetTxt.setPosition(sf::Vector2f(400, 145));

	potTxt.setString(std::to_string(totalPot));
	potTxt.setFont(font);
	potTxt.setCharacterSize(30);
	potTxt.setPosition(sf::Vector2f(950, 140));



	cardsLeftTxt.setString(std::to_string(cardLeft));
	cardsLeftTxt.setFont(font);
	cardsLeftTxt.setCharacterSize(30);
	cardsLeftTxt.setPosition(sf::Vector2f(91,508));

	usedCardsTxt.setString(std::to_string(usedCards));
	usedCardsTxt.setFont(font);
	usedCardsTxt.setCharacterSize(30);
	usedCardsTxt.setPosition(sf::Vector2f(950, 50));


}

void InBetween::UpdateTextValue(sf::Text &text, int newValue) {
	text.setString(std::to_string(newValue));
}

void InBetween::DrawSprites(sf::RenderWindow& window) {



	window.clear();
	window.draw(bgSprite);
	window.draw(cardSprite[0]);
	window.draw(cardSprite[1]);
	window.draw(cardSprite[2]);
	window.draw(playerCoinTxt);
	window.draw(aiCoinTxt);
	window.draw(potTxt);
	window.draw(cardsLeftTxt);
	window.draw(usedCardsTxt);
	
	if (totalPot < 5) {


		window.draw(freshSprite);

		sf::sleep(sf::seconds(1));
		window.display();
		PayMinBet();
		sf::sleep(sf::seconds(1));
		UpdateTextValue(playerCoinTxt, playerCoin);
		UpdateTextValue(aiCoinTxt, aiCoin);
		UpdateTextValue(potTxt, totalPot);

	}


	if (playerTurn) {

		window.draw(upSprite);
		window.draw(downSprite);
		window.draw(placeBetSprite);
		window.draw(youSprite);
		window.draw(playerBetTxt);

		
	}
	else {
	
		window.draw(marthaSprite);
		window.draw(disabledSprite);
		window.draw(aiBetTxt);
		
	}

	
	window.display();

	
}

InBetween::Press InBetween::HandleClicks(int x , int y) {

	std::list<Button>::iterator i;

	for (i = buttons.begin(); i != buttons.end(); i++) {
		sf::Rect<int> buttonRect = i->rect;
		if (buttonRect.height > y && buttonRect.top < y && buttonRect.width > x && buttonRect.left < x)
			return i->type;
	}

	return Nothing;

}

void InBetween::ApplyPressAnimation(InBetween::Press button) {

	if (button == Up) {
		upSprite.setTexture(upGlow);
	}
	else if (button == Down) {
		downSprite.setTexture(downGlow);
	}
	else if (button == PlaceBet) {
		placeBetSprite.setTexture(placeBetGlow);
	
	}

}

void InBetween::PayMinBet() {

	playerCoin -= minBet;
	aiCoin -= minBet;
	totalPot = minBet * 2 + totalPot;

}

void InBetween::PerformAction(InBetween::Press button) {

	if (button == Up && playerBet < totalPot && playerBet <= playerCoin) {
		playerBet++;
	}

	
	else if (button == Down && playerBet > minBet) {
		playerBet--;

	
	}

	UpdateTextValue(playerBetTxt, playerBet);

}

void InBetween::IncreaseCoins() {

	if (playerTurn) {

		playerCoin += playerBet;
		totalPot -= playerBet;
		playerBet = minBet;
		UpdateTextValue(playerCoinTxt, playerCoin);
		UpdateTextValue(potTxt, totalPot);
		UpdateTextValue(playerBetTxt, playerBet);

		
	}
	else {
		aiCoin += aiBet;
		totalPot -= aiBet;
		aiBet = minBet;
		UpdateTextValue(aiCoinTxt, aiCoin);
		UpdateTextValue(potTxt, totalPot);
		UpdateTextValue(aiBetTxt, aiBet);
	}
}

void InBetween::DecreaseCoins() {
	if (playerTurn) {

		playerCoin -= playerBet;
		totalPot += playerBet;
		playerBet = minBet;
		UpdateTextValue(playerCoinTxt, playerCoin);
		UpdateTextValue(potTxt, totalPot);
		UpdateTextValue(playerBetTxt, playerBet);


	}
	else {
		aiCoin -= aiBet;
		totalPot += aiBet;
		aiBet = minBet;
		UpdateTextValue(aiCoinTxt, aiCoin);
		UpdateTextValue(potTxt, totalPot);
		UpdateTextValue(aiBetTxt, aiBet);
	}
}

void InBetween::FlipCard(int cardIndex) {

	deck.CardPointer[cardIndex] = deck.DrawRandomCard();
	cardSprite[cardIndex].setTexture(deck.CardPointer[cardIndex]->suit[deck.CardPointer[cardIndex]->currentSuit].img);

}

void InBetween::MoveCard(sf::RenderWindow& window , int cardIndex , int desiredPosition) {

	 float x = cardSprite[cardIndex].getPosition().x;
	 float y = cardSprite[cardIndex].getPosition().y;



		if (x != desiredPosition) {
			x += 1;
			cardSprite[cardIndex].setPosition(x, y);
			DrawSprites(window);
			MoveCard(window, cardIndex, desiredPosition);
			
		}

		else {

			usedCards++;
			cardLeft--;

			if (usedCards == deck.TOTAL_CARDS - 1) {
				deck.ResetDeck();
				cardLeft = usedCards;
				usedCards = 1;
			}

			UpdateTextValue(cardsLeftTxt, cardLeft);
			UpdateTextValue(usedCardsTxt, usedCards);
			DrawSprites(window);
			return ;
		}

}




