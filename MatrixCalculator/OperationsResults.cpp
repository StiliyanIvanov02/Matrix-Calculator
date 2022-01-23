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
* <source file with functions checking, executing and delivering the results of the matrix operations>
*
*/

#include <iostream>
#include "MatrixOperations.h"
#include "HelperFunctions.h"

using namespace std;

void sumMatrices (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool resultSaved) {
	//checks if the operation is possible
	if (rows1 != rows2 || columns1 != columns2) {
		cout << "Cannot execute the operation. The dimensions of the two matrices should be the same in order for them to be summed." << endl;
		return;
	}

	double** matrix = calculateMatrixSum(matrix1, matrix2, rows1, columns1);

	// prints the operation
	for (int i = 0; i < rows1; i++) {
		printMatrixRow(matrix1, i, columns1);

		if (i == rows1 / 2) {
			cout << " + ";
		}
		else {
			cout << "   ";
		}

		printMatrixRow(matrix2, i, columns1);

		if (i == rows1 / 2) {
			cout << " = ";
		}
		else {
			cout << "   ";
		}

		printMatrixRow(matrix, i, columns1);

		cout << endl;
	}
	cout << endl;

	// saves result if wanted
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(matrix, rows1, columns1, filename);
		delete[] filename;
	}

	FreeDynamicMemory(matrix1, rows1);
	FreeDynamicMemory(matrix2, rows1);
	FreeDynamicMemory(matrix, rows1);
}

void multiplyByScalar (double** matrix, int rows, int columns, double scalar, bool resultSaved) {
	double** multipliedMatrix = calculateMultiplicationByScalar(matrix, rows, columns, scalar);

	// prints the operation
	for (int i = 0; i < rows; i++) {
		printMatrixRow(matrix, i, columns);

		if (i == rows / 2) {
			cout << " *  " << scalar << "  = ";
		}
		else {
			cout << "    ";
			for (int s = 0; s < numberSymbolsNumber(scalar); s++) {
				cout << " ";
			}
			cout << "    ";
		}

		printMatrixRow(multipliedMatrix, i, columns);

		cout << endl;
	}
	cout << endl;

	// saves result if wanted
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(multipliedMatrix, rows, columns, filename);
		delete filename;
	}

	FreeDynamicMemory(matrix, rows);
	FreeDynamicMemory(multipliedMatrix, rows);
}

void divideByScalar (double** matrix, int rows, int columns, double scalar, bool resultSaved) {
	double** dividedMatrix = calculateDivisionByScalar(matrix, rows, columns, scalar);

	// prints the operation
	for (int i = 0; i < rows; i++) {
		printMatrixRow(matrix, i, columns);

		if (i == rows / 2) {
			cout << " /  " << scalar << "  = ";
		}
		else {
			cout << "    ";
			for (int s = 0; s < numberSymbolsNumber(scalar); s++) {
				cout << " ";
			}
			cout << "    ";
		}

		printMatrixRow(dividedMatrix, i, columns);

		cout << endl;
	}
	cout << endl;

	// saves result if wanted
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(dividedMatrix, rows, columns, filename);
		delete filename;
	}

	FreeDynamicMemory(matrix, rows);
	FreeDynamicMemory(dividedMatrix, rows);
};

void multiplyMatrixByMatrix (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool resultSaved) {
	//checks if the operation is possible
	if (columns1 != rows2) {
		cout << "Cannot execute the operation. The number of rows of the second matrix should be the same as the number of columns of the first one in order for them to be multiplied." << endl;
		return;
	}

	double** matrix = calculateMatrixMultiplication(matrix1, matrix2, rows1, columns1, rows2, columns2);

	// prints the operation
	int rows;
	if (rows1 >= rows2) {
		rows = rows1;
	}
	else {
		rows = rows2;
	}

	for (int i = 0; i < rows; i++) {
		if (i >= rows1) {
			for (int j = 0; j < numberSymbolsMatrixRow(columns1); j++) {
				cout << " ";
			}
		}
		else {
			printMatrixRow(matrix1, i, columns1);
		}

		if (i == rows1 / 2) {
			cout << " * ";
		}
		else {
			cout << "   ";
		}

		if (i >= rows2) {
			for (int j = 0; j < numberSymbolsMatrixRow(columns2); j++) {
				cout << " ";
			}
		}
		else {
			printMatrixRow(matrix2, i, columns2);
		}

		if (i == rows1 / 2) {
			cout << " = ";
		}
		else {
			cout << "   ";
		}

		if (i >= rows1) {
			for (int j = 0; j < numberSymbolsMatrixRow(columns2); j++) {
				cout << " ";
			}
		}
		else {
			printMatrixRow(matrix, i, columns2);
		}

		cout << endl;
	}
	cout << endl;

	// saves result if wanted
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(matrix, rows1, columns2, filename);
		delete filename;
	}

	FreeDynamicMemory(matrix1, rows1);
	FreeDynamicMemory(matrix2, rows2);
	FreeDynamicMemory(matrix, rows1);
}

void raiseMatrixToPower(double** matrix, int rows, int columns, int power, bool resultSaved) {
	//checks if the operation is possible
	if (rows != columns) {
		cout << "Cannot execute the operation. You cannot raise to a power a non square matrix." << endl;
		return;
	}

	bool isDeterminantInverseZero = false;

	double** raisedMatrix = calculateMatrixRaisedToPower(matrix, rows, power, isDeterminantInverseZero);

	// continues if the determinant is not equal to zero
	if (!isDeterminantInverseZero) {
		// prints the operation
		for (int i = 0; i < rows; i++) {
			printMatrixRow(matrix, i, rows);

			if (i == 0) {
				cout << power << "    ";
			}
			else if (i == rows / 2) {
				cout << " ";
				for (int i = 0; i < numberSymbolsNumber(power); i++) {
					cout << " ";
				}
				cout << " = ";
			}
			else {
				for (int i = 0; i < numberSymbolsNumber(power) + 4; i++) {
					cout << " ";
				}
			}

			printMatrixRow(raisedMatrix, i, rows);

			cout << endl;
		}
		cout << endl;

		// saves result if wanted
		if (resultSaved == true) {
			char* filename = generateNameMatrixFilePath();
			saveMatrix(raisedMatrix, rows, rows, filename);
			delete filename;
		}
	}

	FreeDynamicMemory(matrix, rows);
	FreeDynamicMemory(raisedMatrix, rows);
}

void findDeterminant(double** matrix, int rows, int columns) {
	//checks if the operation is possible
	if (rows != columns) {
		cout << "Cannot execute the operation. You can find the determinant only of a square matrix." << endl;
		return;
	}
	else if (rows > MAX_NUMBER_ELEMENTS_IN_ROW_DETERMINANT) {
		cout << "Cannot execute the operation. This program cannot find the determinant of a matrix larger than 4 X 4." << endl;
		return;
	}

	double determinant = calculateDeterminant(matrix, rows);

	// prints the operation
	for (int i = 0; i < rows; i++) {
		if (i == rows / 2) {
			cout << " det ";
		}
		else {
			cout << "     ";
		}

		printMatrixRow(matrix, i, rows);

		if (i == rows / 2) {
			cout << " = " << determinant;
		}

		cout << endl;
	}
	cout << endl;

	FreeDynamicMemory(matrix, rows);
}

void inverseMatrix(double** matrix, int rows, int columns, bool resultSaved) {
	//checks if the operation is possible
	if (rows != columns) {
		cout << "Cannot execute the operation. You can find the inverse only of a square matrix." << endl;
		return;
	}
	else if (rows > MAX_NUMBER_ELEMENTS_IN_ROW_DETERMINANT) {
		cout << "Cannot execute the operation. This program cannot find the inverse of a matrix larger than 4 X 4." << endl;
		return;
	}

	bool isDeterminantZero = false;

	double** inverseMatrix = calculateInverseMatrix(matrix, rows, isDeterminantZero);

	// continues if the determinant is not equal to zero
	if (!isDeterminantZero) {
		// prints the operation
		for (int i = 0; i < rows; i++) {
			printMatrixRow(matrix, i, rows);

			if (i == 0) {
				cout << "-1   ";
			}
			else if (i == rows / 2) {
				cout << "   = ";
			}
			else {
				cout << "     ";
			}

			printMatrixRow(inverseMatrix, i, rows);

			cout << endl;
		}
		cout << endl;

		// saves result if wanted
		if (resultSaved == true) {
			char* filename = generateNameMatrixFilePath();
			saveMatrix(inverseMatrix, rows, rows, filename);
			delete filename;
		}
	}

	FreeDynamicMemory(matrix, rows);
	FreeDynamicMemory(inverseMatrix, rows);
};

void transposeMatrix (double** matrix, int rows, int columns, bool resultSaved) {
	double** transposedMatrix = calculateTransposedMatrix(matrix, rows, columns);

	// prints the operation
	int rowsOutput = 0;
	if (rows >= columns) {
		rowsOutput = rows;
	}
	else {
		rowsOutput = columns;
	}

	for (int i = 0; i < rowsOutput; i++) {
		if (i >= rows) {
			for (int j = 0; j < numberSymbolsMatrixRow(columns); j++) {
				cout << " ";
			}
		}
		else {
			printMatrixRow(matrix, i, columns);
		}

		if (i == 0) {
			cout << "t   ";
		}
		else if (i == rows / 2) {
			cout << "  = ";
		}
		else {
			cout << "    ";
		}

		if (i >= columns) {
			for (int j = 0; j < numberSymbolsMatrixRow(rows); j++) {
				cout << " ";
			}
		}
		else {
			printMatrixRow(transposedMatrix, i, rows);
		}

		cout << endl;
	}
	cout << endl;

	// saves result if wanted
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(transposedMatrix, columns, rows, filename);
		delete filename;
	}

	FreeDynamicMemory(matrix, rows);
	FreeDynamicMemory(transposedMatrix, rows);
}

void matrixEquation (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool isLeft, bool resultSaved) {
	//checks if the operation is possible
	if (rows1 != columns1) {
		cout << "Cannot execute the operation. The first matrix should be a square matrix." << endl;
		return;
	}

	bool isDeterminantZero = false;

	double** inverseMatrix1 = calculateInverseMatrix(matrix1, rows1, isDeterminantZero);

	// continues if the determinant is not equal to zero
	if (!isDeterminantZero) {
		if (isLeft) {
			if (columns2 != rows1) {
				cout << "Cannot execute the operation. The two given matrices are incompatible." << endl;
				return;
			}

			double** X = calculateMatrixMultiplication(matrix2, inverseMatrix1, rows2, columns2, rows1, columns1);

			// prints the operation
			int rows;
			if (rows1 >= rows2) {
				rows = rows1;
			}
			else {
				rows = rows2;
			}

			for (int i = 0; i < rows; i++) {
				if (i == rows / 2) {
					cout << " X  * ";
				}
				else {
					cout << "      ";
				}

				if (i >= rows1) {
					for (int j = 0; j < numberSymbolsMatrixRow(columns1); j++) {
						cout << " ";
					}
				}
				else {
					printMatrixRow(matrix1, i, columns1);
				}

				if (i == rows / 2) {
					cout << " = ";
				}
				else {
					cout << "   ";
				}

				if (i >= rows2) {
					for (int j = 0; j < numberSymbolsMatrixRow(columns2); j++) {
						cout << " ";
					}
				}
				else {
					printMatrixRow(matrix2, i, columns2);
				}

				cout << endl;
			}
			cout << endl;

			for (int j = 0; j < rows1; j++) {
				if (j == rows1 / 2) {
					cout << " X  = ";
				}
				else {
					cout << "      ";
				}

				printMatrixRow(X, j, columns1);

				cout << endl;
			}

			cout << endl;

			// saves result if wanted
			if (resultSaved == true) {
				char* filename = generateNameMatrixFilePath();
				saveMatrix(X, rows2, columns1, filename);
				delete filename;
			}

			for (int i = 0; i < rows2; i++) {
				delete[] X[i];
			}
			delete[] X;
		}
		else {
			if (columns1 != rows2) {
				cout << "Cannot execute the operation. The two given matrices are incompatible." << endl;
				return;
			}

			double** X = calculateMatrixMultiplication(inverseMatrix1, matrix2, rows1, columns1, rows2, columns2);

			// prints the operation
			int rows;
			if (rows1 >= rows2) {
				rows = rows1;
			}
			else {
				rows = rows2;
			}

			for (int i = 0; i < rows; i++) {
				if (i >= rows1) {
					for (int j = 0; j < numberSymbolsMatrixRow(columns1); j++) {
						cout << " ";
					}
				}
				else {
					printMatrixRow(matrix1, i, columns1);
				}

				if (i == rows / 2) {
					cout << " *  X  = ";
				}
				else {
					cout << "         ";
				}

				if (i >= rows2) {
					for (int j = 0; j < numberSymbolsMatrixRow(columns2); j++) {
						cout << " ";
					}
				}
				else {
					printMatrixRow(matrix2, i, columns2);
				}

				cout << endl;
			}
			cout << endl;

			for (int j = 0; j < rows2; j++) {
				if (j == rows2 / 2) {
					cout << " X  = ";
				}
				else {
					cout << "      ";
				}

				printMatrixRow(X, j, columns2);

				cout << endl;
			}

			cout << endl;

			// saves result if wanted
			if (resultSaved == true) {
				char* filename = generateNameMatrixFilePath();
				saveMatrix(X, rows2, columns1, filename);
				delete filename;
			}

			FreeDynamicMemory(X, rows1);
		}
	}

	FreeDynamicMemory(inverseMatrix1, rows1);
}