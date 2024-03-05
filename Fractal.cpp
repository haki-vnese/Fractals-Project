#pragma once
#include "Fractal.hpp"

const unsigned int Fractal::maxIter = 30;

Fractal::Fractal() : cols(0), rows(0), grid(nullptr)
{
	cout << "> Default constructor called..." << endl;
}

Fractal::Fractal(const Fractal& f) : cols(f.cols), rows(f.rows)
{
	if (cols == 0 || rows == 0)
		this->grid = nullptr;
		
	else
	{
		cout << "> Copy constructor called..." << endl;
		this->grid = new Pixel * [cols];
		for (unsigned int i = 0; i < cols; i++)
		{
			this->grid[i] = new Pixel[rows];
			for (unsigned int j = 0; j < rows; j++)
				this->grid[i][j] = f.grid[i][j];
		}
	}
}

Fractal::Fractal(Fractal&& f) : cols(f.cols), rows(f.rows), grid(f.grid)
{
	cout << "> Move constructor called..." << endl;
	f.cols = 0;
	f.rows = 0;
	f.grid = nullptr;
}

Fractal::Fractal(unsigned int colsValue, unsigned int rowsValue) : cols(colsValue), rows(rowsValue)
{
	if (cols == 0 || rows == 0)
		this->grid = nullptr;
	
	else
	{
		cout << "> Two-arg constructor called..." << endl;
		this->grid = new Pixel * [cols];
		for (unsigned int i = 0; i < cols; i++)
			this->grid[i] = new Pixel[rows];
		// Generate the Newton fractal
		makeNewtonFractal();
	}
}

Fractal::~Fractal()
{
	cout << "> Destructor called..." << endl;
	if (this->grid != nullptr)
	{
		for (unsigned int i = 0; i < cols; i++)
			delete[] this->grid[i];
		delete[] this->grid;
	}
}

const Fractal& Fractal::operator=(const Fractal& f)
{
	if (this != &f)
	{
		if (this->grid != nullptr)
		{
			for (unsigned int i = 0; i < rows; i++)
				delete[] this->grid[i];
			delete[] this->grid;
		}
		this->cols = f.cols;
		this->rows = f.rows;
		this->grid = new Pixel * [rows];
		for (unsigned int i = 0; i < rows; i++)
		{
			this->grid[i] = new Pixel[cols];
			for (unsigned int j = 0; j < cols; j++)
				this->grid[i][j] = f.grid[i][j];
		}
	}
	return (*this);
}

Fractal& Fractal::operator=(Fractal&& f)
{
	cout << "> Move assignment operator called..." << endl;
	if (this != &f)
	{
		swap(this->grid, f.grid);
		swap(this->cols, f.cols);
		swap(this->rows, f.rows);
	}
	return (*this);
}


Pixel Fractal::determinePixelColor(Complex Z)
{
	const double tol = 1E-4;
	const double test = 0.58974;
	
	unsigned int iter = 0;
	int color = 0;
	double diff = 1.0;
	Complex Znew;

	while (iter < 512) 
	{
		iter++;
		Znew = Z - ((Z * Z * Z) - (2.0 * Z) + 2.0) / ((3.0 * Z * Z) - 2.0);
		diff = getMagnitude(Z - Znew);
		Z = Znew;

		if (diff < tol)
		{
			color = 512 - min(iter, maxIter);
			if (abs(Z["imag"]) < tol)
				return Pixel(color, color, 0);
			else if ((abs(Z["imag"]) - test) < tol)
				return Pixel(0, color, color);
			else if ((abs(Z["imag"]) + test) < tol)
				return Pixel(color, 0, color);
		}
	}
	return Pixel(0, 0, 0);
}

void Fractal::makeNewtonFractal()
{
	cout << "> Now creating the Newton Fractal..." << endl;
	Complex Z;
	double step_height = 4.0 / rows;
	double step_width = 4.0 / cols;
	for (unsigned int j = 0; j < rows; j++)
	{
		cout << j + 1 << " " << endl;
		for (unsigned int k = 0; k < cols; k++)
		{
			Z["imag"] = 2.0 - (j * step_height);
			Z["real"] = (k * step_width) - 2.0;
			this->grid[j][k] = determinePixelColor(Z);
		}
	}
}

void saveToPPM(const Fractal& fractal, const string& name)
{
	ofstream output(name);
	if (!output)
	{
		cerr << "Error: Unable to create output file" << endl;
		return;
	}
	cout << "> Saving Fractal to PPM file..." << endl;
	output << "P3" << endl;
	output << fractal.rows << " " << fractal.cols << endl;
	output << "255" << endl;

	for (unsigned int i = 0; i < fractal.rows; i++)
	{
		for (unsigned int j = 0; j < fractal.cols; j++)
		{
			output << fractal.grid[i][j];
		}
	}
	output.close();
}
