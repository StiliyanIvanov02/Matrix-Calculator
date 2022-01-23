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
* <header file with helper functions>
*
*/

#pragma once

// structure representing the data received for a matrix from a text file
struct matrixData {
	int rows;
	int columns;
	double** elements;
};

const int MAX_NUMBER_ELEMENTS_IN_ROW = 20;
const int MAX_NUMBER_ELEMENTS_IN_ROW_DETERMINANT = 4;

const int MAX_NUMBER_DIGITS = 6;
const int MAX_NUMBER_DIGITS_AFTER_DECIMAL_POINT = 3;

// frees the memory allocated for dynamic matrices
void FreeDynamicMemory(double**, int);

// returns whether the user wants the result of his operation to be saved as a text file
bool saveResultAsFile();

// prompts user to enter filepath and reads the data from it, if valid
matrixData readData(char[]);

// returns the path generated for the text file which will store the matrix result
char* generateNameMatrixFilePath();

// returns the number of symbols that a number consists of
int numberSymbolsNumber(double);

// rounds a number to the specified decimal places
double roundNumber(double);

// returns the number of characters that a row of a matrix takes when printed
int numberSymbolsMatrixRow(int);

// prints a given row of a matrix
void printMatrixRow(double**, int, int);

// saves the matrix result in the generated directory
void saveMatrix(double**, int, int, char*);

// checks whether a char array represents a double number
bool isInt(char[]);

// checks whether a char array represents a double number
bool isDouble(char[]);

// converts char array into int number
int convertToInt(char[]);

// converts char array into double number
double convertToDouble(char[]);