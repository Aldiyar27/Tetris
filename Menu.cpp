#include "Menu.h"
#include <SFML/Graphics.hpp>
#pragma warning(disable : 4996) 

void Tetris();
void MainMenu();

Menu menu(0, 0);

Menu::Menu(int height, int width)
{
	font.loadFromFile("Tetris.ttf");

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("New game");
	menu[0].setCharacterSize(20);
	menu[0].setPosition(35, 150);

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("        Exit    ");
	menu[1].setCharacterSize(20);
	menu[1].setPosition(35, 190);
	Select = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	t.loadFromFile("C:/Users/Notebook/Desktop/images/background.jpg");
	Sprite background(t);
	window.draw(background);
	for (int i = 0; i < ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::Move(int code)
{
	if (code == sf::Keyboard::Up) {
		if (Select - 1 >= 0)
		{
			menu[Select].setColor(sf::Color::White);
			Select--;
			menu[Select].setColor(sf::Color::Red);
		}
	}
	if (code == sf::Keyboard::Down) {
		if (Select + 1 < ITEMS)
		{
			menu[Select].setColor(sf::Color::White);
			Select++;
			menu[Select].setColor(sf::Color::Red);
		}
	}
}

int Menu::getSelect()
{
	return Select;
}

void MainMenu() {
	RenderWindow window(VideoMode(180, 360), "Tetris!");

	while (window.isOpen())
	{
		Event key;
		while (window.pollEvent(key))
		{
			switch (key.type)
			{
			case Event::KeyReleased:
				switch (key.key.code)
				{
				case Keyboard::Up: case Keyboard::Down:
					menu.Move(key.key.code);
					break;
				case Keyboard::Return:
					switch (menu.getSelect())
					{
					case 0: Tetris();
						break;
					case 1: window.close();
					}
					break;
				}
				break;
			case Event::Closed: window.close();
			}
		}
		window.clear();
		menu.draw(window);
		window.display();
	}
}