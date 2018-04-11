#include <iostream>
#include <climits>
using namespace std;
int maximum = -INT_MAX;
int minimum = INT_MAX;

/**
	@param opr1 operand 1 
	@param opr2 operand 2
	@param op operation code. 0 (+) , 1 (-), 2(*) , 3(/)
	@return result of operation.
*/
int operation( int opr1, int opr2 , int op){
	int error = -1;
	switch(op){
		case 0: // +
			return opr1 + opr2;
		case 1: // -
			return opr1 - opr2;
		case 2: // *
			return opr1 * opr2;
		case 3: // %
			return opr1 / opr2;
	}
	return error;
}

/**
	@param cur current operand ( first operand )
	@param op remain operations
	@param remain remain step
	@param index second operand index
	@param arr array of operands
	@brief each step, operation from first to last
*/
void step( int cur, int * op , int remain ,int index, int* arr){
	if(remain <= 0){
		if( maximum < cur) maximum = cur;
		if( minimum > cur) minimum = cur;
		return;
	}

	for( int i=0; i<4; i++){
		if( op[i] >0 ){
			op[i] --;
			step( operation( cur, arr[index] , i) , op, remain -1 , index+1 , arr);
			op[i] ++;
		}
	}
}

int main(void){
	int N;
	int *arr;
	int *op;
	cin>>N;

	op = new int[4];
	arr = new int[N];
	for( int i=0; i<N; i++ ){
		cin >> arr[i];
	}
	for( int i=0; i<4; i++ ){
		cin >> op[i]; 
	}
	step( arr[0] , op , N-1 , 1, arr);
	cout<<maximum<<"\n"<<minimum;

	return 0;
}