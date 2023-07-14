#pragma once
#include "Pole.h"
using namespace sf;

class Coord {
private:
	int X; 
	int Y; 
public:
	Coord(): X(), Y() {}

	int getX() const { return X; } 
	int getY() const { return Y; } 

	void setXY(int X2, int Y2) { X = X2, Y = Y2; }
	void setX(int X2) { X = X2; } 
	void setY(int Y2) { Y = Y2; } 

	void DrawCanvas(Sprite& cubes, RenderWindow& window, Pole& pole, int color);

	//дeструктор
	~Coord() = default;
} h[4], w[4];

void DrawCanvas(Sprite& cubes, RenderWindow& window, Pole& pole, int color) {
	for (int i = 0; i < 4; i++) {
		cubes.setTextureRect(IntRect(color * pole.getSize(), 0, pole.getSize(), pole.getSize()));
		cubes.setPosition(h[i].getX() * pole.getSize(), h[i].getY() * pole.getSize());
		window.draw(cubes);
	}
}