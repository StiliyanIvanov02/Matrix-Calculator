/**
*
* Solution to course project # 11
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Stiliyan Ivanov
* @idnumber 7MI0600083
* @compiler VC
*
* <source file with the supported matrix operations>
*
*/

#include <iostream>
#include "MatrixOperations.h"
#include "HelperFunctions.h"

using namespace std;

// returns the sum of two given matrices with the same dimensions
double** calculateMatrixSum(double** matrix1, double** matrix2, int rows, int columns) {
	double** matrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}

	return matrix;
}

// returns the multiplication of a matrix and scalar
double** calculateMultiplicationByScalar(double** matrix, int rows, int columns, double scalar) {
	double** multipliedMatrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		multipliedMatrix[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			multipliedMatrix[i][j] = matrix[i][j] * scalar;
		}
	}

	return multipliedMatrix;
}

// returns the division of a matrix by a scalar
double** calculateDivisionByScalar(double** matrix, int rows, int columns, double scalar) {
	double** dividedMatrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		dividedMatrix[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			dividedMatrix[i][j] = matrix[i][j] / scalar;
		}
	}

	return dividedMatrix;
}

// returns the multiplication of two matrices
double** calculateMatrixMultiplication(double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2) {
	double** matrix = new double* [rows1];
	for (int i = 0; i < rows1; i++) {
		matrix[i] = new double[columns2];
	}

	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns2; j++) {
			double rowByColumn = 0;
			for (int k = 0; k < columns1; k++) {
				rowByColumn += matrix1[i][k] * matrix2[k][j];
			}
			matrix[i][j] = rowByColumn;
		}
	}

	return matrix;
}

// returns the determinant of a square matrix
double calculateDeterminant(double** matrix, int rows) {
	// base case
	if (rows == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		// use cofactor expansion
		double determinant = 0;
		for (int i = 0; i < rows; i++) {
			double** A = new double* [rows - 1];
			for (int j = 0; j < rows - 1; j++) {
				A[j] = new double[rows - 1];
			}

			for (int k = 1; k < rows; k++) {
				int index = 0;
				for (int m = 0; m < rows; m++) {
					if (m != i) {
						A[k - 1][index] = matrix[k][m];
						index++;
					}
				}
			}

			if ((1 + (i + 1)) % 2 == 0) {
				determinant += matrix[0][i] * calculateDeterminant(A, rows - 1);
			}
			else {
				determinant -= matrix[0][i] * calculateDeterminant(A, rows - 1);
			}

			FreeDynamicMemory(A, rows - 1);
		}

		return determinant;
	}
}

// returns the transposed matrix of a given one
double** calculateTransposedMatrix(double** matrix, int rows, int columns) {
	double** transposedMatrix = new double* [columns];
	for (int i = 0; i < columns; i++) {
		transposedMatrix[i] = new double[rows];
	}

	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			transposedMatrix[i][j] = matrix[j][i];
		}
	}

	return transposedMatrix;
}

// returns the inverse matrix of a given square one
double** calculateInverseMatrix(double** matrix, int rows, bool& isDeterminantZero) {
	double determinant = calculateDeterminant(matrix, rows);

	double** cofactorMatrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		cofactorMatrix[i] = new double[rows];
	}

	if (determinant == 0) {
		cout << "Cannot execute the operation. The determinant of the matrix should not be equal to zero." << endl;
		// stops the calculation and signals that it is impossible to continue
		isDeterminantZero = true;
		return cofactorMatrix;
	}

	// find the cofactor matrix
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			double** A = new double* [rows - 1];
			for (int k = 0; k < rows - 1; k++) {
				A[k] = new double[rows - 1];
			}

			int index1 = 0, index2 = 0;

			for (int m = 0; m < rows; m++) {
				if (m != i) {
					for (int n = 0; n < rows; n++) {
						if (n != j) {
							A[index1][index2] = matrix[m][n];
							index2++;
						}
					}
					index1++;
					index2 = 0;
				}
			}

			cofactorMatrix[i][j] = calculateDeterminant(A, rows - 1);
			for (int k = 1; k <= ((i + 1) + (j + 1)); k++) {
				cofactorMatrix[i][j] *= -1;
			}

			FreeDynamicMemory(A, rows - 1);
		}
	}

	// transpose the cofactor matrix
	double** adjugateMatrix = calculateTransposedMatrix(cofactorMatrix, rows, rows);

	FreeDynamicMemory(cofactorMatrix, rows);

	// divide by the determinant
	double** inverseMatrix = calculateDivisionByScalar(adjugateMatrix, rows, rows, determinant);

	FreeDynamicMemory(adjugateMatrix, rows);

	return inverseMatrix;
}

// returns the given matrix raised to a given power
double** calculateMatrixRaisedToPower(double** matrix, int rows, int power, bool& isDeterminantZero) {
	double** raisedMatrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		raisedMatrix[i] = new double[rows];
	}

	if (power == 0) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < rows; j++) {
				if (i == j) {
					raisedMatrix[i][j] = 1;
				}
				else {
					raisedMatrix[i][j] = 0;
				}
			}
		}
	}
	else if (power >= 1) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < rows; j++) {
				raisedMatrix[i][j] = matrix[i][j];
			}
		}

		for (int k = 2; k <= power; k++) {
			double** raisedMatrixHigher = calculateMatrixMultiplication(raisedMatrix, matrix, rows, rows, rows, rows);

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < rows; j++) {
					raisedMatrix[i][j] = raisedMatrixHigher[i][j];
				}
			}

			FreeDynamicMemory(raisedMatrixHigher, rows);
		}
	}
	// the negative powers are the inverse matrix multiplied by itself
	else if (power < 0) {
		double** inverseMatrix = calculateInverseMatrix(matrix, rows, isDeterminantZero);

		// proceeds only if the original matrix is reversible
		if (!isDeterminantZero) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < rows; j++) {
					raisedMatrix[i][j] = inverseMatrix[i][j];
				}
			}

			for (int k = -2; k >= power; k--) {
				double** raisedMatrixLower = calculateMatrixMultiplication(raisedMatrix, inverseMatrix, rows, rows, rows, rows);

				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < rows; j++) {
						raisedMatrix[i][j] = raisedMatrixLower[i][j];
					}
				}

				FreeDynamicMemory(raisedMatrixLower, rows);
			}
		}
	}

	return raisedMatrix;
}