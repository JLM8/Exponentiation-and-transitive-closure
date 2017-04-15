#ifndef _MATRIX_H
#define _MATRIX_H

//头文件
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
//矩阵数据结构
//二维矩阵
class _Matrix{
private:
public:
	int m;
	int n;
	float *arr;
	
	_Matrix(int mm = 0,int nn = 0);
	
	void set_m(int mm);
	
	void set_n(int nn);
	
	void init_matrix();

	void free_matrix();
	//读取i,j坐标的数据
	//失败返回-31415,成功返回值
	float read(int i,int j);
	//写入i,j坐标的数据
	//失败返回-1,成功返回1
	int write(int i,int j,float val);

	void display();
};

//二维运算类
class _Matrix_Calc
{
private:
public:
	_Matrix_Calc();

	void multiply(_Matrix &A,_Matrix &B,_Matrix &C);
	void Power_calc(_Matrix& A,int n);
	void Matrix_copy(_Matrix& A,_Matrix& B);
	bool Matrix_equality(_Matrix& A,_Matrix& B);

};

#endif