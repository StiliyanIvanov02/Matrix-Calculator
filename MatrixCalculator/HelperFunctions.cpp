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
* <source file with helper functions>
*
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include "HelperFunctions.h"

using namespace std;

const int MAX_NUMBER_CHARS_IN_ROW_FILE = 1024;
const int OUTPUT_FILE_PATH_LENGTH = 19;
const int INPUT_FILE_PATH_MAX_LENGTH = 200;
const char* FILE_PATH = "Matrices/00000.txt";

// frees the memory allocated for dynamic matrices
void FreeDynamicMemory(double** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

// returns whether the user wants the result of his operation to be saved as a text file
bool saveResultAsFile() {
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

// prompts user to enter filepath and reads the data from it, if valid
matrixData readData(char command[]) {
	bool validPath = false;

	char* line = new char[MAX_NUMBER_CHARS_IN_ROW_FILE];

	double* elements = new double[MAX_NUMBER_ELEMENTS_IN_ROW * MAX_NUMBER_ELEMENTS_IN_ROW];
	int elementsCount = 0, linesCount = 0;

	while (validPath == false) {
		cout << command;

		char* path = new char[INPUT_FILE_PATH_MAX_LENGTH];
		cin >> path;

		ifstream file;

		file.open(path, std::ios::in);
		if (!file.is_open()) {
			cout << "There is no file with such a name." << endl;
			cout << endl;
		}
		else {
			validPath = true;
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
	}

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

// returns the path generated for the text file which will store the matrix result
char* generateNameMatrixFilePath() {
	char* output = new char[OUTPUT_FILE_PATH_LENGTH];
	for (int i = 0; i < OUTPUT_FILE_PATH_LENGTH; i++) {
		// the name of the text file consists of 5 random digits
		if (i >= 9 && i <= 13) {
			output[i] = (rand() % 10) + '0';
		}
		else {
			output[i] = FILE_PATH[i];
		}
	}

	return output;
}

// returns the number of symbols that a number consists of
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

// rounds a number to the specified decimal places
double roundNumber(double number) {
	for (int i = 0; i < MAX_NUMBER_DIGITS_AFTER_DECIMAL_POINT; i++) {
		number *= 10;
	}
	number = (int)number;
	for (int i = 0; i < MAX_NUMBER_DIGITS_AFTER_DECIMAL_POINT; i++) {
		number /= 10;
	}

	return number;
}

// returns the number of characters that a row of a matrix takes when printed
int numberSymbolsMatrixRow(int numberElements) {
	int count = 6;

	for (int i = 0; i < numberElements; i++) {
		count += MAX_NUMBER_DIGITS + 1;
	}

	return count;
}

// prints a given row of a matrix
void printMatrixRow(double** matrix, int rowIndex, int columns) {
	cout << " | ";

	for (int i = 0; i < columns; i++) {
		cout << setw(MAX_NUMBER_DIGITS + 1) << roundNumber(matrix[rowIndex][i]);
	}

	cout << " | ";
}

// saves the matrix result in the generated directory
void saveMatrix(double** matrix, int rows, int columns, char* filename) {
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

// checks whether a char array represents a double number
bool isInt(char input[]) {
	for (int i = 0; input[i] != '\0'; i++) {
		// checks for minus sign (the first one)
		if (i == 0 && input[i] == '-') {
			continue;
		}
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

// checks whether a char array represents a double number
bool isDouble(char input[]) {
	bool hasDecimalPoint = false;
	for (int i = 0; input[i] != '\0'; i++) {
		// checks for minus sign (the first one)
		if (i == 0 && input[i] == '-') {
			continue;
		}
		if (!isdigit(input[i])) {
			// checks for decimal point (only one allowed)
			if ((input[i] == '.' || input[i] == ',') && hasDecimalPoint == false) {
				hasDecimalPoint = true;
				continue;
			}
			return false;
		}
	}
	return true;
}

// converts char array into int number
int convertToInt(char input[]) {
	int number = 0;
	bool isNegative = false;
	for (int i = 0; input[i] != '\0'; i++) {
		// checks whether the number is negative
		if (i == 0 && input[i] == '-') {
			isNegative = true;
			continue;
		}
		number += input[i] - '0';
		number *= 10;
	}
	number /= 10;

	if (isNegative) {
		number = -number;
	}
	return number;
}

// converts char array into double number
double convertToDouble(char input[]) {
	double number = 0.0;
	bool isNegative = false, hasDecimalPoint = false;
	int numberDigitsAfterDecimalPoint = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		// checks whether the number is negative
		if (i == 0 && input[i] == '-') {
			isNegative = true;
			continue;
		}
		// checks whether the number has a decimal point
		if ((input[i] == '.' || input[i] == ',') && hasDecimalPoint == false) {
			hasDecimalPoint = true;
			continue;
		}
		else {
			// counts the number of digits after the decimal point
			if (hasDecimalPoint == true) {
				numberDigitsAfterDecimalPoint++;
			}
			number += input[i] - '0';
			number *= 10;
		}
	}
	for (int j = 0; j <= numberDigitsAfterDecimalPoint; j++) {
		number /= 10;
	}

	if (isNegative) {
		number = -number;
	}
	return number;
}