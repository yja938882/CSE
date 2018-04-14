#include <iostream>
using namespace std;

int maximum_sub_arr( int * arr, int N ){
	int cur_sum = arr[0];
	int max_sum = arr[0];
	for( int i=1; i<N; i++ ){
		cur_sum = ( cur_sum + arr[i] > arr[i] ) ? ( cur_sum + arr[i] ) : arr[i];
		max_sum = ( max_sum > cur_sum ) ? max_sum : cur_sum;
	}
	return max_sum;
}

int main(void){
	int N;
	int * arr;
	cin>>N;
	arr = new int[N];
	for( int i=0; i<N; i++ ){
		cin >> arr[i];
	}
	cout<<maximum_sub_arr( arr, N );
	return 0;
}