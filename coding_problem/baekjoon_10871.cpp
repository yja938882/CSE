#include <iostream>
using namespace std;
int main ( void ){
	int N, X;
	cin >> N >> X;
	int arr[N];
	for( int i=0; i<N; i++ ){
		int a;
		cin >> a;	
		if( a < X ) cout << a <<" ";
	}	
	return 0;
}
