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
* <main source file>
*
*/

#include <iostream>
#include "OperationsResults.h"
#include "HelperFunctions.h"

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

void Calculator() {
	srand((unsigned)time(NULL));

	cout << "MATRIX CALCULATOR" << endl;
	cout << endl;

	cout << "Select one of the following operations:" << endl;
	for (int i = 0; i < NUMBER_OPERATIONS; i++) {
		cout << i + 1 << ". " << OPERATIONS[i] << endl;
	}

	int number = 0;

	while (number != 10) {
		// validates the input for the number of the operation
		cout << endl;
		char input[1024] = " ";
		while (!isInt(input)) {
			cout << "Enter the number of the selected operation: ";
			cin >> input;
			if (!isInt(input)) {
				cout << "Invalid data type!" << endl;
				cout << endl;
			}
		}

		number = convertToInt(input);

		switch (number) {
		case 1: {
			char command1[] = "Enter the path to the file containing the first matrix: ";
			matrixData matrixData1 = readData(command1);
			double** matrix1 = matrixData1.elements;
			int rows1 = matrixData1.rows;
			int columns1 = matrixData1.columns;

			char command2[] = "Enter the path to the file containing the second matrix: ";
			matrixData matrixData2 = readData(command2);
			double** matrix2 = matrixData2.elements;
			int rows2 = matrixData2.rows;
			int columns2 = matrixData2.columns;

			bool saveResultFile = saveResultAsFile();

			sumMatrices(matrix1, matrix2, rows1, columns1, rows2, columns2, saveResultFile);

			break;
		}
		case 2: {
			char command[] = "Enter the path to the file containing the matrix: ";
			matrixData matrixData = readData(command);
			double** matrix = matrixData.elements;
			int rows = matrixData.rows;
			int columns = matrixData.columns;

			char inputScalar[1024] = " ";
			while (!isDouble(inputScalar)) {
				cout << "Enter the value of the scalar: ";
				cin >> inputScalar;
				if (!isDouble(inputScalar)) {
					cout << "Invalid data type!" << endl;
					cout << endl;
				}
			}
			double scalar = convertToDouble(inputScalar);

			bool saveResultFile = saveResultAsFile();

			multiplyByScalar(matrix, rows, columns, scalar, saveResultFile);

			break;
		}
		case 3: {
			char command[] = "Enter the path to the file containing the matrix: ";
			matrixData matrixData = readData(command);
			double** matrix = matrixData.elements;
			int rows = matrixData.rows;
			int columns = matrixData.columns;

			char inputScalar[1024] = " ";
			while (!isDouble(inputScalar) || convertToDouble(inputScalar) == 0) {
				cout << "Enter the value of the scalar: ";
				cin >> inputScalar;
				if (!isDouble(inputScalar)) {
					cout << "Invalid data type!" << endl;
					cout << endl;
				}
				else if (convertToDouble(inputScalar) == 0) {
					cout << "Cannot divide by 0!" << endl;
					cout << endl;
				}
			}
			double scalar = convertToDouble(inputScalar);

			bool saveResultFile = saveResultAsFile();

			divideByScalar(matrix, rows, columns, scalar, saveResultFile);

			break;
		}
		case 4: {
			char command1[] = "Enter the path to the file containing the first matrix: ";
			matrixData matrixData1 = readData(command1);
			double** matrix1 = matrixData1.elements;
			int rows1 = matrixData1.rows;
			int columns1 = matrixData1.columns;

			char command2[] = "Enter the path to the file containing the second matrix: ";
			matrixData matrixData2 = readData(command2);
			double** matrix2 = matrixData2.elements;
			int rows2 = matrixData2.rows;
			int columns2 = matrixData2.columns;

			bool saveResultFile = saveResultAsFile();

			multiplyMatrixByMatrix(matrix1, matrix2, rows1, columns1, rows2, columns2, saveResultFile);

			break;
		}
		case 5: {
			char command[] = "Enter the path to the file containing the matrix: ";
			matrixData matrixData = readData(command);
			double** matrix = matrixData.elements;
			int rows = matrixData.rows;
			int columns = matrixData.columns;

			int power = -6;
			while (power < -5 || power > 5) {
				char inputPower[1024] = " ";
				while (!isInt(inputPower)) {
					cout << "Enter the power to which the matrix will be raised (an integer between -5 and 5): ";
					cin >> inputPower;
					if (!isInt(inputPower)) {
						cout << "Invalid data type!" << endl;
						cout << endl;
					}
				}

				power = convertToInt(inputPower);

				if (power < -5 || power > 5) {

				}
			}

			bool saveResultFile = saveResultAsFile();

			raiseMatrixToPower(matrix, rows, columns, power, saveResultFile);
			break;
		}
		case 6: {
			char command[] = "Enter the path to the file containing the matrix: ";
			matrixData matrixData = readData(command);
			double** matrix = matrixData.elements;
			int rows = matrixData.rows;
			int columns = matrixData.columns;

			findDeterminant(matrix, rows, columns);

			break;
		}
		case 7: {
			char command[] = "Enter the path to the file containing the matrix: ";
			matrixData matrixData = readData(command);
			double** matrix = matrixData.elements;
			int rows = matrixData.rows;
			int columns = matrixData.columns;

			bool saveResultFile = saveResultAsFile();

			inverseMatrix(matrix, rows, columns, saveResultFile);

			break;
		}
		case 8: {
			char command[] = "Enter the path to the file containing the matrix: ";
			matrixData matrixData = readData(command);
			double** matrix = matrixData.elements;
			int rows = matrixData.rows;
			int columns = matrixData.columns;

			bool saveResultFile = saveResultAsFile();

			transposeMatrix(matrix, rows, columns, saveResultFile);

			break;
		}
		case 9: {
			char command1[] = "Enter the path to the file containing the first matrix: ";
			matrixData matrixData1 = readData(command1);
			double** matrix1 = matrixData1.elements;
			int rows1 = matrixData1.rows;
			int columns1 = matrixData1.columns;

			char command2[] = "Enter the path to the file containing the second matrix: ";
			matrixData matrixData2 = readData(command2);
			double** matrix2 = matrixData2.elements;
			int rows2 = matrixData2.rows;
			int columns2 = matrixData2.columns;

			char position = ' ';
			bool isLeft;
			while (position != 'L' && position != 'R') {
				cout << "Will the matrix X we want to obtain be the left multiplier (X*A=B) or the right multiplier (A*X=B)?" << endl;
				cout << "Enter L for left or R for right: ";
				cin >> position;
				if (position == 'L') {
					isLeft = true;
				}
				else if (position == 'R') {
					isLeft = false;
				}
			}

			bool saveResultFile = saveResultAsFile();

			matrixEquation(matrix1, matrix2, rows1, columns1, rows2, columns2, isLeft, saveResultFile);

			break;
		}
		case 10: {
			cout << "Exited from program." << endl;
			break;
		}
		default: {
			cout << "Invalid number of operation!" << endl;
			break;
		}
		}
	}
}

int main() {
	Calculator();

	return 0;
}