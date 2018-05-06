#include <iostream>
using namespace std;

void heapify( int* arr, int size, int root ){
	int left = ( root + 1 )*2 -1;
	int right = ( root + 1)*2;
	int largest = root;
	
	if( left < size && arr[ left ] > arr[ largest ] ){
		largest = left;
	}

	if( right < size && arr[ right ] > arr[ largest ] ){
		largest = right;
	}

	if( largest != root ){
		swap( arr[root] , arr[ largest ] );
		heapify( arr, size, largest );
	}
}

void heap_sort( int * arr, int size ){
	for( int i= size/2 -1; i>=0; i --){
		heapify( arr, size, i );
	}
	for( int i= size-1; i>=0 ; i-- ){
		swap( arr[0], arr[i] );
		heapify( arr, i, 0 );
	}
}



int main( void ){
	int N;
	cin >> N;
	int arr[N];
	for ( int i=0; i<N; i++ ){
		cin >> arr[i];
	}
	heap_sort( arr, N );
	for( int i=0; i<N; i++ ){
		cout << arr[i] <<" ";
	}
	return 0;
}
