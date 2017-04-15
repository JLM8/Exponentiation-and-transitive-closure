#ifndef _MATRIX_H
#define _MATRIX_H

//ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
//�������ݽṹ
//��ά����
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
	//��ȡi,j���������
	//ʧ�ܷ���-31415,�ɹ�����ֵ
	float read(int i,int j);
	//д��i,j���������
	//ʧ�ܷ���-1,�ɹ�����1
	int write(int i,int j,float val);

	void display();
};

//��ά������
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