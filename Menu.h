#pragma once
#include "SFML/Graphics.hpp"
#include<list>
#include<iostream>
class Menu
{
public:
	enum MenuResult {Nothing , Exit , Play };

	struct MenuItem
	{
	public:
		sf::Rect<int> rect; //represents the dimension of the MenuItem
		MenuResult action; // is it nothing , an Exit or a Play?
	};

	MenuResult Show(sf::RenderWindow& window);

	sf::Texture image;
	sf::Sprite sprite;

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	MenuResult GetHoveredItem(sf::RenderWindow& window);

	std::list<MenuItem> menuItems;
	
};

