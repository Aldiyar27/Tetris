#include "Pole.h"
using namespace sf;

void Pole::Insert(int i, int j, int data) { MasPole[i][j] = data; }

int Pole::Search(int i, int j) {
	if (i < 0 || j < 0 || i > Height || j > Width) { return -1; }
	return MasPole[i][j];
}

void Pole::Show(Sprite& shape, RenderWindow& window) {
	for (int i = 0; i < getHeight(); i++) {
		for (int j = 0; j < getWidth(); j++) {
			if (Search(i, j) != 0) {
				shape.setTextureRect(IntRect(Search(i, j) * getSize(), 0, getSize(), getSize()));
				shape.setPosition(j * getSize(), i * getSize());
				window.draw(shape);
			}
		}
	}
}
void Pole::Copy(int i, int j, int i2, int j2) { MasPole[i][j] = MasPole[i2][j2]; }

void Pole::Null() {
	for (int i = 0; i < getHeight(); i++) {
		for (int j = 0; j < getWidth(); j++) {
			MasPole[i][j] = 0;
		}
	}
}

bool Pole::Lose() {
	for (int i = 0; i < Width; i++) {
		if (Search(0, i) != 0) { return true; }
	}
	return false;
}

void Pole::Delete() { delete[] MasPole; }
