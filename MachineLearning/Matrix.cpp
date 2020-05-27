#include "Matrix.h"
#include <time.h>
#include <random>
#include <iostream>

using namespace std;

Matrix::Matrix(int numRows, int numCols, bool isRandom)
{
	this->numRows = numRows;
	this->numCols = numCols;
	
	for (int i = 0; i < numRows; i++)
	{
		vector<double> colValues;

		for (int j = 0; j < numCols; j++)
		{
			double r = 0.0;
			if (isRandom)
			{
				r = this->getRandomNumber();
			}

			colValues.push_back(r);
		}
		this->values.push_back(colValues);
	}
}

Matrix* Matrix::transpose()
{
	Matrix* mT = new Matrix(this->numCols, this->numRows, false);
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			mT->setValue(j, i, this->getValue(i, j));
		}
	}
	return mT;
}

void Matrix::printToConsole()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			cout << this->values.at(i).at(j) << "\t\t";
		}
		cout << endl;
	}
}

void Matrix::setValue(int r, int c, double v)
{
	this->values.at(r).at(c) = v;
}

double Matrix::getValue(int r, int c)
{
	return this->values.at(r).at(c);
}

double Matrix::getRandomNumber()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}
