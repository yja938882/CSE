#include <cstdio>
using namespace std;

void merge_p( int* arr, int m , int l , int r ){
	int mid =( l + r )/2; 
	
	

}

void merge( int* arr, int l , int r ){
	int m = ( l+r )/2;
	if( l <= r ){
		merge_p( arr, l, m-1 );
		merge_p( arr, m+1, r );
	}
}

int main( void ){
	int N , M;

	scanf("%d",&N);
	scanf("%d",&M);
	
	int arr[N];


	return 0;
}
