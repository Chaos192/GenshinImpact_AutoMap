#pragma once
#include <iostream>

class ATM_MatrixD
{
	int cols = 0;
	int rows = 0;
	double **mat = nullptr;

public:
	ATM_MatrixD();
	~ATM_MatrixD();

	ATM_MatrixD(int _cols, int _rows);
	ATM_MatrixD(int _cols, int _rows, double *lis);
	ATM_MatrixD(int _cols, int _rows, double **lis);
	ATM_MatrixD(const ATM_MatrixD & Mat);
	ATM_MatrixD(char *matFileName);

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
	ATM_MatrixD col(int x);
	ATM_MatrixD col(int xa, int xb);
	ATM_MatrixD row(int y);
	ATM_MatrixD row(int ya, int yb);

	double* operator[](int i);
	ATM_MatrixD& operator=(const ATM_MatrixD& _Mat);
	ATM_MatrixD& operator=(const double& _m);
	ATM_MatrixD operator+(const ATM_MatrixD& _Mat);
	ATM_MatrixD operator+(const double& _m);
	ATM_MatrixD operator-();
	ATM_MatrixD operator-(const ATM_MatrixD& _Mat);
	ATM_MatrixD operator-(const double& _m);
	ATM_MatrixD operator^(const ATM_MatrixD& _Mat)const;
	ATM_MatrixD operator*(const ATM_MatrixD& _Mat)const;
	ATM_MatrixD operator*(const double& _m);
	ATM_MatrixD operator/(const ATM_MatrixD& _Mat);
	ATM_MatrixD operator/(const double& _m);


	ATM_MatrixD T();
	ATM_MatrixD T(const ATM_MatrixD & _Mat);
	ATM_MatrixD I();
	ATM_MatrixD I(const ATM_MatrixD & _Mat);

	ATM_MatrixD Tra(double(*pf)(double));

	void load(char* matFileName);
	void save(char* matFileName);

	double * data();
	void data(double **matlis);

	friend std::ostream & operator<<(std::ostream& out, ATM_MatrixD &_Mat);
	//friend std::ostream & operator<<(std::ostream& out, ATM_MatrixD _Mat);
private:
	bool CreatMatrix();
	bool DeleteMatrix();
public:
	int col();
	int row();
};

class ATM_MatrixI
{
	int cols = 0;
	int rows = 0;
	int **mat = nullptr;

public:
	ATM_MatrixI();
	~ATM_MatrixI();

	ATM_MatrixI(int _cols, int _rows);
	ATM_MatrixI(int _cols, int _rows, int *lis);
	ATM_MatrixI(int _cols, int _rows, int **lis);
	ATM_MatrixI(const ATM_MatrixI & Mat);
	ATM_MatrixI(char *matFileName);

public:
	int at(int i, int j);
	void set(int i, int j,int value);

	bool reSet(int _cols, int _rows);
	bool reRand();
	bool reRand(int min, int max);
	bool reEye();
	bool reZeros();
	bool reRange();
	bool reRange(int min, int max);

	int Sum();
	double Avg();
	double Avg2();
	int Max();
	int Min();
	double D();
	ATM_MatrixI col(int x);
	ATM_MatrixI col(int xa, int xb);
	ATM_MatrixI row(int y);
	ATM_MatrixI row(int ya, int yb);

	int* operator[](int i);
	ATM_MatrixI& operator=(const ATM_MatrixI& _Mat);
	ATM_MatrixI& operator=(const int& _m);
	ATM_MatrixI operator+(const ATM_MatrixI& _Mat);
	ATM_MatrixI operator+(const double& _m);
	ATM_MatrixI operator-();
	ATM_MatrixI operator-(const ATM_MatrixI& _Mat);
	ATM_MatrixI operator-(const double& _m);
	ATM_MatrixI operator^(const ATM_MatrixI& _Mat)const;
	ATM_MatrixI operator*(const ATM_MatrixI& _Mat)const;
	ATM_MatrixI operator*(const double& _m);
	ATM_MatrixI operator/(const ATM_MatrixI& _Mat);
	ATM_MatrixI operator/(const double& _m);


	ATM_MatrixI T();
	ATM_MatrixI T(const ATM_MatrixI & _Mat);
	ATM_MatrixI I();
	ATM_MatrixI I(const ATM_MatrixI & _Mat);

	ATM_MatrixI Tra(double(*pf)(double));

	void load(char* matFileName);
	void save(char* matFileName);

	int * data();
	void data(int **matlis);
	void copyTo(ATM_MatrixI _Mat);

	friend std::ostream & operator<<(std::ostream& out, ATM_MatrixI &_Mat);
	//friend std::ostream & operator<<(std::ostream& out, ATM_MatrixI _Mat);
private:
	bool CreatMatrix();
	bool DeleteMatrix();
public:
	int col();
	int row();
};

typedef ATM_MatrixI ATM_Matrix;