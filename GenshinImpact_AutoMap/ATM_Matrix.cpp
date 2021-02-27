#include "ATM_Matrix.h"

ATM_Matrix::ATM_Matrix()
{
}

ATM_Matrix::~ATM_Matrix()
{
	if (!DeleteMatrix())
	{
		std::cout << "Delete Matrix Faile!" << std::endl;
	}
}

ATM_Matrix::ATM_Matrix(int _cols, int _rows)
{
	cols = _cols;
	rows = _rows;
	CreatMatrix();
}

ATM_Matrix::ATM_Matrix(int _cols, int _rows, double * lis)
{
	cols = _cols;
	rows = _rows;
	CreatMatrix();
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = lis[i*rows + j];
		}
	}
}

ATM_Matrix::ATM_Matrix(int _cols, int _rows, double ** lis)
{
	cols = _cols;
	rows = _rows;
	CreatMatrix();
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = lis[i][j];
		}
	}
}

ATM_Matrix::ATM_Matrix(const ATM_Matrix & Mat)
{
	cols = Mat.cols;
	rows = Mat.rows;
	CreatMatrix();
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = Mat.mat[i][j];
		}
	}
}

ATM_Matrix::ATM_Matrix(char * matFileName)
{
	load(matFileName);
}

double ATM_Matrix::at(int i, int j)
{
	if (cols == 0 || rows == 0)
	{
		return 0.0;
	}
	if (i >= 0 && j >= 0 && i < cols&&j < rows)
	{
		return mat[i][j];
	}
	return mat[0][0];
}

bool ATM_Matrix::reSet(int _cols, int _rows)
{
	if (!DeleteMatrix())
	{
		return false;
	}

	cols = _cols;
	rows = _rows;
	CreatMatrix();

	return true;
}

bool ATM_Matrix::reRand()
{
	if (mat == nullptr)
	{
		return false;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = (double)(rand() / 32767.0);
		}
	}

	return true;
}

bool ATM_Matrix::reRand(double min, double max)
{
	if (mat == nullptr)
	{
		return false;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = (double)((max - min)*(rand() / 32767.0) - (max - min) / 2.0);
		}
	}

	return true;
}

bool ATM_Matrix::reEye()
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (i == j)
			{
				mat[i][j] = 1;
			}
			else
			{
				mat[i][j] = 0;
			}
		}
	}
	if (cols != rows)
	{
		return false;
	}
	return true;
}

bool ATM_Matrix::reZeros()
{
	if (mat == nullptr)
	{
		return false;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = 0.0;
		}
	}

	return true;
}

bool ATM_Matrix::reRange()
{
	if (mat == nullptr)
	{
		return false;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (mat[i][j] > 1)
			{
				mat[i][j] = 1;
			}
			if (mat[i][j] < -1)
			{
				mat[i][j] = -1;
			}
		}
	}

	return true;
}

bool ATM_Matrix::reRange(double min, double max)
{
	if (mat == nullptr || min > max)
	{
		return false;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (mat[i][j] > max)
			{
				mat[i][j] = max;
			}
			if (mat[i][j] < min)
			{
				mat[i][j] = min;
			}
		}
	}

	return true;
}

double ATM_Matrix::Sum()
{
	if (mat == nullptr)
	{
		return 0;
	}
	double sum = 0;
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			sum += mat[i][j];
		}
	}
	return sum;
}

double ATM_Matrix::Avg()
{
	if (mat == nullptr)
	{
		return 0.0;
	}
	double avg = Sum();
	avg = avg / (cols*rows);
	return avg;
}

double ATM_Matrix::Avg2()
{
	double avg = Sum();
	if (mat == nullptr)
	{
		return 0.0;
	}
	avg = avg * avg / (cols*rows);
	return avg;
}

double ATM_Matrix::Max()
{
	if (mat == nullptr)
	{
		return 0.0;
	}
	double maxV = mat[0][0];
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (maxV <= mat[i][j])
			{
				maxV = mat[i][j];
			}
		}
	}
	return maxV;
}

double ATM_Matrix::Min()
{
	if (mat == nullptr)
	{
		return 0.0;
	}
	double minV = mat[0][0];
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (minV >= mat[i][j])
			{
				minV = mat[i][j];
			}
		}
	}
	return minV;
}

double ATM_Matrix::D()
{
	if (mat == nullptr)
	{
		return 0.0;
	}
	double D = 0;
	double avg = Avg();
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			D += pow(mat[i][j] - avg, 2);
		}
	}
	return D;
}

ATM_Matrix ATM_Matrix::col(int x)
{
	if (x < 0 || x >= rows)
	{
		throw "Element out of bounds.";
	}
	ATM_Matrix colx(cols, 1);
	for (int i = 0; i < cols; i++)
	{
		colx[i][0] = mat[i][x];
	}
	return colx;
}

ATM_Matrix ATM_Matrix::col(int xa, int xb)
{
	if (xa < 0 || xa >= rows || xb < 0 || xb >= rows || xa > xb)
	{
		throw "Element out of bounds.";
	}
	int rowx = xb - xa + 1;
	ATM_Matrix colx(cols, rowx);
	for (int i = 0; i < cols; i++)
	{
		for (int ii = 0; ii < rowx; ii++)
		{
			colx[i][ii] = mat[i][xa + ii];
		}
	}
	return colx;
}

ATM_Matrix ATM_Matrix::row(int y)
{
	if (y < 0 || y >= cols)
	{
		throw "Element out of bounds.";
	}
	ATM_Matrix rowy(1, rows);
	for (int i = 0; i < rows; i++)
	{
		rowy[0][i] = mat[y][i];
	}
	return rowy;
}

ATM_Matrix ATM_Matrix::row(int ya, int yb)
{
	if (ya < 0 || ya >= cols || yb < 0 || yb >= cols || ya > yb)
	{
		throw "Element out of bounds.";
	}
	int colx = yb - ya + 1;
	ATM_Matrix rowy(colx, rows);
	for (int i = 0; i < rows; i++)
	{
		for (int ii = 0; ii < colx; ii++)
		{
			rowy[ii][i] = mat[ya + ii][i];
		}
	}
	return rowy;
}

double * ATM_Matrix::operator[](int i)
{
	if (i < 0)
	{
		return mat[0];

	}
	if (i > cols)
	{
		return mat[cols - 1];
	}
	return mat[i];
}

ATM_Matrix & ATM_Matrix::operator=(const ATM_Matrix & _Mat)
{
	DeleteMatrix();
	cols = _Mat.cols;
	rows = _Mat.rows;
	CreatMatrix();
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = _Mat.mat[i][j];
		}
	}
	return *this;
}

ATM_Matrix & ATM_Matrix::operator=(const double & _m)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			mat[i][j] = _m;
		}
	}
	return *this;
}

ATM_Matrix ATM_Matrix::operator+(const ATM_Matrix & _Mat)
{
	if (this->cols != _Mat.cols || this->rows != _Mat.rows)
	{
		throw "ATM_Matrix Size Not Equre!";
	}
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = mat[i][j] + _Mat.mat[i][j];
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator+(const double & _m)
{
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = mat[i][j] + _m;
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator-()
{
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = -mat[i][j];
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator-(const ATM_Matrix & _Mat)
{
	if (this->cols != _Mat.cols || this->rows != _Mat.rows)
	{
		throw "ATM_Matrix Size Not Equre!";
	}
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = mat[i][j] - _Mat.mat[i][j];
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator-(const double & _m)
{
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = mat[i][j] - _m;
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator^(const ATM_Matrix & _Mat) const
{
	if (this->cols != _Mat.cols || this->rows != _Mat.rows)
	{
		throw "Both ATM_Matrix Size Not Equre!";
	}
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < _Mat.rows; j++)
		{
			Mat.mat[i][j] = mat[i][j] * _Mat.mat[i][j];
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator*(const ATM_Matrix & _Mat)const
{
	if (this->rows != _Mat.cols)
	{
		throw "Both ATM_Matrix Size Not Equre!";
	}
	ATM_Matrix Mat(cols, _Mat.rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < _Mat.rows; j++)
		{
			for (int k = 0; k < rows; k++)
			{
				Mat.mat[i][j] = Mat.mat[i][j] + mat[i][k] * _Mat.mat[k][j];
			}
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator*(const double & _m)
{
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = mat[i][j] * _m;
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::operator/(const ATM_Matrix & _Mat)
{
	ATM_Matrix I_Mat = I(_Mat);
	ATM_Matrix Mat = *this*I_Mat;
	return Mat;
}

ATM_Matrix ATM_Matrix::operator/(const double & _m)
{
	if (_m == 0)
	{
		throw"Not As Zeros.";
	}
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Mat[i][j] = mat[i][j] / _m;
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::T()
{
	ATM_Matrix Mat(rows, cols);
	for (int i = 0; i < Mat.cols; i++)
	{
		for (int j = 0; j < Mat.rows; j++)
		{
			Mat[i][j] = mat[j][i];
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::T(const ATM_Matrix & _Mat)
{
	ATM_Matrix Mat(_Mat.rows, _Mat.cols);
	for (int i = 0; i < Mat.cols; i++)
	{
		for (int j = 0; j < Mat.rows; j++)
		{
			Mat[i][j] = _Mat.mat[j][i];
		}
	}
	return Mat;
}

ATM_Matrix ATM_Matrix::I()
{
	ATM_Matrix Mat = I(*this);
	return Mat;
}

ATM_Matrix ATM_Matrix::I(const ATM_Matrix & _Mat)
{
	if (_Mat.cols != _Mat.rows)
	{
		throw"Col And Row Not Equre!";
	}
	const double EPS = 1e-10;
	double temp;
	ATM_Matrix Mat(_Mat);//为矩阵_Mat做一个备份
	ATM_Matrix Mat_Eye(_Mat);
	Mat_Eye.reEye();

	//将小于EPS的数全部置0
	for (int i = 0; i < Mat.cols; i++) {
		for (int j = 0; j < Mat.rows; j++) {
			if (abs(Mat[i][j]) <= EPS) {
				Mat[i][j] = 0;
			}
		}
	}

	//选择需要互换的两行选主元
	for (int i = 0; i < Mat.cols; i++) {
		if (abs(Mat[i][i]) <= EPS) {
			bool flag = false;
			for (int j = 0; (j < Mat.cols) && (!flag); j++) {
				if ((abs(Mat[i][j]) > EPS) && (abs(Mat[j][i]) > EPS)) {
					flag = true;
					for (int k = 0; k < Mat.rows; k++) {
						temp = Mat[i][k];
						Mat[i][k] = Mat[j][k];
						Mat[j][k] = temp;
						temp = Mat_Eye[i][k];
						Mat_Eye[i][k] = Mat_Eye[j][k];
						Mat_Eye[j][k] = temp;
					}
				}
			}
			if (!flag) {
				throw"Matrix Inv Not Found!";
			}
		}
	}
	//通过初等行变换将A变为上三角矩阵
	double temp_rate;
	for (int i = 0; i < Mat.cols; i++) {
		for (int j = i + 1; j < Mat.cols; j++) {
			temp_rate = Mat[j][i] / Mat[i][i];
			for (int k = 0; k < Mat.rows; k++) {
				Mat[j][k] -= Mat[i][k] * temp_rate;
				Mat[j][k] -= Mat[i][k] * temp_rate;
			}
			Mat[j][i] = 0;
		}
	}
	//使对角元素均为1
	for (int i = 0; i < Mat.cols; i++) {
		temp = Mat[i][i];
		for (int j = 0; j < Mat.rows; j++) {
			Mat[i][j] /= temp;
			Mat_Eye[i][j] /= temp;
		}
	}
	//将已经变为上三角矩阵的A，变为单位矩阵
	for (int i = Mat.cols - 1; i >= 1; i--) {
		for (int j = i - 1; j >= 0; j--) {
			temp = Mat[j][i];
			for (int k = 0; k < Mat.rows; k++) {
				Mat[j][k] -= Mat[i][k] * temp;
				Mat_Eye[j][k] -= Mat_Eye[i][k] * temp;
			}
		}
	}
	return Mat_Eye;//返回该矩阵的逆矩阵
}

ATM_Matrix ATM_Matrix::Tra(double(*pf)(double))
{
	ATM_Matrix Mat(cols, rows);
	for (int i = 0; i < Mat.cols; i++)
	{
		for (int j = 0; j < Mat.rows; j++)
		{
			Mat[i][j] = (*pf)(mat[i][j]);
		}
	}
	return Mat;
}

void ATM_Matrix::load(char * matFileName)
{
	FILE *fpLoad;
	errno_t err;
	err = fopen_s(&fpLoad, matFileName, "r");
	if (fpLoad == NULL)
	{
		return;
	}
	DeleteMatrix();
	fscanf_s(fpLoad, "%d", &cols);
	fscanf_s(fpLoad, "%d", &rows);
	CreatMatrix();
	for (int i = 0; i < cols; i++)
	{
		for (int ii = 0; ii < rows; ii++)
		{
			fscanf_s(fpLoad, "%lf", &mat[i][ii]);
		}
	}
	fclose(fpLoad);
}

void ATM_Matrix::save(char * matFileName)
{
	FILE *fpSave;
	errno_t err;
	err = fopen_s(&fpSave, matFileName, "w");
	if (fpSave == NULL)
	{
		return;
	}
	fprintf_s(fpSave, "%d ", cols);
	fprintf_s(fpSave, "%d\n", rows);
	for (int i = 0; i < cols; i++)
	{
		for (int ii = 0; ii < rows; ii++)
		{
			fprintf_s(fpSave, "%lf ", mat[i][ii]);
		}
		fprintf_s(fpSave, "\n");
	}
	fclose(fpSave);
}

//需要delete
double * ATM_Matrix::data()
{
	double *data = new double[cols*rows];
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			data[i*rows + j] = mat[i][j];
		}
	}
	return data;
}

void ATM_Matrix::data(double **matlis)
{
	//if ((*matlis) != nullptr)
	//{
	//	delete[] (*(matlis));
	//}
	//double *matlisOut = new double[cols*rows];
	(*matlis) = new double[cols*rows];
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			(*matlis)[i*rows + j] = mat[i][j];
		}
	}
	//*matlis = matlisOut;
}

bool ATM_Matrix::CreatMatrix()
{
	if (cols == 0 || rows == 0)
	{
		return false;
	}
	mat = new double*[cols];
	for (int i = 0; i < cols; i++)
	{
		mat[i] = new double[rows] {0};
	}

	return true;
}

bool ATM_Matrix::DeleteMatrix()
{
	if (mat == nullptr)
	{
		return false;
	}
	for (int i = 0; i < cols; i++)
	{
		delete[] mat[i];
	}
	delete[] mat;
	mat = nullptr;
	return true;
}

int ATM_Matrix::col()
{
	return cols;
}

int ATM_Matrix::row()
{
	return rows;
}

std::ostream & operator<<(std::ostream & out, ATM_Matrix & _Mat)
{
	for (int i = 0; i < _Mat.cols; i++)
	{
		for (int j = 0; j < _Mat.rows; j++)
		{
			out << _Mat[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
}

