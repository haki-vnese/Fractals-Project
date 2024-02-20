#include "Pixel.hpp"

Pixel::~Pixel()
{
	cout << "> Destructor called..." << endl;
}

Pixel::Pixel() : red(0), green(0), blue(0)
{
	cout << "> Default constructor called..." << endl;
}

Pixel::Pixel(const Pixel& p) : red(p.red), green(p.green), blue(p.blue)
{
	cout << "> Copy constructor called..." << endl;
}

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b) : red(r), green(g), blue(b)
{
	cout << "> Three-arg constructor called..." << endl;
}

const unsigned int& Pixel::operator[](const char* color) const
{
	if (strcmp(color, "red") == 0) return this->red;
	else if (strcmp(color, "green") == 0) return this->green;
	else if (strcmp(color, "blue") == 0) return this->blue;
	else throw InputOutOfBoundsException("Invalid input", color);
}

Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* errorMsg, const char* offIndexMsg)
{
	errorMessage = errorMsg;
	offendingIndex = offIndexMsg;
}
const char* Pixel::InputOutOfBoundsException::returnError() const
{
	return errorMessage;
}

const char* Pixel::InputOutOfBoundsException::returnOffendingIndex() const
{
	return offendingIndex;
}

ofstream& operator<<(ofstream& os, const Pixel& p)
{
	try
	{
		os << p["red"] << ' ' << p["green"] << ' ' << p["blue"] << endl;
		return os;
	}
	catch (const Pixel::InputOutOfBoundsException& e)
	{
		os << "Exception: " << e.returnError() << endl;
		os << "Exception: " << e.returnOffendingIndex() << endl;
		return os;
	}
}
