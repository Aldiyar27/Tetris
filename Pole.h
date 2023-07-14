#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <time.h>
using namespace sf;

#define RAND(min, max) (rand()%((max)-(min)+1)+(min))
//размер одной плитки/кубика для sfml
#define CUBES 18
//класические размеры поля игры тетрис
#define HEIGHT 20
#define WIDTH 10

class Pole
{
private:
	int** MasPole;
	float Size;
	int   Height;      
	int   Width;             
public:
	Pole() :Height(HEIGHT), Width(WIDTH), Size(CUBES) {
		MasPole = new int*[HEIGHT];
		for (int i = 0; i < HEIGHT; ++i) {
			MasPole[i] = new int[WIDTH];
		}
	}
	Pole(int height, int width) :Height(height), Width(width) {}
	Pole(int height, int width, float size) :Height(height), Width(width), Size(size) {}

	//get
	int   getHeight() const { return Height; }
	int   getWidth() const { return Width; }
	float getSize() const { return Size; }
	//set
	void setSize(float size) { Size = size; }
	void set_height_width(int height, int width) { Height = height, Width = width; }

	//Реализация методов в Pole.cpp
	void Insert(int i, int j, int data);
	int  Search(int i, int j);
	void Copy  (int i, int j, int i2, int j2);
	bool Lose();
	void Show(Sprite& cubes, RenderWindow& window);
	void Delete();
	void Null();

	// Дeструктор
	~Pole() { Delete(); }
};


