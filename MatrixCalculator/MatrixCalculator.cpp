#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int NUMBER_OPERATIONS = 9;

const char* OPERATIONS[NUMBER_OPERATIONS] = {
	"Sum of two matrices",
	"Multiplication of matrix by scalar",
	"Division of mаtrix by scalar",
	"Multiplication of matrix by matrix",
	"Finding the determinant",
	"Finding the inverse matrix",
	"Transposition of matrix",
	"Matrix equation",
	"Singular Value Decomposition"
};

const size_t MAX_NUMBER_ELEMENTS = 4;

int ReadData(char path[]) {
	ifstream file(path);

	if (!file.is_open()) {
		return 1;
	}
}

void SumMatrices(double** matrix1, double** matrix2, int rows1, int columns1, int rows2, int columns2) {
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
			cout << setw(6) << matrix1[i][j];
		}
		cout << " ║ ";

		if (i == rows1 / 2) cout << " + ";

		cout << " ║ ";
		for (int j = 0; j < columns1; j++) {
			cout << setw(6) << matrix2[i][j];
		}
		cout << " ║ ";

		if (i == rows1 / 2) cout << " = ";

		cout << " ║ ";
		for (int j = 0; j < columns1; j++) {
			matrix[i][j] = matrix1[i][j] + matrix2[i][j];
			cout << setw(6) << matrix[i][j];
		}
		cout << " ║ ";

		cout << endl;
	}
}

void MultiplyByScalar(double** matrix, int rows, int columns, int scalar) {
	for (int i = 0; i < rows; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(6) << matrix[i][j];
		}
		cout << " ║ ";

		if (i == rows / 2) {
			cout << " *  " << scalar << "  = ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = matrix[i][j] * scalar;
			cout << setw(6) << matrix[i][j];
		}
		cout << " ║ ";

		cout << endl;
	}
}

void DivideByScalar(double** matrix, int rows, int columns, int scalar) {
	for (int i = 0; i < rows; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(6) << matrix[i][j];
		}
		cout << " ║ ";

		if (i == rows / 2) {
			cout << " *  " << scalar << "  = ";
		}

		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = matrix[i][j] / scalar;
			cout << setw(6) << matrix[i][j];
		}
		cout << " ║ ";

		cout << endl;
	}
};

void TransposeMatrix(double** matrix, int rows, int columns) {
	double** transposedMatrix = new double*[columns];
	for (int i = 0; i < columns; i++) {
		transposedMatrix[i] = new double[rows];
	}

	for (int i = 0; i < rows; i++) {
		cout << " ║ ";
		for (int j = 0; j < columns; j++) {
			cout << setw(6) << matrix[i][j];
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
			cout << setw(6) << matrix[j][i];
		}
		cout << " ║ ";

		cout << endl;
	}
}

void InverseMatrix();

int main() {
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

			break;
		}
		case 2: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			cout << "Enter the value of the scalar:";
			double scalar;
			cin >> scalar;

			break;
		}
		case 3: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			cout << "Enter the value of the scalar:";
			double scalar;
			cin >> scalar;

			break;
		}
		case 4: {
			cout << "Enter the path to the file containing the first matrix:";
			char* file1 = new char[200];
			cin >> file1;
			cout << "Enter the path to the file containing the second matrix:";
			char* file2 = new char[200];
			cin >> file2;

			break;
		}
		case 5: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			break;
		}
		case 6: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

			break;
		}
		case 7: {
			cout << "Enter the path to the file containing the matrix:";
			char* file = new char[200];
			cin >> file;

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