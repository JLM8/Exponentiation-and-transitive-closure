#include<iostream>
#include"_Matrix.h"

using namespace std;

int main(){
	//输入集合A的大小 并创建合法的集合A
	cout<<"Please input the size of Gather A..."<<endl;
	int size=0;
	cin>>size;
	cout<<"The size of Gather A is "<<size<<"."<<endl;
	int *A = new int[size];
	cout<<endl;
	//向集合A中填充元素 并判断合法（没有重复），否则重复填充
	cout<<"Please input the elements of Gather A..."<<endl;
	bool Gather_legal = true;
	do{
		for(int i=0; i<size; i++)
			cin>>A[i];
		for(int i=0; i<size; i++){
			for(int j=i+1; j<size; j++)
				if(A[i]==A[j]){
					Gather_legal = false;
					break;
				}else
					Gather_legal = true;
			if(Gather_legal == false)
				break;
		}

		if(Gather_legal == false){
			cout<<"Your can't input the same elements in Gather A!"<<endl;
			cout<<"Please re-input  elements..."<<endl;
		}
	}while(Gather_legal == false);
	//打印集合A
	cout<<"Gather A is"<<endl;
	for(int i=0; i<size; i++)
		cout<<A[i]<<" ";
	cout<<endl;
	cout<<"----------------------------------------------------------"<<endl;
	//创建矩阵A*A
	_Matrix arr(size,size);
	arr.init_matrix();
	//a.display();
	//输入集合R的大小
	int sizeR=0;
	cout<<"Please input the size of Gather R"<<endl;
	cin >> sizeR;
	//分别输入R中元素 并判断是否合法 不合法重新输入 最后填充在矩阵A*A中
	for(int i=0; i<sizeR; i++){
		int Rx=0,Ry=0;
		cout<<"Please input X Y of Group R "<<i+1<<endl;

		bool Rx_legal = false, Ry_legal = false;
		do{
			cin>>Rx>>Ry;
			for(int j=0; j<size; j++)
				if(A[j]==Rx){
					Rx_legal = true;
					break;
				}else
					Rx_legal = false;
				if(Rx_legal == true)
					for(int j=0; j<size; j++)
						if(A[j]==Ry){
							Ry_legal = true;
							break;
						}else
							Ry_legal = false;
						
						if(Rx_legal == false || Ry_legal == false){
							cout<<"Your XY can't have the element which isn't in Gather A!"<<endl;
							cout<<"Please re-input your X Y of Group R "<<i+1<<endl;
						}
		}while(Rx_legal == false || Ry_legal == false);
		
		int x=0, y=0;
		for(int i=0; i<size; i++){
			if(Rx==A[i])
				x=i;
		}
		for(int i=0; i<size; i++){
			if(Ry == A[i])
				y=i;
		}
		
		arr.write(x,y,1);
	}
	cout<<"Matrix is"<<endl;
	arr.display();
	//输入幂次
	int power = 0;
	cout<<"Please input the power of Matrix.."<<endl;
	do{
		cin>>power;
		if(power<0){
			cout<<"The Power must be 0 or positive number!"<<endl;
			cout<<"Please re-input the power..."<<endl;
		}
	}while(power<0);
	
	//进行n次幂运算
	_Matrix_Calc cal;
	_Matrix temp_arr_root(size,size);
	temp_arr_root.init_matrix();
	cal.Matrix_copy(arr,temp_arr_root);

	bool equality = false;
	int num=0;
	int dis=0;
	if(power==0){
		temp_arr_root.init_matrix();
		for(int i=0; i<temp_arr_root.m; i++)
			temp_arr_root.write(i,i,1);
	}else if(power==1){
	}else{
		for(int i=2; i<=power; i++){
			_Matrix temp_arr(temp_arr_root.m,temp_arr_root.n);
			temp_arr.init_matrix();
			
			cal.multiply(temp_arr_root,arr,temp_arr);

			cal.Matrix_copy(temp_arr,temp_arr_root);
			temp_arr.free_matrix();
			//cout<<"i "<<i;
			//检查是否循环
			_Matrix temp_arr_root2(size,size);
			temp_arr_root2.init_matrix();
			cal.Matrix_copy(arr,temp_arr_root2);
			
			for(int j=1; j<=(i-1); j++){
				_Matrix temp_arr2(temp_arr_root2.m,temp_arr_root2.n);
			    temp_arr2.init_matrix();

				if(j==1){
					cal.Matrix_copy(arr,temp_arr_root2);
				}else if(j>1){
					cal.multiply(temp_arr_root2,arr,temp_arr2);
				    cal.Matrix_copy(temp_arr2,temp_arr_root2);
				    temp_arr2.free_matrix();
				}
				//cout<<" j "<<j<<endl;
				if(cal.Matrix_equality(temp_arr_root,temp_arr_root2)){
					num=j;
					dis=i-j;
					cout<<"With circulation,start "<<num<<" distance "<<dis<<endl;
					equality = true;
					break;
				}
			}
			
			if(equality==true)
				break;
		}
	}

	if(equality == true){
		_Matrix temp_arr_root3(size,size);
	    temp_arr_root3.init_matrix();
	    cal.Matrix_copy(arr,temp_arr_root3);
		
		for(int i=1; i<=(num+(power-num)%dis); i++){
			_Matrix temp_arr3(temp_arr_root3.m,temp_arr_root3.n);
			temp_arr3.init_matrix();
			
			if(i==1){
				cal.Matrix_copy(arr,temp_arr_root3);
			}else if(i>1){
				cal.multiply(temp_arr_root3,arr,temp_arr3);
				cal.Matrix_copy(temp_arr3,temp_arr_root3);
			    temp_arr3.free_matrix();
			}
		}
		cal.Matrix_copy(temp_arr_root3,temp_arr_root);
		temp_arr_root3.free_matrix();
	}
	
			
	

	cout<<"Have calculated..."<<endl;
	cout<<"The result is"<<endl;
	temp_arr_root.display();
	cout<<"---------------------------------"<<endl;
	
//Warshall算法 计算传递闭包
	cal.Matrix_copy(arr,temp_arr_root);

	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++){
			if(temp_arr_root.read(j,i)==1){
				for(int k=0; k<size; k++){
					int temp=0;
				    temp = temp_arr_root.read(j,k)+temp_arr_root.read(i,k);
					if(temp>1)
						temp=1;
					temp_arr_root.write(j,k,temp);
				}
			}
		}
  //打印传递闭包  
	cout<<"Transitive Closure = {";
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			if(temp_arr_root.read(i,j)==1)
				cout<<"<"<<A[i]<<","<<A[j]<<">,";
	cout<<"}."<<endl;
	 
	//释放空间
	temp_arr_root.free_matrix();
	arr.free_matrix();
	delete A;

	system("pause");
	return 0;
}