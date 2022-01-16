#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

const int NUMBER_OPERATIONS = 9;

const char* OPERATIONS[NUMBER_OPERATIONS] = {
	"Sum of two matrices",
	"Multiplication of matrix by scalar",
	"Division of matrix by scalar",
	"Multiplication of matrix by matrix",
	"Finding the determinant",
	"Finding the inverse matrix",
	"Transposition of matrix",
	"Matrix equation",
	"Singular Value Decomposition"
};

const int MAX_NUMBER_DIGITS = 6;

const size_t MAX_NUMBER_ELEMENTS = 4;

bool SaveResultAsFile () {
	char saved = ' ';
	while (saved != 'Y' && saved != 'N') {
		cout << "Do you want to save the result of the operation in a file?" << endl;
		cout << "Enter Y for yes or N for no:";
		char saved;
		cin >> saved;
		if (saved == 'Y') {
			return true;
		}
		else if (saved == 'N') {
			return false;
		}
	}
}

int ReadData (char path[]) {
	ifstream file(path);

	if (!file.is_open()) {
		return 1;
	}
}

char* GenerateNameMatrixFilePath () {
	int random = ((double)rand() / (1));
	double code = random * 100000;

	//return "Matrices/" + char*(code);
	char* output = new char[1024];
	return output;
}

double** CalculateDivisionByScalar(double** matrix, int rows, int columns, double scalar) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] /= scalar;
		}
	}

	return matrix;
}

double** CalculateMatrixMultiplication(double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2) {
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

double CalculateDeterminant(double** matrix, int rows) {
	if (rows == 1) {
		return matrix[rows - 1][rows - 1];
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
				determinant += matrix[0][i] * CalculateDeterminant(A, rows - 1);
			}
			else {
				determinant -= matrix[0][i] * CalculateDeterminant(A, rows - 1);
			}

			delete[] A;
		}

		return determinant;
	}
}

double** CalculateTransposedMatrix (double** matrix, int rows, int columns) {
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

double** CalculateInverseMatrix(double** matrix, int rows) {
	double determinant = CalculateDeterminant(matrix, rows);

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
				for (int n = 0; n < rows; n++) {
					if (m != i || n != j) {
						A[index1][index2] = matrix[m][n];
						index2++;
					}
				}
				index1++;
			}

			cofactorMatrix[i][j] = CalculateDeterminant(A, rows - 1);

			delete[] A;
		}
	}

	double** adjugateMatrix = CalculateTransposedMatrix(cofactorMatrix, rows, rows);

	delete[] cofactorMatrix;

	double** inverseMatrix = CalculateDivisionByScalar (adjugateMatrix, rows, rows, determinant);

	delete[] adjugateMatrix;

	return inverseMatrix;
}

void SaveMatrix (double** matrix, int rows, int columns, char* filename) {
	ofstream file(filename);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			file << setw(6) << matrix[i][j];
		}
		file << endl;
	}
	file.close();

	cout << "Result saved at " << filename << endl;
}

void SumMatrices (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool resultSaved) {
	if (rows1 != rows2 || columns1 != columns2) {
		cout << "Cannot execute the operation. The dimensions of the two matrices should be the same in order for them to be summed." << endl;
		return;
	}

	double** matrix = new double* [rows1];
	for (int i = 0; i < rows1; i++) {
		matrix[i] = new double[columns1];
	}

	for (int i = 0; i < rows1; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns1; j++) {
			cout << setw(MAX_NUMBER_DIGITS+1) << matrix1[i][j];
		}
		cout << " ║ ";

		if (i == rows1 / 2) {
			cout << " + ";
		}
		else {
			cout << "   ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns1; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix2[i][j];
		}
		cout << " ║ ";

		if (i == rows1 / 2) {
			cout << " = ";
		}
		else {
			cout << "   ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns1; j++) {
			matrix[i][j] = matrix1[i][j] + matrix2[i][j];
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[i][j];
		}
		cout << " ║ ";

		cout << endl;
	}

	if (resultSaved == true) {
		char* filename = GenerateNameMatrixFilePath();
		SaveMatrix(matrix, rows1, columns1, filename);	
		delete[] filename;
	}

	delete[] matrix;
}

void MultiplyByScalar (double** matrix, int rows, int columns, int scalar, bool resultSaved) {
	for (int i = 0; i < rows; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[i][j];
		}
		cout << " ║ ";

		if (i == rows / 2) {
			cout << " *  " << scalar << "  = ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = matrix[i][j] * scalar;
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[i][j];
		}
		cout << " ║ ";

		cout << endl;
	}

	if (resultSaved == true) {
		char* filename = GenerateNameMatrixFilePath();
		SaveMatrix(matrix, rows, columns, filename);
		delete[] filename;
	}
}

void DivideByScalar (double** matrix, int rows, int columns, int scalar, bool resultSaved) {
	double** dividedMatrix = CalculateDivisionByScalar(matrix, rows, columns, scalar);

	for (int i = 0; i < rows; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[i][j];
		}
		cout << " ║ ";

		if (i == rows / 2) {
			cout << " *  " << scalar << "  = ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << dividedMatrix[i][j];
		}
		cout << " ║ ";

		cout << endl;
	}
	
	if (resultSaved == true) {
		char* filename = GenerateNameMatrixFilePath();
		SaveMatrix(matrix, rows, columns, filename);
		delete[] filename;
	}
};

void MultiplyMatrixByMatrix (double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool resultSaved) {
	if (columns2 != rows1) {
		cout << "Cannot execute the operation. The number of rows of the second matrix should be the same as the number of columns of the first one in order for them to be multiplied." << endl;
		return;
	}

	double** matrix = CalculateMatrixMultiplication(matrix1, matrix2, rows1, columns1, rows2, columns2);

	if (resultSaved == true) {
		char* filename = GenerateNameMatrixFilePath();
		SaveMatrix(matrix, rows1, columns2, filename);
		delete[] filename;
	}

	delete[] matrix;
}

void FindDeterminant(double** matrix, int rows, int columns) {
	if (rows != columns) {
		cout << "Cannot execute the operation. You can find the determinant only of a square matrix." << endl;
		return;
	}
	else if (rows > 4) {
		cout << "Cannot execute the operation. This program cannot find the determinant of a matrix larger than 4 X 4." << endl;
		return;
	}

	double determinant = CalculateDeterminant(matrix, rows);

	for (int i = 0; i < rows; i++) {
		if (i == rows / 2) {
			cout << " det " << endl;
		}

		cout << " ║ ";
		
		for (int j = 0; j < rows; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[i][j];
		}

		cout << " ║ ";

		if (i == rows / 2) {
			cout << " = " << determinant << endl;
		}
	}
}

void InverseMatrix(double** matrix, int rows, int columns, bool resultSaved) {
	if (rows != columns) {
		cout << "Cannot execute the operation. You can find the inverse only of a square matrix." << endl;
		return;
	}
	else if (rows > 4) {
		cout << "Cannot execute the operation. This program cannot find the inverse of a matrix larger than 4 X 4." << endl;
		return;
	}

	double** inverseMatrix = CalculateInverseMatrix(matrix, rows);

	if (resultSaved == true) {
		char* filename = GenerateNameMatrixFilePath();
		SaveMatrix(inverseMatrix, rows, rows, filename);
	}

	delete[] inverseMatrix;
};

void TransposeMatrix (double** matrix, int rows, int columns, bool resultSaved) {
	double** transposedMatrix = CalculateTransposedMatrix(matrix, rows, columns);

	for (int i = 0; i < rows; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[i][j];
		}
		cout << " ║ ";

		if (i == 0) {
			cout << " t ";
		}

		if (i == rows / 2) {
			cout << " = ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(MAX_NUMBER_DIGITS + 1) << matrix[j][i];
		}
		cout << " ║ ";

		cout << endl;
	}

	if (resultSaved == true) {
		char* filename = GenerateNameMatrixFilePath();
		SaveMatrix(transposedMatrix, columns, rows, filename);
		delete[] filename;
	}

	delete[] transposedMatrix;
}

void MatrixEquation(double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2, bool isLeft, bool resultSaved) {
	if (rows1 != columns1) {
		cout << "Cannot execute the operation. The first matrix should be a square matrix." << endl;
		return;
	}

	double** inverceMatrix1 = CalculateInverseMatrix(matrix1, rows1);

	if (isLeft) {
		if (columns2 != rows1) {
			cout << "Cannot execute the operation. The two given matrices are incompatible." << endl;
			return;
		}
		
		double** X = new double* [rows2];
		for (int i = 0; i < rows2; i++) {
			X[i] = new double[columns1];
		}

		X = CalculateMatrixMultiplication(matrix2, matrix1, rows2, columns2, rows1, columns1);

		if (resultSaved == true) {
			char* filename = GenerateNameMatrixFilePath();
			SaveMatrix(X, rows2, columns1, filename);
			delete[] filename;
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

		X = CalculateMatrixMultiplication(matrix1, matrix2, rows1, columns1, rows2, columns2);

		if (resultSaved == true) {
			char* filename = GenerateNameMatrixFilePath();
			SaveMatrix(X, rows2, columns1, filename);
			delete[] filename;
		}

		delete[] X;
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

	cout << "Enter number:";
	int number;
	cin >> number;

	switch (number) {
		case 1: {
			cout << "Enter the path to the file containing the first matrix:";
			char* file1 = new char[200];
			cin >> file1;
			cout << "Enter the path to the file containing the second matrix:";
			char* file2 = new char[200];
			cin >> file2;

			bool saveResultFile = SaveResultAsFile();

			double** matrix1 = new double* [4];
			for (int i = 0; i < 4; i++) {
				matrix1[i] = new double[4];
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					matrix1[i][j] = 100000.0;
				}
			}

			double** matrix2 = new double* [4];
			for (int i = 0; i < 4; i++) {
				matrix2[i] = new double[4];
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					matrix2[i][j] = 200000.0;
				}
			}

			SumMatrices(matrix1, matrix2, 4, 4, 4, 4, saveResultFile);

			break;
		}
		case 2: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			cout << "Enter the value of the scalar:";
			double scalar;
			cin >> scalar;

			bool saveResultFile = SaveResultAsFile();

			break;
		}
		case 3: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			cout << "Enter the value of the scalar:";
			double scalar;
			cin >> scalar;

			bool saveResultFile = SaveResultAsFile();

			break;
		}
		case 4: {
			cout << "Enter the path to the file containing the first matrix:";
			char* file1 = new char[200];
			cin >> file1;
			cout << "Enter the path to the file containing the second matrix:";
			char* file2 = new char[200];
			cin >> file2;

			bool saveResultFile = SaveResultAsFile();

			break;
		}
		case 5: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			bool saveResultFile = SaveResultAsFile();

			break;
		}
		case 6: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			bool saveResultFile = SaveResultAsFile();

			break;
		}
		case 7: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			bool saveResultFile = SaveResultAsFile();

			break;
		}
		case 8: {
			break;
		}
		case 9: {
			break;
		}
	}

	return 0;
}