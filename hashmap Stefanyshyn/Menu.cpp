#include "Menu.h"

Menu::Menu(float width, float height) {
	font.loadFromFile("font.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Start");
	menu[0].setPosition(sf::Vector2f(width / 2, height / MAX_NUMBER_OF_ITEMS * 0.5));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(width / 2, height / MAX_NUMBER_OF_ITEMS * 1.5));

}

Menu::~Menu() {

}

void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) window.draw(menu[i]);
}