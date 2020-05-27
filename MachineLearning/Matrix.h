#pragma once
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
using namespace std;

class Matrix
{
public:
	Matrix(int numRows, int numCols, bool isRandom);

	Matrix* transpose();

	void printToConsole();

	// Setters
	void setValue(int r, int c, double v);

	// Getters
	double getValue(int r, int c);
	int getNumRows() { return this->numRows; }
	int getNumCols() { return this->numCols; }



private:
	int numRows;
	int numCols;

	double getRandomNumber();

	vector<vector<double>> values;
};

#endif // !_MATRIX_HPP_
