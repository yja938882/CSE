#include <iostream>
using namespace std;

int* counting_sort( int* arr, int N, int K){
	int counter[K+1];
	int *result = new int[ N ]; 
	for( int i=0; i<K+1; i++){
		counter[i] = 0;
	}
	for( int i=0; i<N; i++){
		counter[ arr[i] ]++;
	}
	int index = 0;
	for( int i=0; i< K; i++){
		counter[i+1] += counter[i];
	}
	for( int j= K; j>=0; j--){
		result[ counter[ arr[j] ]-1 ] = arr[j];
		counter[ arr[j]]--;
	}
	return result;
}

int main(void){
	int K = -1;
	int N;
	cin >> N;
	int *arr = new int[ N ];
	for(int i=0;i<N;i++){
		cin>>arr[i];
		if(K<arr[i])
			K = arr[i];
	}
	int *result = counting_sort( arr, N, K);

	for( int i=0;i<N;i++){
		cout<<result[i]<<" ";
	}
}
