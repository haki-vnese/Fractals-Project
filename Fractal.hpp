#pragma once
#include <iostream>
#include "Pixel.hpp"
#include "Complex.hpp"
#include <algorithm>
using namespace std;

class Fractal
{
private:
	unsigned int cols;
	unsigned int rows;
	Pixel** grid;
	static const unsigned int maxIter;
public:
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	~Fractal();
	const Fractal& operator=(const Fractal&);
	Fractal& operator=(Fractal&&);
	friend void saveToPPM(const Fractal&, const string& name);
private:
	Pixel determinePixelColor(Complex);
	void makeNewtonFractal();
};