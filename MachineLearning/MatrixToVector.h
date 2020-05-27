#pragma once
#ifndef _MATRIX_TO_VECTOR_H_
#define _MATRIX_TO_VECTOR_H_

#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std;

namespace utils
{
	class MatrixToVector
	{
	public:
		MatrixToVector(Matrix* a);

		vector<double> execute();

	private:
		Matrix* a;
	};
}

#endif // !_MATRIX_TO_VECTOR_H_



