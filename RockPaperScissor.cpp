#include "stdafx.h"
#include "RockPaperScissor.h"
#include <iostream>

RockPaperScissor::RPSWinner RockPaperScissor::PlayRPS(sf::RenderWindow& renderWindow) {

	bgImg.loadFromFile("images/rps-bg.png");

	InitializeWeapons(); 

	LoadImages();

	InitializeSprites();
	
	srand(time(NULL));

	sf::Event event;


	while (true) {
	
		DrawSprites(renderWindow);

			while (renderWindow.pollEvent(event)) {
			
					if (event.type == sf::Event::Closed)	return Quit;
					
			
					if (event.type == sf::Event::MouseButtonPressed) {

						RPSPicked playerPick = HandleClick(event.mouseButton.x , event.mouseButton.y);

							if (playerPick != Nothing) {
					
									RPSPicked aiPick = GetAIPick();
									UpdateRightSprites(renderWindow , aiPick);
									RPSWinner winner = GetRPSWinner(aiPick, playerPick);
									UpdateBgSprite(renderWindow , winner);
									DisplayPicks(renderWindow, aiPick, playerPick);
									sf::sleep(sf::milliseconds(1000));
									return winner;

							}
					
					}
			

			}

	}

}


RockPaperScissor::RPSWinner RockPaperScissor::GetRPSWinner(RPSPicked aiPicked, RPSPicked playerPicked) {

	if (aiPicked == playerPicked)
		return Draw; 
	else if ( (aiPicked == Rock && playerPicked == Scissor )|| (aiPicked == Paper && playerPicked == Rock) || (aiPicked == Scissor && playerPicked == Paper) )
		return CPU;
	else
		return Player;
	
}

void RockPaperScissor::DrawSprites(sf::RenderWindow& window) {


	RPSPicked hoveredItem = GetHoveredItem(window);

	if (hoveredItem == Rock) {
		L_RockSprite.setTexture(rockGlow);
		L_PaperSprite.setTexture(paperImg);
		L_ScissorSprite.setTexture(scissorImg);
	}
	else if (hoveredItem == Paper) {
		L_PaperSprite.setTexture(paperGlow);
		L_RockSprite.setTexture(rockImg);
		L_ScissorSprite.setTexture(scissorImg);
	}
	else if (hoveredItem == Scissor) {
		L_ScissorSprite.setTexture(scissorGlow);
		L_RockSprite.setTexture(rockImg);
		L_PaperSprite.setTexture(paperImg);
	}
	else {
		L_RockSprite.setTexture(rockImg);
		L_PaperSprite.setTexture(paperImg);
		L_ScissorSprite.setTexture(scissorImg);
	}

	window.clear();
	window.draw(bgSprite);
	window.draw(L_RockSprite);
	window.draw(L_PaperSprite);
	window.draw(L_ScissorSprite);
	window.draw(R_RockSprite);
	window.draw(R_PaperSprite);
	window.draw(R_ScissorSprite);
	window.display();
}

RockPaperScissor::RPSPicked RockPaperScissor::GetAIPick() {
	
	int aipick = 1 + (rand() % 3);
	if (aipick == 1) return Rock;
	else if (aipick == 2) return Paper;
	else return Scissor;
	

}

RockPaperScissor::RPSPicked RockPaperScissor::HandleClick(int x, int y) {

	std::list<Weapon>::iterator i;

	for (i = weapon.begin(); i != weapon.end(); i++) {

		sf::Rect<int> weaponRect= i->rect;
		//check if the x and y axis of the mousepress is in the area of our weaponRect
		
		if (weaponRect.height > y && weaponRect.top < y && weaponRect.width > x && weaponRect.left < x) {

			return i ->  type;

		}

	}

	return Nothing;

}

RockPaperScissor::RPSPicked RockPaperScissor::GetHoveredItem(sf::RenderWindow& renderWindow ) {

	std::list<Weapon>::iterator i;

	for (i = weapon.begin(); i != weapon.end(); i++) {

		sf::Rect<int> weaponRect = i->rect;
		//check if the x and y axis of the mousepress is in the area of our weaponRect
		if (weaponRect.height > mouse.getPosition(renderWindow).y && weaponRect.top < mouse.getPosition(renderWindow).y && weaponRect.width > mouse.getPosition(renderWindow).x
			&& weaponRect.left < mouse.getPosition(renderWindow).x) {
			return i -> type;
		}
	}

	return Nothing;
}

void RockPaperScissor::InitializeSprites() {
	//background
	bgSprite.setTexture(bgImg);

	//left side
	L_RockSprite.setTexture(rockImg);
	L_RockSprite.setPosition(sf::Vector2f(185, 270));


	L_PaperSprite.setTexture(paperImg);
	L_PaperSprite.setPosition(sf::Vector2f(112, 385));

	L_ScissorSprite.setTexture(scissorImg);
	L_ScissorSprite.setPosition(sf::Vector2f(275, 388));

	//right side
	R_RockSprite.setTexture(rockImg);
	R_RockSprite.setPosition(sf::Vector2f(735, 270));


	R_PaperSprite.setTexture(paperImg);
	R_PaperSprite.setPosition(sf::Vector2f(665, 385));

	R_ScissorSprite.setTexture(scissorImg);
	R_ScissorSprite.setPosition(sf::Vector2f(825, 388));
}

void RockPaperScissor :: InitializeWeapons() {

	//initialize rock's invisible rectangle
	RockPaperScissor::Weapon rock;
	rock.rect.top = 305;
	rock.rect.height = 395;
	rock.rect.left = 207;
	rock.rect.width = 289;
	rock.type = Rock;


	//initialize paper's invisible rectangle 
	RockPaperScissor::Weapon paper;
	paper.rect.top = 398;
	paper.rect.height = 525;
	paper.rect.left = 123;
	paper.rect.width = 215;
	paper.type = Paper;


	//initialize scissor's invisible rectangle  
	RockPaperScissor::Weapon scissor;
	scissor.rect.top = 401;
	scissor.rect.height = 527;
	scissor.rect.left = 290;
	scissor.rect.width = 375;
	scissor.type = Scissor;
	

	weapon.push_back(rock);
	weapon.push_back(paper);
	weapon.push_back(scissor);

}

void RockPaperScissor::LoadImages() {

	bgLose.loadFromFile("images/bg-lose.png");
	bgWin.loadFromFile("images/bg-win.png");
	bgDraw.loadFromFile("images/bg-draw.png");

	rockImg.loadFromFile("images/spritesheet.png", sf::IntRect(0, imgHeight * 1, imgWidth, imgHeight));
	paperImg.loadFromFile("images/spritesheet.png", sf::IntRect(0, imgHeight * 2, imgWidth, imgHeight));
	scissorImg.loadFromFile("images/spritesheet.png", sf::IntRect(0, imgHeight * 0, imgWidth, imgHeight));

	rockGlow.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 1, imgHeight * 1, imgWidth, imgHeight));
	paperGlow.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 1, imgHeight * 2, imgWidth, imgHeight));
	scissorGlow.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 1, imgHeight * 0, imgWidth, imgHeight));
}

void RockPaperScissor::UpdateRightSprites(sf::RenderWindow& window , RockPaperScissor::RPSPicked aiPick) {

	if (aiPick == Rock) {
		R_RockSprite.setTexture(rockGlow);
		window.draw(R_RockSprite);
		window.display();
		sf::sleep(sf::milliseconds(500));
	}
		
	else if (aiPick == Paper) {
		R_PaperSprite.setTexture(paperGlow);
		window.draw(R_PaperSprite);
		window.display();
		sf::sleep(sf::milliseconds(500));
		
	
		
	}
	
	else {
		R_ScissorSprite.setTexture(scissorGlow);
		window.draw(R_ScissorSprite);
		window.display();
		sf::sleep(sf::milliseconds(500));

	}
		
}

void RockPaperScissor::UpdateBgSprite(sf::RenderWindow& window, RockPaperScissor::RPSWinner winner) {

	if (winner == Player) {
		bgSprite.setTexture(bgWin);
		window.clear();
		window.draw(bgSprite);
	
	}
	else if (winner == CPU) {
		bgSprite.setTexture(bgLose);
		window.clear();
		window.draw(bgSprite);
		
	}
	else {
		bgSprite.setTexture(bgDraw);
		window.clear();
		window.draw(bgSprite);

	}
}




void RockPaperScissor::DisplayPicks(sf::RenderWindow& window, RockPaperScissor::RPSPicked ai, RockPaperScissor::RPSPicked player) {
	sf::Texture l_img, r_img;
	sf::Sprite l_sprite, r_sprite;
	//left side
	if(player == Rock)
		l_img.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 2, imgHeight * 1, imgWidth, imgHeight));
	else if(player == Paper)
		l_img.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 2, imgHeight * 2, imgWidth, imgHeight));
	else if (player == Scissor)
		l_img.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 2, imgHeight * 0, imgWidth, imgHeight));

	//right side
	if (ai == Rock)
		r_img.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 3, imgHeight * 1, imgWidth, imgHeight));
	else if (ai == Paper)
		r_img.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 3, imgHeight * 2, imgWidth, imgHeight));
	else if (ai == Scissor)
		r_img.loadFromFile("images/spritesheet.png", sf::IntRect(imgWidth * 3, imgHeight * 0, imgWidth, imgHeight));


	l_sprite.setTexture(l_img);
	l_sprite.setPosition(sf::Vector2f(317, 245));

	r_sprite.setTexture(r_img);
	r_sprite.setPosition(558, 245);

	window.draw(l_sprite);
	window.draw(r_sprite);
	window.display();
}