#include <iostream>
#include <cstdio>
using namespace std;

void quicksort( int *arr, int left, int right ){
	int i = left;
	int j = right;
	int p = arr[(left+right)/2];
	while( i<= j ){
		while(arr[i]< p ) i++;
		while(arr[j]> p ) j--;
		if( j>= i ){
			swap( arr[i++] , arr[j--] );
		}
	}
	if( left < j ) quicksort( arr, left, j );
	if( i< right) quicksort( arr, i, right );
}

int main( void ){
	int N;
	scanf("%d",&N);
	int arr[N];
	for( int i=0; i<N; i++ ){
		scanf("%d",&arr[i]);
	}	
	quicksort( arr, 0, N-1 );
	for( int i=0; i<N; i++ ){
		printf("%d\n",arr[i]);
	}
	return 0;	
}
