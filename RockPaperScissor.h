#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <list>
class RockPaperScissor
{
public:

	enum RPSPicked{Nothing , Rock , Paper, Scissor};
	enum RPSWinner{Quit , Draw , Player , CPU};

	//the rock , paper and scissor placed on the left screen ( acts as a button )
	struct Weapon{
		sf::Rect<int> rect; //the rectangle will serves as the box where the image is placed.(it is the one responsible for sensing the mouse events, not the image)
		RPSPicked type;	//this is the kind of weapon clicked or hovered (rock , paper, or scissors)
	};


	RockPaperScissor::RPSWinner PlayRPS(sf::RenderWindow &renderWindow);//this was made public so that the Game class could call it


private:

	double imgWidth = 142.5, imgHeight = 173.3;	//the exact width and height of each img in the spritesheet

	sf::Mouse mouse;	//the mouse object to tract the coordinates of the mouse respective to the window

	sf::Texture rockImg, paperImg, scissorImg, bgImg, bgWin, bgLose, bgDraw; //textures to hold normal images

	sf::Texture rockGlow, paperGlow, scissorGlow;	//textures to hold imgs with glow or highlights

	//holds the Texture of Weapons  that will be placed both left and right of the screen
	sf::Sprite  L_RockSprite, L_PaperSprite, L_ScissorSprite ,
				R_RockSprite, R_PaperSprite, R_ScissorSprite , 
				bgSprite ;
	

	std::list<Weapon> weapon;	//the storage of the Weapon structure

	RPSPicked RockPaperScissor::GetAIPick(); //generate a random number from 1 to 3 and converts it to an Enum of RPSPicked
	RPSPicked GetHoveredItem(sf::RenderWindow& window);
	RPSPicked HandleClick(int x , int y);
	RPSWinner RockPaperScissor::GetRPSWinner(RPSPicked aiPicked, RPSPicked playerPicked);

	void DrawSprites(sf::RenderWindow& window);
	void UpdateRightSprites(sf::RenderWindow& window, RPSPicked aiPick);
	void InitializeWeapons();
	void LoadImages();
	void InitializeSprites();
	void UpdateBgSprite(sf::RenderWindow& window, RockPaperScissor::RPSWinner winner);
	void DisplayPicks(sf::RenderWindow& window, RPSPicked ai, RPSPicked player);
};

