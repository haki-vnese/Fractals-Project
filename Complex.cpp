#include "Complex.hpp"

Complex::~Complex()
{
	// leaving blank
}

Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex(const Complex& c) : real(c.real), imag(c.imag) {}

Complex::Complex(double r) : real(r), imag(0.0) {}

Complex::Complex(double r, double i) : real(r), imag(i) {}

double& Complex::operator[](const char* msg)
{
	if (strcmp(msg, "real") == 0) return real;
	else if (strcmp(msg, "imag") == 0) return imag;
	else throw InputOutOfBoundsException("Invalid index", msg);
}

const Complex operator*(const Complex& c1, const Complex& c2)
{
	return (c1.real * c2.real - c1.imag * c2.imag, c1.real * c2.imag + c1.imag * c2.real);
}

const Complex operator/(const Complex& c1, const Complex& c2)
{
	double denominator = pow(c2.real, 2) + pow(c2.imag, 2);
	return Complex((c1.real * c2.real + c1.imag * c2.imag) / denominator, (c1.imag * c2.real - c1.real * c2.imag) / denominator);
}

const Complex operator+(const Complex& c1, const Complex& c2)
{
	return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

const Complex operator-(const Complex& c1, const Complex& c2)
{
	return Complex(c1.real - c2.real, c1.imag - c2.imag);
}

double getMagnitude(const Complex& c)
{
	return sqrt(pow(c.real, 2) + pow(c.imag, 2));
}

Complex::InputOutOfBoundsException::InputOutOfBoundsException(const char* errorMsg, const char* offIndexMsg)
{
	errorMessage = errorMsg;
	offendingIndex = offIndexMsg;
}
const char* Complex::InputOutOfBoundsException::returnError()
{
	return errorMessage;
}

const char* Complex::InputOutOfBoundsException::returnOffendingIndex()
{
	return offendingIndex;
}