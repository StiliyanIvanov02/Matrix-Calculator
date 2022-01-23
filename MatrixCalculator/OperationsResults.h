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
* <header file with functions checking, executing and delivering the results of the matrix operations>
*
*/

#pragma once

void sumMatrices (double**, double**, int, int, int, int, bool);

void multiplyByScalar (double**, int, int, double, bool);

void divideByScalar (double**, int, int, double, bool);

void multiplyMatrixByMatrix (double**, double**, int, int, int, int, bool);

void raiseMatrixToPower(double**, int, int, int, bool);

void findDeterminant(double**, int, int);

void inverseMatrix(double**, int, int, bool);

void transposeMatrix(double**, int, int, bool);

void matrixEquation(double** matrix1, double**, int, int, int, int, bool, bool);
