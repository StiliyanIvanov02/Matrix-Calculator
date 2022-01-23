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
* <header file with the supported matrix operations>
*
*/

#pragma once

// returns the sum of two given matrices with the same dimensions
double** calculateMatrixSum(double**, double**, int, int);

// returns the multiplication of a matrix and scalar
double** calculateMultiplicationByScalar(double**, int, int, double);

// returns the division of a matrix by a scalar
double** calculateDivisionByScalar(double**, int, int, double);

// returns the multiplication of two matrices
double** calculateMatrixMultiplication(double**, double**, int, int, int, int);

// returns the determinant of a square matrix
double calculateDeterminant(double**, int);

// returns the transposed matrix of a given one
double** calculateTransposedMatrix(double**, int, int);

// returns the inverse matrix of a given square one
double** calculateInverseMatrix(double**, int, bool&);

// returns the given matrix raised to a given power
double** calculateMatrixRaisedToPower(double**, int, int, bool&);
