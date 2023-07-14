#include <time.h>
#include "Pole.h"
#include "Game.h"
#include "Menu.h"
using namespace sf;

void Tetris();
void MainMenu();

// 7 фигур
int Figures[7][4] = {
	1, 3, 5, 7, 
	2, 4, 5, 7, 
	3, 5, 4, 6, 
	3, 5, 4, 7, 
	2, 3, 5, 7, 
	3, 5, 7, 6, 
	2, 3, 4, 5  
};

void Tetris() {
	void Copy(int x = 0);
	bool Check(Pole & Pole);

	//переменные sfml
	Pole    Pole;
	Texture texture, t2;
	Clock   clock;
	Sprite  shape(texture);

	//обычные перемнные
	int   Coord = 0;
	float Time = 0;
	int   Add = true;
	int   Count_Color = 1;
	float Delay = 0.5;
	int   Rotation = false;
	

	Pole.set_height_width(HEIGHT, WIDTH);
	Pole.setSize(CUBES);
	Pole.Null();
	std::string filename = "C:/Users/Notebook/Desktop/images/tiles.png";
	texture.loadFromFile(filename);
	t2.loadFromFile("C:/Users/Notebook/Desktop/images/background.jpg");
	Sprite background(t2);

	srand(time(0));

	RenderWindow window(VideoMode(180, 360), "Tetris!");
	while (window.isOpen())
	{
		if (Pole.Lose() == true) {
			Text text;
			Font font;
			font.loadFromFile("Tetris.ttf");
			text.setFont(font);
			text.setPosition(30, 150);
			text.setString("Game Over");
			text.setCharacterSize(20);

			while (window.isOpen()) {
				Event event;
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) { window.close(); }
					if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::Escape) { MainMenu(); }
					}
				}
				window.clear();
				window.draw(background);
				window.draw(text);
				window.display();
			}
		}

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		Time += time;
		Event key;

		while (window.pollEvent(key))
		{
			if (key.type == Event::Closed) { window.close(); }
			else if (key.type == Event::KeyPressed) {
				if (key.key.code == Keyboard::Up || 
					key.key.code == Keyboard::W) { Rotation = true; }

				else if (key.key.code == Keyboard::Right || 
					     key.key.code == Keyboard::D) { Coord =  1; }

				else if (key.key.code == Keyboard::Left || 
					key.key.code == Keyboard::A) { Coord = -1; }

				else if (key.key.code == Keyboard::Escape) {
					MainMenu();
					return;
				}
				else if (key.key.code == Keyboard::Space) {
					Text pause;
					Font font;
					font.loadFromFile("Tetris.ttf");
					pause.setFont(font);
					pause.setPosition(55, 160);
					pause.setString("Pause");
					pause.setCharacterSize(20);

					while (window.waitEvent(key)) {

						window.draw(background);
						window.draw(pause);
						window.display();

						if (key.type == Event::Closed) { window.close(); return; }
						if (key.type == Event::KeyPressed) {
							break;
						}
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) || 
			Keyboard::isKeyPressed(Keyboard::S)) { Delay = 0.05; }

		for (int i = 0; i < 4; i++) {
			w[i] = h[i];
			h[i].setX(h[i].getX() + Coord);
		}

		if (!Check(Pole)) { Copy(); }

		if (Rotation != 0) {
			for (int i = 0; i < 4; i++) {
				h[i].setXY(h[1].getX() - 
					(h[i].getY() - h[1].getY()),
					 h[1].getY() + (h[i].getX() - h[1].getX()));
			}
			if (!Check(Pole)) { Copy(); }
		}

		int temp = RAND(0, 6);
		if (Time > Delay) {
			Copy(1);
			if (!Check(Pole)) {
				for (int i = 0; i < 4; i++) { Pole.Insert(w[i].getY(), w[i].getX(), Count_Color); }
				Count_Color = 1 + temp;
				for (int i = 0; i < 4; i++) {
					h[i].setXY(Figures[temp][i] % 2, Figures[temp][i] / 2);
				}
			}
			Time = 0;
		}

		if (Add != 0) {
			if (h[0].getX() == 0) {
				for (int i = 0; i < 4; i++) { h[i].setXY(Figures[temp][i] % 2, Figures[temp][i] / 2); }
			}
			Add = false;
		}
		int StaticTemp = Pole.getHeight() - 1;

		for (int i = Pole.getHeight() - 1; i > 0; i--) {
			int count = 0;
			for (int j = 0; j < Pole.getWidth(); j++) {
				if (Pole.Search(i, j) != 0) { count++; }
				Pole.Copy(StaticTemp, j, i, j);
			}
			if (count < Pole.getWidth()) { StaticTemp--; }
		}

		window.clear(Color::White);
		window.draw(background);
		Delay = 0.3;
		Coord = 0;
		Rotation = false;

		Pole.Show(shape, window);

		for (int i = 0; i < 4; i++) {
			shape.setTextureRect(IntRect(Count_Color * Pole.getSize(), 0, Pole.getSize(), Pole.getSize()));
			shape.setPosition(h[i].getX() * Pole.getSize(), h[i].getY() * Pole.getSize());
			window.draw(shape);
		}
		window.display();
	}
	return;
}

bool Check(Pole& Pole) {
	for (int i = 0; i < 4; i++) {
		if (h[i].getX() < 0 ||
			h[i].getX() >= Pole.getWidth() ||
			h[i].getY() >= Pole.getHeight())
		{ return false; }
		if (Pole.Search(h[i].getY(), h[i].getX()) != 0) { return false; }
	}
	return true;
}

void Copy(int x = 0) {
	if (x == 1) {
		for (int i = 0; i < 4; i++) {
			h[i] = w[i];
			h[i].setY(h[i].getY() + 1);
		}
	}
	else {
		for (int i = 0; i < 4; i++) { h[i] = w[i]; }
	}
}