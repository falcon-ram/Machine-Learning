#pragma once
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <assert.h>
using namespace std;

class Matrix
{
public:
	Matrix(int numRows, int numCols, bool isRandom);

	void printToConsole();

	// Setters
	void setValue(int r, int c, double v);

	// Getters
	double getValue(int r, int c) const;
	int getNumRows() const { return this->numRows; }
	int getNumCols() const { return this->numCols; }

	// Matrix Maths
	Matrix operator-(const Matrix b);
	Matrix* transpose();


private:
	int numRows;
	int numCols;

	double getRandomNumber();

	vector<vector<double>> values;
};

#endif // !_MATRIX_HPP_
