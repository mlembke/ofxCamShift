#include "ofxMatrix.h"

template <typename T>
ofxMatrix<T>::ofxMatrix()
{
	height = 1;
	width = 1;

	data = new T[height * width]();
	matrix = new T*[height];

	for (auto i = 0; i < height; i++)
		matrix[i] = &data[width * i];
}

template<typename T>
ofxMatrix<T> ofxMatrix<T>::flipHorizontaly() const
{
	ofxMatrix<T> res(height, width);

	for (auto i = 0, i_2 = width - 1; i < width; i++, i_2--)
	{
		for (auto j = 0; j < height; j++)
		{
			res[j][i] = matrix[j][i_2];
		}
	}

	return res;
}

template <typename T>
void ofxMatrix<T>::copyRow(const ofxMatrix<T>& source, int idestrow, int isourcerow)
{
	T* src = source[isourcerow];
	T* dst = matrix[idestrow];

	memcpy(dst, src, sizeof(T)* width);

}


template <typename T>
void ofxMatrix<T>::writeToFile(const char* filename)
{
	fstream f(filename, ios::in | ios::trunc);
	if(f.is_open())
	{
		f << height << " " << width << "\n";
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
			{
				f << getRow(i)[j] << " ";
			}
			f << "\n";
		}
	}
	f.close();
}

template <typename T>
void ofxMatrix<T>::setSize(int height, int width)
{
	if (data != nullptr) 
		delete []data;
	if (matrix != nullptr) 
		delete []matrix;

	this->width = width;
	this->height = height;

	data = new T[height * width]();
	matrix = new T*[height];

	T* data_p = data;
	for (auto i = 0; i < height; i++)
	{
		matrix[i] = data_p;
		data_p += width;
	}
}

template <typename T>
T* ofxMatrix<T>::getRow(int i) const {return matrix[i];}

template <typename T>
T* ofxMatrix<T>::getData() const {return data;}

template <typename T>
ofxMatrix<T>::ofxMatrix(int height, int width)
{
	this->height = height;
	this->width = width;

	this->data = new T[height * width]();
	this->matrix = new T*[height];

	for (auto i = 0; i < height; i++)
		this->matrix[i] = &data[width * i];
}

template <typename T>
ofxMatrix<T>::ofxMatrix(int height, int width, T* data)
{
	this->height = height;
	this->width = width;

	this->data = new T[height * width]();
	this->matrix = new T*[height];

	memcpy(this->data, data, width*height*sizeof(T));

	for (auto i = 0; i < height; i++)
		this->matrix[i] = &this->data[width * i];
}

template <typename T>
T& ofxMatrix<T>::operator()(int row, int col)
{
	return matrix[row][col];
}

template <typename T>
ofxMatrix<T>::ofxMatrix(const ofxMatrix<T>& other)
{
	height = other.height;
	width = other.width;

	this->data = new T[height * width]();
	this->matrix = new T*[height];

	T* data_p = data;

	for (auto i = 0; i < height; i++)
	{
		this->matrix[i] = data_p;
		data_p += width;
	}

	memcpy(data, other.data, width*height*sizeof(T));
}

template <typename T>
ofxMatrix<T>::~ofxMatrix()
{
	delete [] data;
	delete [] matrix;
}

template <typename T>
ofxMatrix<T>& ofxMatrix<T>::operator=(const ofxMatrix<T>& right)
{
	if (this == &right)
		return *this;

	delete [] data;
	delete [] matrix;

	height = right.height;
	width = right.width;

	this->data = new T[height * width]();
	this->matrix = new T*[height];

	for (auto i = 0; i < height; i++)
		this->matrix[i] = &data[width * i];

	memcpy(this->data, right.data, height * width * sizeof(T));

	return *this;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator-(const ofxMatrix<T>& right) const
{
	ofxMatrix<T> res(height, width);

	if (right.height == 1)
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				res.matrix[i][j] = matrix[i][j] - right.matrix[0][j];
		}
	}
	else
	{
		for (atuo i = 0; i < height; i++)
		{
			for (atuo j = 0; j < width; j++)
				res.matrix[i][j] = matrix[i][j] - right.matrix[i][j];
		}
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator-(const T& right) const
{
	ofxMatrix<T> res(height, width);

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			res.matrix[i][j] = matrix[i][j] - right;
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator-=(const ofxMatrix<T>& right)
{
	if (right.height == 1)
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				matrix[i][j] -= right.matrix[0][j];
		}
	}
	else
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				matrix[i][j] -= right.matrix[i][j];
		}
	}

	return *this;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator-=(const T& right)
{
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			matrix[i][j] -= right;
	}

	return *this;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator+(const ofxMatrix<T>& right) const
{
	ofxMatrix<T> res(height, width);

	if (right.height == 1)
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				res.matrix[i][j] = matrix[i][j] + right.matrix[0][j];
		}
	}
	else
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				res.matrix[i][j] = matrix[i][j] + right.matrix[i][j];
		}
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator+(const T& right) const
{
	ofxMatrix<T> res(height, width);

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			res.matrix[i][j] = matrix[i][j] + right;
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator+=(const ofxMatrix<T>& right)
{
	if (right.height == 1)
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				matrix[i][j] += right.matrix[0][j];
		}
	}
	else
	{
		for (auto i = 0; i < height; i++)
		{
			for (auto j = 0; j < width; j++)
				matrix[i][j] += right.matrix[i][j];
		}
	}

	return *this;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator+=(const T& right)
{
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			matrix[i][j] += right;
	}

	return *this;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator*(const ofxMatrix<T>& right) const
{
	ofxMatrix<T> res(height, right.width);

	int rh = res.height;
	int rw = res.width;

	T* ptr_res_row;
	T* ptr_this_row;
	T* ptr_res;

	for (auto i = 0; i < rh; i++)
	{
		ptr_res_row = res.getRow(i);
		ptr_this_row = getRow(i);
		for (auto j = 0; j < rw; j++)
		{
			ptr_res = ptr_res_row + j;
			for (auto k = 0; k < width; k++)
			{
				*ptr_res += ptr_this_row[k] * right.matrix[k][j];
			}
		}
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator*(const T& right) const
{
	ofxMatrix<T> res(height, width);
	T* ptr;
	T* ptr_res;

	for (auto i = 0; i < res.height; i++)
	{
		ptr = getRow(i);
		ptr_res = res.getRow(i);
		for (auto j = 0; j < res.width; j++)
			ptr_res[j] = right * ptr[j];

	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator/(const T& right) const
{
	ofxMatrix<T> res(height, width);

	for (auto i = 0; i < res.height; i++)
	{
		for (auto j = 0; j < res.width; j++)
		{
			res.matrix[i][j] = matrix[i][j] / right;
		}
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::operator/=(const T& right)
{
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			matrix[i][j] /= right;
	}

	return *this;
}

template <typename T>
void ofxMatrix<T>::subtractRow(const ofxMatrix<T>& right)
{
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			matrix[i][j] -= right.matrix[0][j];
	}
}

template<typename T>
void ofxMatrix<T>::addRow(const ofxMatrix<T>& right)
{
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			matrix[i][j] += right.matrix[0][j];
	}
}

template <typename T>
double ofxMatrix<T>::mean()
{
	double sum = 0;

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			sum += matrix[i][j];
		}
	}

	return sum / (height * width);
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::meanRow() const
{
	ofxMatrix<T> sum(1, width);

	for (auto i = 0; i < width; i++)
	{
		for (auto j = 0; j < height; j++)
		{
			sum.matrix[0][i] += matrix[j][i];
		}
		sum.matrix[0][i] = sum.matrix[0][i] / height;
	}

	return sum;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::minRow() const
{
	ofxMatrix<T> min(1, width);

	for (auto i = 0; i < width; i++)
	{
		min.matrix[0][i] = matrix[0][i];
		for (auto j = 1; j < height; j++)
		{
			T val = matrix[j][i];
			if (val < min.matrix[0][i])
				min.matrix[0][i] = val;
		}
	}

	return min;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::maxRow() const
{
	ofxMatrix<T> max(1, width);

	for (auto i = 0; i < width; i++)
	{
		max.matrix[0][i] = matrix[0][i];
		for (auto j = 1; j < height; j++)
		{
			T val = matrix[j][i];
			if (val > max.matrix[0][i])
				max.matrix[0][i] = val;
		}
	}

	return max;
}

template <typename T>
double ofxMatrix<T>::std()
{
	double meanVal = mean();
	double sum = 0;
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			sum += pow(matrix[i][j] - meanVal, 2);
		}
	}

	return sqrt(sum / (height * width));
}

template <typename T>
double ofxMatrix<T>::norm()
{
	double sum = 0;
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			sum += matrix[i][j] * matrix[i][j];
		}
	}

	return sqrt(sum);
}

template <typename T>
double ofxMatrix<T>::norm(int start_col, int end_col, int start_row, int end_row)
{
	double sum = 0;
	for (auto i = start_row; i < end_row; i++)
	{
		for (auto j = start_col; j < end_col; j++)
		{
			sum += matrix[i][j] * matrix[i][j];
		}
	}

	return sqrt(sum);
}

template <typename T>
void ofxMatrix<T>::divideFlattened(int start_col, int end_col, int start_row, int end_row, int n_el_in_row, T val)
{
	double sum = 0;
	for (auto i = start_row; i < end_row; i++)
	{
		for (auto j = start_col; j < end_col; j++)
		{
			auto pos = i * n_el_in_row + j;
			data[pos] /= val;
		}
	}
}

template <typename T>
double ofxMatrix<T>::flattenNorm(int start_col, int end_col, int start_row, int end_row, int n_el_in_row)
{
	double sum = 0;
	for (auto i = start_row; i < end_row; i++)
	{
		for (auto j = start_col; j < end_col; j++)
		{
			auto pos = i* n_el_in_row + j;
			sum += data[pos] * data[pos];
		}
	}

	return sqrt(sum);
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::trans() const
{
	ofxMatrix<T> res(width, height);

	for (auto i = 0; i < res.height; i++)
	{
		for (auto j = 0; j < res.width; j++)
			res.matrix[i][j] = matrix[j][i];
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::flatten() const
{
	ofxMatrix<T> res(1, height * width);

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			res.matrix[0][i * width + j] = matrix[i][j];
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::flattenT() const
{
	ofxMatrix<T> res(height * width, 1);

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			res.matrix[i * width + j][0] = matrix[i][j];
	}

	return res;
}

template <typename T>
T ofxMatrix<T>::maximum() const
{
	T res = matrix[0][0];

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			if (matrix[i][j] > res)
				res = matrix[i][j];
		}
	}

	return res;
}

template <typename T>
T ofxMatrix<T>::minimum() const
{
	T res = matrix[0][0];

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			if (matrix[i][j] < res)
				res = matrix[i][j];
		}
	}

	return res;
}

template <typename T>
void ofxMatrix<T>::print() const
{
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
			std::cout << std::setw(5) << std::setprecision(3) << matrix[i][j] << " ";

		std::cout << std::endl;
	}
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::subMat(int startRow, int endRow, int startCol, int endCol) const
{
	ofxMatrix<T> res(endRow - startRow, endCol - startCol);

	for (auto i = startRow, i2 = 0; i < endRow; i++, i2++)
	{
		for (auto j = startCol, j2 = 0; j < endCol; j++, j2++)
		{
			res.matrix[i2][j2] = matrix[i][j];
		}
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::vstack(ofxMatrix<T> other) const
{
	ofxMatrix<T> res(height + other.height, width);
	for (auto i = 0; i < height + other.height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			if (i < height)
				res.matrix[i][j] = matrix[i][j];
			else
				res.matrix[i][j] = other.matrix[i - height][j];
		}
	}

	return res;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::hstack(ofxMatrix<T> other) const
{
	ofxMatrix<T> res(height, width + other.width);
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width + other.width; j++)
		{
			if (j < width)
				res.matrix[i][j] = matrix[i][j];
			else
				res.matrix[i][j] = other.matrix[i][j - width];
		}
	}

	return res;
}

template <typename T>
int ofxMatrix<T>::argmin() const
{
	T minVal = matrix[0][0];
	auto minInd = 0;

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			if (matrix[i][j] < minVal)
			{
				minVal = matrix[i][j];
				minInd = i * width + j;
			}
		}
	}

	return minInd;
}

template <typename T>
T ofxMatrix<T>::sum() const
{
	T total = 0;
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			total += matrix[i][j];
		}
	}

	return total;
}

template <typename T>
ofxMatrix<T> ofxMatrix<T>::piecewisePow(double power) const
{
	ofxMatrix<T> res(height, width);
	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			res.matrix[i][j] = pow(matrix[i][j], power);
		}
	}

	return res;
}

template <typename T>
void ofxMatrix<T>::copyFromUCharTable(unsigned char *src, int _width, int _height)
{
	setSize(_height, _width);
	for (auto i=0; i<width*height; i++)
	{
		data[i] = static_cast<T>(src[i]);
	}
}

template <typename T>
void ofxMatrix<T>::copyFromUCharTableWithFlip(unsigned char *src, int _width, int _height)
{
	setSize(_height, _width);
	T* row;
	int pos;
	for (auto i=0; i<height; i++)
	{
		row = getRow(i);
		pos = (height - i - 1)*width;
		for (auto j=0; j<width; j++)
		{
			row[j] = static_cast<T>(src[pos + j]);
		}
	}
}

template <typename T>
void ofxMatrix<T>::swapColumns(int i, int j)
{
	T ccopy;
	T* row;
	for (auto ri=0; ri<height; ri++)
	{
		row = getRow(ri);
		ccopy = row[i];
		row[i] = row[j];
		row[j] = ccopy;
	}

}

template <typename T>
void ofxMatrix<T>::swapRows(int i, int j)
{
	T* rcopy = new T[width];
	memcpy(rcopy, getRow(i), width*sizeof(T));
	memcpy(getRow(i), getRow(j), width*sizeof(T));
	memcpy(getRow(j), rcopy, width*sizeof(T));

	delete []rcopy;
}
