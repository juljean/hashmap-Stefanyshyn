#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "TextBox.h"
#include "Button.h"

using namespace std;

int int_val() {
    int inp = 0;
    while (1) {
        if (scanf_s("%d", &inp)) {
            if (getchar() == '\n') {
                if (inp >= 0) return inp;
                else {
                    printf("WRONG VALUE\n");
                }
            }
            else
            {
                while (getchar() != '\n');
                printf("WRONG VALUE\n");
            }
        }
        else {
            while (getchar() != '\n');
            printf("WRONG VALUE\n");
        }
    }
}

float float_val(const char* prompt) {
    float inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%f", &inp)) {
            if (getchar() == '\n') {
                return inp;
            }
            else
            {
                while (getchar() != '\n');
                printf("WRONG VALUE\n");
            }
        }
        else {
            while (getchar() != '\n');
            printf("WRONG VALUE\n");
        }
    }
}

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
    cell.setFillColor(sf::Color(0,0,0));

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf :: Color :: White);

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < 2; k++) {
            if (k % 2 == 0) {
                cell.setSize(sf::Vector2f(70, 60));
                cell.setPosition(700 , 100 + i * 62);
            }
            else {
                cell.setSize(sf::Vector2f(400, 60));
                cell.setPosition(700 + 72, 100 + i * 62);
            }
            window.draw(cell);
        }
    }

    for (int elem = 0; elem < size; elem++) {
        text.setString(to_string(elem));
        text.setPosition(700, 100 + elem * 62);
        window.draw(text);
        int gap = 0;
        for (auto x : map[elem]) {
            text.setString(to_string(x));
            text.setPosition(700 + 72 + gap * 60, 100 + elem * 62);
            window.draw(text);
            gap++;
        }
    }
}

int main() {
    bool menuOpen = true;
    bool hashOpen = true;

    sf::Texture menuTexture;
    menuTexture.loadFromFile("menuBack.jpg");
    sf::Sprite hashBack(menuTexture);
    hashBack.scale(2.2, 2.2);

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Main window");
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error in opening font";
    }

    Menu menu(5);

    int element = -123321;
    int flagbtn = 0;
    Hash h(7);

    Textbox textbox1(30, sf::Color::Black, false);
    textbox1.setFont(font);
    textbox1.setPosition({ 10, 180 });
    textbox1.setLimit(true, 3);

    Button title("Hash Table", { 470, 60 }, 30, sf::Color(128, 64, 0), sf::Color::White);
    title.setPosition({ 700, 10 });
    title.setFont(font);

    Button insert_btn("Insert an element", { 270, 60 }, 30, sf::Color(128, 64, 0), sf::Color::White);
    insert_btn.setPosition({ 5, 10 });
    insert_btn.setFont(font);

    Button delete_btn("Delete an element", { 270, 60 }, 30, sf::Color(128, 64, 0), sf::Color::White);
    delete_btn.setPosition({ 300, 10 });
    delete_btn.setFont(font);

    Button menu_btn("Go to menu", { 270, 60 }, 30, sf::Color(128, 64, 0), sf::Color::White);
    menu_btn.setPosition({ 5, 600 });
    menu_btn.setFont(font);

    sf::Text action;
    action.setFont(font);
    action.setFillColor(sf::Color::Black);
    action.Bold;
    action.setPosition(10, 90);
    action.setCharacterSize(30);

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
                    if (flagbtn == 1 && element >= 0) {
                        h.insertit(element);
                        h.displayMap(window, font);
                        flagbtn = 0;
                    }
                    else if (flagbtn == 2 && element >= 0) {
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
                else if (menu_btn.isMouseOver(window)) menu_btn.setBackColor(sf::Color::Red);

                else {
                    insert_btn.setBackColor(sf::Color(128, 64, 0));
                    delete_btn.setBackColor(sf::Color(128, 64, 0));
                    menu_btn.setBackColor(sf::Color(128, 64, 0));
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (insert_btn.isMouseOver(window)) {
                    action.setString("Enter the element you want to add in a table\n(up to 3 NUMBERS and press ESC):");
                    textbox1.setSelected(true);
                    flagbtn = 1;
                }
                else if (delete_btn.isMouseOver(window)) {
                    action.setString("Enter the element you want to delete from a table\n(up to 3 NUMBERS and press ESC):");
                    textbox1.setSelected(true);
                    flagbtn = 2;
                }
                else if (menu_btn.isMouseOver(window)) {
                    menuOpen = true;
                }
            }
        }
        while (menuOpen)
        {
            bool ans = menu.draw();
            if (!ans) { 
                window.close();
            }
            menuOpen = false;
   
        }
        window.clear();
        window.draw(hashBack);
        window.draw(action);
        textbox1.drawTo(window);
        title.drawTo(window);
        menu_btn.drawTo(window);
        insert_btn.drawTo(window);
        delete_btn.drawTo(window);
        h.displayMap(window, font);
        window.display();

     }
    return 0;
}