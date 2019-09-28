#include "stdafx.h"
#include "Menu.h"
#include <iostream>

//shows the main menu
Menu::MenuResult Menu::Show(sf::RenderWindow& window) {
	//load menu image from file
	image.loadFromFile("images/menu.jpg");

	sprite.setTexture(image);

	//Play menu Item coordinates
	MenuItem playButton;
	playButton.rect.top = 348;
	playButton.rect.height = 456;
	playButton.rect.left = 296;
	playButton.rect.width = 717;
	playButton.action = Play;


	//Exit menu Imte coordinates
	MenuItem exitButton;
	exitButton.rect.top = 505;
	exitButton.rect.height = 612;
	exitButton.rect.left = 296;
	exitButton.rect.width = 721;
	exitButton.action = Exit;

	menuItems.push_back(playButton); //push the play button in the list
	menuItems.push_back(exitButton); //push the exit button in the list

	window.clear();
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);

}

// return an enum MenuResult(action) whether it is nothing , play or exit
Menu::MenuResult Menu::HandleClick(int x, int y) {
	std::list<MenuItem>::iterator i;

	for (i = menuItems.begin(); i != menuItems.end(); i++) {

		sf::Rect<int> menuItemRect = i->rect;
		//check if the x and y axis of the mousepress is in the area of our menuItemRect
		if (menuItemRect.height > y && menuItemRect.top < y && menuItemRect.width > x && menuItemRect.left < x) {

			return i->action;
		}
	}

	return Nothing; 
}

Menu::MenuResult Menu::GetHoveredItem(sf::RenderWindow& window) {

	sf::Mouse mouse;

	std::list<MenuItem>::iterator i;

	for (i = menuItems.begin(); i != menuItems.end(); i++) {

		sf::Rect<int> menuItemRect = i->rect;

		//check if the x and y axis of the mousepress is in the area of our menuItemRect
		if ( menuItemRect.height > mouse.getPosition(window).y 
			 && menuItemRect.top < mouse.getPosition(window).y 
			 && menuItemRect.width > mouse.getPosition(window).x
			 && menuItemRect.left < mouse.getPosition(window).x ) 
		
				return i -> action;
		

	}

	return Nothing;
}






Menu::MenuResult Menu::GetMenuResponse(sf::RenderWindow& window) {

	sf::Event menuEvent;
	int hoveredItem;

	while (true) {
		while (window.pollEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::MouseButtonPressed) {
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed) {
				return Exit; 
			}

			hoveredItem = GetHoveredItem(window);


			if (hoveredItem == Nothing)
				image.loadFromFile("images/menu.jpg");
			else if (hoveredItem == Play)
				image.loadFromFile("images/hover-start.jpg");
			else if (hoveredItem == Exit)
				image.loadFromFile("images/hover-exit.jpg");

			sprite.setTexture(image);
			window.clear();
			window.draw(sprite);
			window.display();
		}


	}
}

