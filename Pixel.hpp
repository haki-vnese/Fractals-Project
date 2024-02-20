#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Pixel
{
private:
	unsigned int red, green, blue;
public:
	~Pixel();
	Pixel();
	Pixel(const Pixel&);
	Pixel(unsigned int, unsigned int, unsigned int);
	const unsigned int& operator[](const char*) const;
	friend ofstream& operator<<(ofstream&, const Pixel&);
public:
	class InputOutOfBoundsException
	{
	private:
		const char* errorMessage;
		const char* offendingIndex;
	public:
		InputOutOfBoundsException(const char*, const char*);
		const char* returnError() const;
		const char* returnOffendingIndex() const;
	};
};
