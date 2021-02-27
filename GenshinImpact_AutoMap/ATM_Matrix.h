#pragma once
#include <iostream>

class ATM_Matrix
{
	int cols = 0;
	int rows = 0;
	double **mat = nullptr;

public:
	ATM_Matrix();
	~ATM_Matrix();

	ATM_Matrix(int _cols, int _rows);
	ATM_Matrix(int _cols, int _rows, double *lis);
	ATM_Matrix(int _cols, int _rows, double **lis);
	ATM_Matrix(const ATM_Matrix & Mat);
	ATM_Matrix(char *matFileName);

public:
	double at(int i, int j);

	bool reSet(int _cols, int _rows);
	bool reRand();
	bool reRand(double min, double max);
	bool reEye();
	bool reZeros();
	bool reRange();
	bool reRange(double min, double max);

	double Sum();
	double Avg();
	double Avg2();
	double Max();
	double Min();
	double D();
	ATM_Matrix col(int x);
	ATM_Matrix col(int xa, int xb);
	ATM_Matrix row(int y);
	ATM_Matrix row(int ya, int yb);

	double* operator[](int i);
	ATM_Matrix& operator=(const ATM_Matrix& _Mat);
	ATM_Matrix& operator=(const double& _m);
	ATM_Matrix operator+(const ATM_Matrix& _Mat);
	ATM_Matrix operator+(const double& _m);
	ATM_Matrix operator-();
	ATM_Matrix operator-(const ATM_Matrix& _Mat);
	ATM_Matrix operator-(const double& _m);
	ATM_Matrix operator^(const ATM_Matrix& _Mat)const;
	ATM_Matrix operator*(const ATM_Matrix& _Mat)const;
	ATM_Matrix operator*(const double& _m);
	ATM_Matrix operator/(const ATM_Matrix& _Mat);
	ATM_Matrix operator/(const double& _m);


	ATM_Matrix T();
	ATM_Matrix T(const ATM_Matrix & _Mat);
	ATM_Matrix I();
	ATM_Matrix I(const ATM_Matrix & _Mat);

	ATM_Matrix Tra(double(*pf)(double));

	void load(char* matFileName);
	void save(char* matFileName);

	double * data();
	void data(double **matlis);

	friend std::ostream & operator<<(std::ostream& out, ATM_Matrix &_Mat);
	//friend std::ostream & operator<<(std::ostream& out, ATM_Matrix _Mat);
private:
	bool CreatMatrix();
	bool DeleteMatrix();
public:
	int col();
	int row();
};

