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

double Matrix::getValue(int r, int c) const
{
	return this->values.at(r).at(c);
}

Matrix Matrix::operator-(const Matrix b)
{
	Matrix* result = new Matrix(this->numRows, this->numCols, false);
	if ((this->numCols != b.numCols) || (this->numRows != b.numRows))
	{
		cerr << "Matrices are not the same size\n";
		assert(false);
	}
	double resVal = 0.0;
	for (int i = 0; i < this->numRows; i++)
	{
		for (int j = 0; j < this->numCols; j++)
		{
			resVal = this->getValue(i, j) - b.getValue(i, j);
			result->setValue(i, j, resVal);
		}

	}
	return *result;
}

double Matrix::getRandomNumber()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}
