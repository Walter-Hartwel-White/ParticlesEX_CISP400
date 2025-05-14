#include "Matrices.h"
#include <iomanip>
#include <cmath>
using namespace Matrices;

Matrix::Matrix(int _rows, int _cols) {
	rows = _rows;
	cols = _cols;
	a.resize(rows);

	for (int i = 0; i < rows; i++) {
		a.at(i).resize(cols);
	}
}

Matrix Matrices::operator+(const Matrix& a, const Matrix& b) {
	Matrix output(a.getRows(), a.getCols());

	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		throw runtime_error("Error: dimensions must agree");
	} 

	for (int i = 0; i < a.getRows(); i++) {
		for (int j = 0; j < a.getCols(); j++) {
			output(i, j) = a(i, j) + b(i, j);
		}
	}

	return output;
} 

Matrix Matrices::operator*(const Matrix& a, const Matrix& b) {
	Matrix c(a.getRows(), b.getCols());
	double sum = 0.0;

	if (a.getCols() != b.getRows()) {
		throw runtime_error("Error: dimensions must agree");
	}

	for (int k = 0; k < b.getCols(); k++) {
		for (int i = 0; i < a.getRows(); i++) {
			sum = 0.0;
			for (int j = 0; j < a.getCols(); j++) {
				sum += a(i, j) * b(j, k);
			}
			c(i, k) = sum;
		}
	}

	return c;
} 

bool Matrices::operator==(const Matrix& a, const Matrix& b) {
	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		return false;
	}

	for (int i = 0; i < a.getRows(); i++) {
		for (int j = 0; j < a.getCols(); j++) {
			if (abs(a(i, j) - b(i, j)) > 0.001) {
				return false;
			}
		}
	}

	return true;
}

bool Matrices::operator!=(const Matrix& a, const Matrix& b) {
	if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
		return true;
	}

	for (int i = 0; i < a.getRows(); i++) {
		for (int j = 0; j < a.getCols(); j++) {
			if (abs(a(i, j) - b(i, j)) > 0.001) {
				return true;
			}
		}
	}

	return false;
}

ostream& Matrices::operator<<(ostream& os, const Matrix& a) {
	for (int i = 0; i < a.getRows(); i++) {
		for (int j = 0; j < a.getCols(); j++) {
			os << setw(10);
			os << a(i, j) << ' ';
		}
		os << '\n';
	}

	return os;
}

RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
	a.at(0).at(0) = cos(theta);
	a.at(0).at(1) = -sin(theta);
	a.at(1).at(0) = sin(theta);
	a.at(1).at(1) = cos(theta);
}

ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) { 
	a.at(0).at(0) = scale;
	a.at(0).at(1) = 0;
	a.at(1).at(0) = 0;
	a.at(1).at(1) = scale;
}

TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) { 
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < nCols; j++) {
			if (i == 0) {
				a.at(i).at(j) = xShift;
			}
			else {
				a.at(i).at(j) = yShift;
			}
		}
	}
}