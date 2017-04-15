#include "_Matrix.h"
#include<iostream>
using namespace std;
//矩阵类方法
//初始化
_Matrix::_Matrix(int mm,int nn){
	m = mm;
	n = nn;
	arr = new float[m * n];
}

//设置m
void _Matrix::set_m(int mm){
	m = mm;
}

//设置n
void _Matrix::set_n(int nn){
	n = nn;
}

//初始化
void _Matrix::init_matrix(){
	
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			*(arr + i * n + j)=0;

}

//释放
void _Matrix::free_matrix(){
	delete arr;
}


float _Matrix::read(int i,int j){
	if (i >= m || j >= n){
		cout<<"read i "<<i<<" j "<<j<<"  The data for reading have some wrong..."<<endl;
		system("pause");
		return 2222;
	//不知如何停止程序
	}else
		return *(arr + i * n + j);
}

//写入i,j坐标的数据
//失败返回-1,成功返回1
int _Matrix::write(int i,int j,float val){
	if (i >= m || j >= n){
		cout<<"The data for writing have some wrong..."<<endl;
	}
	
	*(arr + i * n + j) = val;
	return 1;
}


void _Matrix::display(){
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++)
			cout<<*(arr+i*n +j)<<"\t";
		cout<<endl;
	}
}


_Matrix_Calc::_Matrix_Calc(){
}


//C = A * B
//成功返回1,失败返回-1
void _Matrix_Calc::multiply(_Matrix &A,_Matrix &B,_Matrix &C){
	//判断是否可以运算
	if (A.m != C.m || B.n != C.n || A.n != B.m){
			cout<<"The data of your Matrix for Multiply have some wrong..."<<endl;

	}else{
		//运算
		for (int i = 0;i < C.m;i++){
			for (int j = 0;j < C.n;j++){
				int temp = 0;
				for (int k = 0;k < A.n;k++){
					temp += A.read(i,k) * B.read(k,j);
				}
				if(temp>0)
					temp=1;
				C.write(i,j,temp);
			}
		}
		//cout<<"The Multiply have been finished!"<<endl;
	}	
}
void _Matrix_Calc::Matrix_copy(_Matrix & A, _Matrix & B){
	B.m=A.m;
	B.n= A.n;
	B.init_matrix();
	for(int i=0; i<B.m; i++)
		for(int j=0; j<B.n; j++)
			B.write(i,j,A.read(i,j));
}

void _Matrix_Calc::Power_calc(_Matrix & A, int n){
	_Matrix temp_arr_root(A.m,A.n);
	temp_arr_root.init_matrix();
	Matrix_copy(A,temp_arr_root);

	if(n==0){
		temp_arr_root.init_matrix();
		for(int i=0; i<A.m; i++)
			temp_arr_root.write(i,i,1);
	}else if(n==1){
	}else{
		for(int i=1; i<n; i++){
			_Matrix temp_arr(A.m,A.n);
			temp_arr.init_matrix();
			
			multiply(temp_arr_root,A,temp_arr);

			Matrix_copy(temp_arr,temp_arr_root);
			temp_arr.free_matrix();
		}	
	}

	Matrix_copy(temp_arr_root,A);
	temp_arr_root.free_matrix();
}

bool _Matrix_Calc::Matrix_equality(_Matrix& A,_Matrix& B){
	bool equality=true;
	if(A.m!=B.m || A.n!=B.n)
		equality=false;
	else{
		for(int i=0; i<A.m; i++){
			for(int j=0; j<A.n; j++)
				if(A.read(i,j)!=B.read(i,j)){
					equality=false;
					break;
				}
             if(equality==false)
				 break;
		}
     return equality;
}
}