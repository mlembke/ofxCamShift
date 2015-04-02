#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T>
class ofxMatrix
{
public:
	int height;
	int width;

	T** matrix;
	T* data;

public:
	ofxMatrix();

	void setSize(int height, int width);

	T* getRow(int i) const;
	T* getData() const;

	ofxMatrix(int height, int width);

	ofxMatrix(int height, int width, T* data);

	ofxMatrix(const ofxMatrix<T>& other);

	~ofxMatrix();

	ofxMatrix<T>& operator=(const ofxMatrix<T>& right);
	ofxMatrix<T> operator-(const ofxMatrix<T>& right) const;
	ofxMatrix<T> operator-(const T& right) const;
	ofxMatrix<T> operator-=(const ofxMatrix<T>& right);
	ofxMatrix<T> operator-=(const T& right);

	ofxMatrix<T> operator+(const ofxMatrix<T>& right) const;
	ofxMatrix<T> operator+(const T& right) const;
	ofxMatrix<T> operator+=(const ofxMatrix<T>& right);
	ofxMatrix<T> operator+=(const T& right);
	ofxMatrix<T> operator*(const ofxMatrix<T>& right) const;
	ofxMatrix<T> operator*(const T& right) const;
	ofxMatrix<T> operator/(const T& right) const;
	ofxMatrix<T> operator/=(const T& right);

	void copyRow(const ofxMatrix<T>& source, int idestrow, int isourcerow);

	void subtractRow(const ofxMatrix<T>& right);
	void addRow(const ofxMatrix<T>& right);
	ofxMatrix<T> flipHorizontaly() const;


	T& operator()(int row, int col);

	T* operator[](int i) const
	{
		return getRow(i);
	}

	void swapRows(int i, int j);
	void swapColumns(int i, int j);
	double mean();

	ofxMatrix<T> meanRow() const;
	ofxMatrix<T> minRow() const;
	ofxMatrix<T> maxRow() const;

	double std();
	double norm();
	double norm(int start_col, int end_col, int start_row, int end_row);
	double flattenNorm(int start_col, int end_col, int start_row, int end_row, int n_el_in_row);
	void divideFlattened(int start_col, int end_col, int start_row, int end_row, int n_el_in_row, T val);

	ofxMatrix<T> trans() const;
	ofxMatrix<T> flatten() const;
	ofxMatrix<T> flattenT() const;

	T maximum() const;
	T minimum() const;

	void print() const;
	ofxMatrix<T> subMat(int startRow, int endRow, int startCol, int endCol) const;
	ofxMatrix<T> vstack(ofxMatrix<T> other) const;
	ofxMatrix<T> hstack(ofxMatrix<T> other) const;

	int argmin() const;
	T sum() const;
	ofxMatrix<T> piecewisePow(double power) const;

	void copyFromUCharTable(unsigned char* src, int _width, int _height);
	void copyFromUCharTableWithFlip(unsigned char* src, int _width, int _height);

	void writeToFile(const char* filename);
};

#include "ofxMatrix.cpp"