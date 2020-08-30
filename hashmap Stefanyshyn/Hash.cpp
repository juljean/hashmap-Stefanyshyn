#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "TextBox.h"
#include "Button.h"

using namespace std;

class Hash {
    int size;
    list<int>* map;

public:
    Hash(int sizemap);
    void insertit(int key);
    void deleteit(int key);
    void displayMap(sf::RenderWindow &window, sf::Font &font);
};

Hash::Hash(int sizemap) {
    this->size = sizemap;
    map = new list<int>[sizemap];
}

void Hash::insertit(int key) {
    int index = key % size;
    map[index].push_back(key);
}

void Hash::deleteit(int key) {
    int index = key % size;
    list<int> ::iterator elem;
    for (elem = map[index].begin(); elem != map[index].end(); elem++) {
        if (*elem == key) break;
    }
    if (elem != map[index].end()) map[index].erase(elem);
}

void Hash::displayMap(sf :: RenderWindow &window, sf::Font &font) {
    sf::RectangleShape cell(sf::Vector2f(200, 30));
    sf::RectangleShape title(sf::Vector2f(200, 30));

    sf::Text text;
    sf::Text title_text;

    cell.setFillColor(sf :: Color(204, 255, 255));
    title.setFillColor(sf::Color(102, 102, 153));

    title.setSize(sf::Vector2f(300, 60));
    title.setPosition(700, 5);

    text.setFont(font);
    text.setFillColor(sf :: Color :: Black);

    title_text.setFont(font);
    title_text.setFillColor(sf :: Color :: White);
    title_text.setString("Hash Table");
    title_text.setPosition(780, 10);


    for (int i = 0; i < size; i++) {
        for (int k = 0; k < 2; k++) {
            if (k % 2 == 0) {
                cell.setSize(sf::Vector2f(70, 60));
                cell.setPosition(700 , 70 + i * 62);
            }
            else {
                cell.setSize(sf::Vector2f(300, 60));
                cell.setPosition(700 + 72, 70 + i * 62);
            }
            window.draw(cell);
        }
    }

    for (int elem = 0; elem < size; elem++) {
        text.setString(to_string(elem));
        text.setPosition(700, 70 + elem * 62);
        window.draw(text);
        int gap = 0;
        for (auto x : map[elem]) {
            text.setString(to_string(x));
            text.setPosition(700 + 72 + gap * 60, 70 + elem * 62);
            window.draw(text);
            gap++;
        }
    }
    window.draw(title);
    window.draw(title_text);
}

int main() {
    bool menuOpen = true;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Main window");
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error in opening font";
    }

    Menu menu(5);

    int element = 0;
    int flagbtn = 0;
    Hash h(7);

    Textbox textbox1(20, sf::Color::White, false);
    textbox1.setFont(font);
    textbox1.setPosition({ 10, 140 });
    textbox1.setLimit(true, 5);

    Button insert_btn("Insert an element", { 270, 60 }, 30, sf::Color(102, 102, 153), sf::Color::White);
    insert_btn.setPosition({ 5, 10 });
    insert_btn.setFont(font);

    Button delete_btn("Delete an element", { 270, 60 }, 30, sf::Color(102, 102, 153), sf::Color::White);
    delete_btn.setPosition({ 300, 10 });
    delete_btn.setFont(font);

    sf::Text action;
    action.setFont(font);
    action.setFillColor(sf::Color::White);
    action.setPosition(10, 90);
    action.setCharacterSize(20);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();

            case sf::Event::TextEntered:
                textbox1.typedOn(event);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    stringstream el(textbox1.getText());
                    el >> element;
                    if (flagbtn == 1) {
                        h.insertit(element);
                        h.displayMap(window, font);
                        flagbtn = 0;
                    }
                    else if (flagbtn == 2) {
                        h.deleteit(element);
                        h.displayMap(window, font);
                        flagbtn = 0;
                    }
                    action.setString("");
                    textbox1.setSelected(false);
                    textbox1.deletestr();
                }
                break;

            case sf::Event::MouseMoved:
                if (insert_btn.isMouseOver(window)) insert_btn.setBackColor(sf::Color::Red);

                else if (delete_btn.isMouseOver(window)) delete_btn.setBackColor(sf::Color::Red);

                else {
                    insert_btn.setBackColor(sf::Color(102, 102, 153));
                    delete_btn.setBackColor(sf::Color(102, 102, 153));
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (insert_btn.isMouseOver(window)) {
                    action.setString("Enter the element you want to add in a table\n(up to 3 numbers and press ESC):");
                    textbox1.setSelected(true);
                    flagbtn = 1;
                }
                else if (delete_btn.isMouseOver(window)) {
                    action.setString("Enter the element you want to delete from a table\n(up to 3 numbers and press ESC):");
                    textbox1.setSelected(true);
                    flagbtn = 2;
                }
            }
        }
        while (menuOpen)
        {
            menu.draw();
            menuOpen = false;
   
        }
        window.clear();
        window.draw(action);
        textbox1.drawTo(window);
        insert_btn.drawTo(window);
        delete_btn.drawTo(window);
        h.displayMap(window, font);
        window.display();
     }
    return 0;
}