#include "stdafx.h"
#include "SplashScreen.h"
#include <iostream>
void SplashScreen::Show(sf::RenderWindow& renderWindow) {
	sf::Texture image;
	int width = 780;
	int height = 107;

	if (!image.loadFromFile("images/splash.jpg"))  std::cout << "Image not Found!" << std::endl;
	
	sf::Sprite sprite(image);
	sf::RectangleShape rectangle(sf::Vector2f(0,height));
	rectangle.setPosition(sf::Vector2f(120, 520));

	while (true) {

		float w = rectangle.getSize().x;

		if (w <= width) {
			w += 50;
			rectangle.setSize(sf::Vector2f(w, height));
			rectangle.setFillColor(sf::Color::Green);
			sf::sleep(sf::milliseconds(80));
		}
		else
			return;

		renderWindow.draw(sprite);
		renderWindow.draw(rectangle);
		renderWindow.display();
		
	}
		
}