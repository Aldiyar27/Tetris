#pragma once
#include <SFML/Graphics.hpp>
#define ITEMS 2
using namespace sf;

class Menu
{
private:
	Font font;
	Text menu[ITEMS];
	Texture t;
public:
	int Select;
	Menu(int height, int width);
	~Menu();

	int getSelect();
	void draw(RenderWindow& window);
	void Move(int code);
};