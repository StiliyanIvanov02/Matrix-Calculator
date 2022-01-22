#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

const int NUMBER_OPERATIONS = 10;
const char* OPERATIONS[NUMBER_OPERATIONS] = {
	"Sum of two matrices",
	"Multiplication of matrix by scalar",
	"Division of matrix by scalar",
	"Multiplication of matrix by matrix",
	"Raising a matrix to a power",
	"Finding the determinant",
	"Finding the inverse matrix",
	"Transposition of matrix",
	"Matrix equation",
	"Exit"
};

const int MAX_NUMBER_CHARS_IN_ROW_FILE = 1024;
const int OUTPUT_FILE_PATH_LENGTH = 19;
const int INPUT_FILE_PATH_MAX_LENGTH = 200;
const char* FILE_PATH = "Matrices/00000.txt";

const int MAX_NUMBER_ELEMENTS_IN_ROW = 20;
const int MAX_NUMBER_ELEMENTS_IN_ROW_DETERMINANT = 4;

const int MAX_NUMBER_DIGITS = 6;

struct matrixData {
	int rows;
	int columns;
	double** elements;
};

bool saveResultAsFile () {
	char saved = ' ';
	while (saved != 'Y' && saved != 'N') {
		cout << "Do you want to save the result of the operation in a file?" << endl;
		cout << "Enter Y for yes or N for no: ";
		char saved;
		cin >> saved;
		if (saved == 'Y') {
			cout << endl;
			return true;
		}
		else if (saved == 'N') {
			cout << endl;
			return false;
		}
	}
}

matrixData readData (char path[]) {
	ifstream file;

	char* line = new char[MAX_NUMBER_CHARS_IN_ROW_FILE];

	double* elements = new double[MAX_NUMBER_ELEMENTS_IN_ROW*MAX_NUMBER_ELEMENTS_IN_ROW];
	int elementsCount = 0, linesCount = 0;

	file.open(path, std::ios::in);
	if (!file.is_open()) {
		cout << "There is no file with such a name" << endl;
	}
	else {
		while (!file.eof()) {
			file >> elements[elementsCount];
			elementsCount++;
		}
		file.clear();
		file.seekg(0, file.beg);
		while (!file.eof()) {
			file.getline(line, MAX_NUMBER_CHARS_IN_ROW_FILE);
			linesCount++;
		}
	}

	file.close();

	int rows = linesCount;
	int columns = elementsCount / rows;
	int index = 0;

	double** matrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = elements[index];
			index++;
		}
	}

	matrixData matrixData = { rows,columns,matrix };
	return matrixData;
}

char* generateNameMatrixFilePath() {
	char* output = new char[OUTPUT_FILE_PATH_LENGTH];
	for (int i = 0; i < OUTPUT_FILE_PATH_LENGTH; i++) {
		if (i >= 9 && i <= 13) {
			output[i] = (rand() % 10) + '0';
		}
		else {
			output[i] = FILE_PATH[i];
		}
	}

	return output;
}

int numberSymbolsNumber(double number) {
	int count = 0;

	if (number < 0) {
		count++;
	}

	if (number - (int)number <= 0.0001) {
		int numberInt = (int)number;
		while (numberInt != 0.0) {
			numberInt /= 10;
			count++;
		}
	}
	else {
		count = 1;
		while (number - (int)number > 0.0001) {
			number *= 10;
		}
		int numberInt = (int)number;
		while (numberInt != 0) {
			numberInt /= 10;
			count++;
		}
	}

	return count;
}

double roundNumber(double number) {
	int numberChars = numberSymbolsNumber(number);
	if (numberChars > MAX_NUMBER_DIGITS && number - (int)number > 0.0001) {
		int numberCharsIntPart = numberSymbolsNumber((int)number);
		int numberCharsToRoundUpTo = MAX_NUMBER_DIGITS - numberCharsIntPart - 1;
		for (int i = 0; i < numberCharsToRoundUpTo; i++) {
			number *= 10;
		}
		number = (int)number;
		for (int i = 0; i < numberCharsToRoundUpTo; i++) {
			number /= 10;
		}
	}

	return number;
}

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

double calculateDeterminant(double** matrix, int rows) {
	if (rows == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		double determinant = 0;
		for (int i = 0; i < rows; i++) {
			double** A = new double*[rows - 1];
			for (int j = 0; j < rows - 1; j++) {
				A[j] = new double[rows - 1];
			}

			for (int k = 1; k < rows; k++) {
				int index = 0;
				for (int m = 0; m < rows; m++) {
					if (m != i) {
						A[k-1][index] = matrix[k][m];
						index++;
					}
				}
			}

			if ((1 + (i + 1))% 2 == 0) {
				determinant += matrix[0][i] * calculateDeterminant(A, rows - 1);
			}
			else {
				determinant -= matrix[0][i] * calculateDeterminant(A, rows - 1);
			}

			for (int j = 0; j < rows - 1; j++) {
				delete A[j];
			}
			delete[] A;
		}

		return determinant;
	}
}

double** calculateTransposedMatrix (double** matrix, int rows, int columns) {
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

double** calculateInverseMatrix(double** matrix, int rows) {
	double determinant = calculateDeterminant(matrix, rows);

	if (determinant == 0) {
		cout << "Cannot execute the operation. The determinant of the matrix should not be equal to zero." << endl;
		exit;
	}

	double** cofactorMatrix = new double* [rows];
	for (int i = 0; i < rows; i++) {
		cofactorMatrix[i] = new double[rows];
	}

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

			for (int k = 0; k < rows - 1; k++) {
				delete A[k];
			}
			delete[] A;
		}
	}

	double** adjugateMatrix = calculateTransposedMatrix(cofactorMatrix, rows, rows);

	for (int i = 0; i < rows; i++) {
		delete cofactorMatrix[i];
	}
	delete[] cofactorMatrix;

	double** inverseMatrix = calculateDivisionByScalar (adjugateMatrix, rows, rows, determinant);

	for (int i = 0; i < rows; i++) {
		delete adjugateMatrix[i];
	}
	delete[] adjugateMatrix;

	return inverseMatrix;
}

double** calculateMatrixRaisedToPower(double** matrix, int rows, int power) {
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

			for (int i = 0; i < rows; i++) {
				delete[] raisedMatrixHigher[i];
			}
			delete[] raisedMatrixHigher;
		}
	}
	else if (power < 0) {
		double** inverseMatrix = calculateInverseMatrix(matrix, rows);

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

			for (int i = 0; i < rows; i++) {
				delete[] raisedMatrixLower[i];
			}
			delete[] raisedMatrixLower;
		}
	}

	return raisedMatrix;
}

int numberSymbolsMatrixRow(int numberElements) {
	int count = 6;

	for (int i = 0; i < numberElements; i++) {
		count += MAX_NUMBER_DIGITS + 1;
	}

	return count;
}

void printMatrixRow (double** matrix, int rowIndex, int columns) {
	cout << " | ";

	for (int i = 0; i < columns; i++) {
		cout << setw(MAX_NUMBER_DIGITS + 1) << roundNumber(matrix[rowIndex][i]);
	}

	cout << " | ";
}

void saveMatrix (double** matrix, int rows, int columns, char* filename) {
	ofstream file(filename);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			file << setw(6) << matrix[i][j];
		}
		if (i != rows - 1) {
			file << endl;
		}
	}
	file.close();

	cout << "Result saved at " << filename << endl;
}

void sumMatrices (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool resultSaved) {
	if (rows1 != rows2 || columns1 != columns2) {
		cout << "Cannot execute the operation. The dimensions of the two matrices should be the same in order for them to be summed." << endl;
		return;
	}

	double** matrix = calculateMatrixSum(matrix1, matrix2, rows1, columns1);

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

	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(matrix, rows1, columns1, filename);	
		delete[] filename;
	}

	for (int i = 0; i < rows1; i++) {
		delete matrix[i];
	}
	delete[] matrix;
}

void multiplyByScalar (double** matrix, int rows, int columns, double scalar, bool resultSaved) {
	double** multipliedMatrix = calculateMultiplicationByScalar(matrix, rows, columns, scalar);

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

	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(multipliedMatrix, rows, columns, filename);
		delete filename;
	}

	for (int i = 0; i < rows; i++) {
		delete multipliedMatrix[i];
	}
	delete[] multipliedMatrix;
}

void divideByScalar (double** matrix, int rows, int columns, double scalar, bool resultSaved) {
	double** dividedMatrix = calculateDivisionByScalar(matrix, rows, columns, scalar);

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
	
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(dividedMatrix, rows, columns, filename);
		delete filename;
	}

	for (int i = 0; i < rows; i++) {
		delete dividedMatrix[i];
	}
	delete[] dividedMatrix;
};

void multiplyMatrixByMatrix (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool resultSaved) {
	if (columns2 != rows1) {
		cout << "Cannot execute the operation. The number of rows of the second matrix should be the same as the number of columns of the first one in order for them to be multiplied." << endl;
		return;
	}

	double** matrix = calculateMatrixMultiplication(matrix1, matrix2, rows1, columns1, rows2, columns2);

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
			printMatrixRow(matrix, i, columns1);
		}

		cout << endl;
	}
	cout << endl;
	
	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(matrix, rows1, columns2, filename);
		delete filename;
	}

	for (int i = 0; i < rows1; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void raiseMatrixToPower(double** matrix, int rows, int columns, int power, bool resultSaved) {
	if (rows != columns) {
		cout << "Cannot execute the operation. You cannot raise to a power a non square matrix." << endl;
		return;
	}

	double** raisedMatrix = calculateMatrixRaisedToPower(matrix, rows, power);

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

	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(raisedMatrix, rows, rows, filename);
		delete filename;
	}

	for (int i = 0; i < rows; i++) {
		delete[] raisedMatrix[i];
	}
	delete[] raisedMatrix;
} 

void findDeterminant (double** matrix, int rows, int columns) {
	if (rows != columns) {
		cout << "Cannot execute the operation. You can find the determinant only of a square matrix." << endl;
		return;
	}
	else if (rows > MAX_NUMBER_ELEMENTS_IN_ROW_DETERMINANT) {
		cout << "Cannot execute the operation. This program cannot find the determinant of a matrix larger than 4 X 4." << endl;
		return;
	}

	double determinant = calculateDeterminant(matrix, rows);

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
}

void inverseMatrix(double** matrix, int rows, int columns, bool resultSaved) {
	if (rows != columns) {
		cout << "Cannot execute the operation. You can find the inverse only of a square matrix." << endl;
		return;
	}
	else if (rows > MAX_NUMBER_ELEMENTS_IN_ROW_DETERMINANT) {
		cout << "Cannot execute the operation. This program cannot find the inverse of a matrix larger than 4 X 4." << endl;
		return;
	}

	double** inverseMatrix = calculateInverseMatrix(matrix, rows);

	if (!isnan(inverseMatrix[0][0])) {
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

		if (resultSaved == true) {
			char* filename = generateNameMatrixFilePath();
			saveMatrix(inverseMatrix, rows, rows, filename);
			delete filename;
		}
	}

	for (int i = 0; i < rows; i++) {
		delete[] inverseMatrix[i];
	}
	delete[] inverseMatrix;
};

void transposeMatrix (double** matrix, int rows, int columns, bool resultSaved) {
	double** transposedMatrix = calculateTransposedMatrix(matrix, rows, columns);

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

	if (resultSaved == true) {
		char* filename = generateNameMatrixFilePath();
		saveMatrix(transposedMatrix, columns, rows, filename);
		delete filename;
	}

	for (int i = 0; i < columns; i++) {
		delete[] transposedMatrix[i];
	}
	delete[] transposedMatrix;
}

void matrixEquation(double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool isLeft, bool resultSaved) {
	if (rows1 != columns1) {
		cout << "Cannot execute the operation. The first matrix should be a square matrix." << endl;
		return;
	}

	double** inverseMatrix1 = calculateInverseMatrix(matrix1, rows1);

	if (!isnan(inverseMatrix1[0][0])) {
		if (isLeft) {
			if (columns2 != rows1) {
				cout << "Cannot execute the operation. The two given matrices are incompatible." << endl;
				return;
			}

			double** X = new double* [rows2];
			for (int i = 0; i < rows2; i++) {
				X[i] = new double[columns1];
			}

			X = calculateMatrixMultiplication(matrix2, inverseMatrix1, rows2, columns2, rows1, columns1);

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

				printMatrixRow(X, j, columns1);

				cout << endl;
			}

			cout << endl;

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

			double** X = new double* [rows1];
			for (int i = 0; i < rows1; i++) {
				X[i] = new double[columns2];
			}

			X = calculateMatrixMultiplication(inverseMatrix1, matrix2, rows1, columns1, rows2, columns2);

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

				printMatrixRow(X, j, columns2);

				cout << endl;
			}

			cout << endl;

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
	}
}

int main() {
	srand((unsigned)time(NULL));

	cout << "MATRIX CALCULATOR" << endl;
	cout << endl;

	cout << "Select one of the following operations:" << endl;
	for (int i = 0; i < NUMBER_OPERATIONS; i++) {
		cout << i + 1 << ". " << OPERATIONS[i] << endl;
	}
	cout << endl;

	int number = 0;

	while (number != NUMBER_OPERATIONS) {
		cout << "Enter the number of the selected operation: ";
		cin >> number;

		switch (number) {
			case 1: {
				cout << "Enter the path to the file containing the first matrix: ";
				char* file1 = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file1;
				cout << "Enter the path to the file containing the second matrix: ";
				char* file2 = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file2;

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData1 = readData(file1);
				double** matrix1 = matrixData1.elements;
				int rows1 = matrixData1.rows;
				int columns1 = matrixData1.columns;

				matrixData matrixData2 = readData(file2);
				double** matrix2 = matrixData2.elements;
				int rows2 = matrixData2.rows;
				int columns2 = matrixData2.columns;

				sumMatrices(matrix1, matrix2, rows1, columns1, rows2, columns2, saveResultFile);

				break;
			}
			case 2: {
				cout << "Enter the path to the file containing the matrix: ";
				char* file = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file;

				cout << "Enter the value of the scalar: ";
				double scalar;
				cin >> scalar;

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData = readData(file);
				double** matrix = matrixData.elements;
				int rows = matrixData.rows;
				int columns = matrixData.columns;

				multiplyByScalar(matrix, rows, columns, scalar, saveResultFile);

				break;
			}
			case 3: {
				cout << "Enter the path to the file containing the matrix: ";
				char* file = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file;

				cout << "Enter the value of the scalar: ";
				double scalar;
				cin >> scalar;

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData = readData(file);
				double** matrix = matrixData.elements;
				int rows = matrixData.rows;
				int columns = matrixData.columns;

				divideByScalar(matrix, rows, columns, scalar, saveResultFile);

				break;
			}
			case 4: {
				cout << "Enter the path to the file containing the first matrix: ";
				char* file1 = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file1;
				cout << "Enter the path to the file containing the second matrix: ";
				char* file2 = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file2;

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData1 = readData(file1);
				double** matrix1 = matrixData1.elements;
				int rows1 = matrixData1.rows;
				int columns1 = matrixData1.columns;

				matrixData matrixData2 = readData(file2);
				double** matrix2 = matrixData2.elements;
				int rows2 = matrixData2.rows;
				int columns2 = matrixData2.columns;

				multiplyMatrixByMatrix(matrix1, matrix2, rows1, columns1, rows2, columns2, saveResultFile);

				break;
			}
			case 5: {
				cout << "Enter the path to the file containing the matrix: ";
				char* file = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file;

				int power = -6;
				while (power < -5 || power > 5) {
					cout << "Enter the power to which the matrix will be raised (an integer between -5 and 5): ";
					cin >> power;
				}

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData = readData(file);
				double** matrix = matrixData.elements;
				int rows = matrixData.rows;
				int columns = matrixData.columns;

				raiseMatrixToPower(matrix, rows, columns, power, saveResultFile);
				break;
			}
			case 6: {
				cout << "Enter the path to the file containing the matrix: ";
				char* file = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file;

				matrixData matrixData = readData(file);
				double** matrix = matrixData.elements;
				int rows = matrixData.rows;
				int columns = matrixData.columns;

				findDeterminant(matrix, rows, columns);

				break;
			}
			case 7: {
				cout << "Enter the path to the file containing the matrix: ";
				char* file = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file;

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData = readData(file);
				double** matrix = matrixData.elements;
				int rows = matrixData.rows;
				int columns = matrixData.columns;

				inverseMatrix(matrix, rows, columns, saveResultFile);

				break;
			}
			case 8: {
				cout << "Enter the path to the file containing the matrix: ";
				char* file = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file;

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData = readData(file);
				double** matrix = matrixData.elements;
				int rows = matrixData.rows;
				int columns = matrixData.columns;

				transposeMatrix(matrix, rows, columns, saveResultFile);

				break;
			}
			case 9: {
				cout << "Enter the path to the file containing the first matrix: ";
				char* file1 = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file1;
				cout << "Enter the path to the file containing the second matrix: ";
				char* file2 = new char[INPUT_FILE_PATH_MAX_LENGTH];
				cin >> file2;

				char position = ' ';
				bool isLeft;
				while (position != 'L' && position != 'R') {
					cout << "Will the matrix X we want to obtain be the left multiplier (X*A=B) or the right multiplier (A*X=B)?" << endl;
					cout << "Enter L for left or R for right: ";
					char saved;
					cin >> saved;
					if (position == 'L') {
						isLeft = true;
					}
					else if (position == 'R') {
						isLeft = false;
					}
				}

				bool saveResultFile = saveResultAsFile();

				matrixData matrixData1 = readData(file1);
				double** matrix1 = matrixData1.elements;
				int rows1 = matrixData1.rows;
				int columns1 = matrixData1.columns;

				matrixData matrixData2 = readData(file2);
				double** matrix2 = matrixData2.elements;
				int rows2 = matrixData2.rows;
				int columns2 = matrixData2.columns;

				matrixEquation(matrix1, matrix2, rows1, columns1, rows2, columns2, isLeft, saveResultFile);

				break;
			}
			default: {
				break;
			}
		}
	}

	return 0;
}