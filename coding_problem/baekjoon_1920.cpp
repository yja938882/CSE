#include <iostream>
#include <algorithm>
using namespace std;

bool bin_search(int* arr, int left, int right, int target ){
	int mid = (left+right)/2;
	if( left > right) return false;
	if( arr[mid] == target ) return true;
	if( target > arr[mid]){
		return bin_search( arr, mid+1, right, target );
	}else
		return bin_search( arr, left, mid-1, target );
}


int main( void){
	int N, M;
	scanf("%d",&N);
	int arr[N];
	for( int i=0; i<N;i++){
		scanf("%d",arr+i);
	}
	sort(arr , arr+N);
	scanf("%d",&M);
	for( int i=0; i<M; i++){
		int in;
		scanf("%d",&in);
		if( bin_search( arr, 0, N-1, in ) )
			printf("1\n");
		else
			printf("0\n");	
	}
	
 	return 0;
}
