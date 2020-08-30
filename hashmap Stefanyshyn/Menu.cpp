#include "Menu.h"
#include "Button.h"
#include <iostream>

Menu::Menu(int k) {
}

Menu::~Menu() {

}

bool Menu::draw() {
	sf::RenderWindow MenuW(sf::VideoMode(1200, 700), "Menu Bar");
	sf::Texture menuTexture;
	menuTexture.loadFromFile("hashBack.jpg");
	sf::Sprite menuBack(menuTexture);
	menuBack.scale(2.2, 2.2);

	font.loadFromFile("font.ttf");

	Button start_btn("Start", { 130, 60 }, 30, sf::Color(0,0,0,95), sf::Color::White);
	start_btn.setPosition({ 900, 120 });
	start_btn.setFont(font);

	Button exit_btn("Exit", { 130, 60 }, 30, sf::Color(0, 0, 0, 95), sf::Color::White);
	exit_btn.setPosition({ 900, 460 });
	exit_btn.setFont(font);

	std::string note = "Topic: CHAINED HASHMAP\n\n\n\n\n\n\n\nCreated by Nazar Stefanyshyn KM-91";
	Button notif_btn(note , { 600, 400 }, 30, sf::Color(0, 0, 0, 85), sf::Color::White);
	notif_btn.setPosition({ 60, 120 });
	notif_btn.setFont(font);

	while (MenuW.isOpen())
	{
		sf::Event event;
		while (MenuW.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				MenuW.close();

			case sf::Event::MouseMoved:
				if (start_btn.isMouseOver(MenuW)) start_btn.setBackColor(sf::Color::Red);

				else if (exit_btn.isMouseOver(MenuW)) exit_btn.setBackColor(sf::Color::Red);

				else {
					start_btn.setBackColor(sf::Color(0, 0, 0, 95));
					exit_btn.setBackColor(sf::Color(0, 0, 0, 95));
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (start_btn.isMouseOver(MenuW)) {
					MenuW.close();
					return true;
				} 
				else if (exit_btn.isMouseOver(MenuW)) {
					MenuW.close();
					return false;
				}
			}
		}
	MenuW.clear();
	MenuW.draw(menuBack);
	start_btn.drawTo(MenuW);
	exit_btn.drawTo(MenuW);
	notif_btn.drawTo(MenuW);
	MenuW.display();
	}

}