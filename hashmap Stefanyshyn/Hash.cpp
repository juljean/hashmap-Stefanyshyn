#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "Menu.h"
using namespace std;

sf::Font font;

class Hash {
    int size;
    list<int>* map;

public:
    Hash(int sizemap);
    void insertit(int key);
    void deleteit(int key);
    void displayMap(sf::RenderWindow &window);
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

void Hash::displayMap(sf :: RenderWindow &window) {
    sf::RectangleShape cell(sf::Vector2f(200, 30));
    sf::RectangleShape title(sf::Vector2f(200, 30));

    sf::Text text;
    sf::Text title_text;

    cell.setFillColor(sf :: Color(204, 255, 255));
    title.setFillColor(sf::Color(102, 102, 153));

    title.setSize(sf::Vector2f(300, 60));
    title.setPosition(700, 5);

    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error in opening font";
    }

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
    sf::RenderWindow window(sf::VideoMode(1400, 900), "Main window");
    Menu menu(window.getSize().x, window.getSize().y);

    sf::RectangleShape bt_insert(sf::Vector2f(270, 60));
    sf::RectangleShape bt_delete(sf::Vector2f(270, 60));
    sf::Text insert_text;
    sf::Text delete_text;

    bt_insert.setFillColor(sf::Color(102, 102, 153));

    insert_text.setFont(font);
    insert_text.setFillColor(sf::Color::Black);

    insert_text.Bold;
    delete_text = insert_text;

    insert_text.setString("Insert an element");
    delete_text.setString("Delete an element");

    insert_text.setPosition(10, 10);
    delete_text.setPosition(310, 10);

    bt_delete = bt_insert;
    bt_insert.setPosition(5, 10);
    bt_delete.setPosition(300, 10);

    vector<int>a;
    int element;
    int menuNum;
    Hash h(7);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        if (sf::IntRect(0, 0, 270, 60).contains(sf::Mouse::getPosition(window))) { bt_insert.setFillColor(sf::Color(255, 200, 227)); menuNum = 1; }
        if (sf::IntRect(300, 0, 500, 60).contains(sf::Mouse::getPosition(window))) { bt_delete.setFillColor(sf::Color(255, 200, 227)); menuNum = 2; }

        while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) { //insert
                bt_insert.setFillColor(sf::Color(102, 102, 153));
                cout << "Enter the number you want to add:";
                cin >> element;
                h.insertit(element);
                h.displayMap(window);
                menuNum = 0;
            }

            if (menuNum == 2) { //delete
                bt_delete.setFillColor(sf::Color(102, 102, 153));
                cout << "Enter the number you want to delete:";
                cin >> element;
                h.deleteit(element);
                h.displayMap(window);
                menuNum = 0;
            }
        }
        window.clear();

        menu.draw(window);
        window.draw(bt_insert);
        window.draw(bt_delete);
        window.draw(delete_text);
        window.draw(insert_text);

        h.displayMap(window);
        window.display();
        }
    return 0;
}