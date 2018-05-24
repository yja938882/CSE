#include <iostream>
using namespace std;

int gcd( int a, int b ){
	int mod = a%b;
	while( mod >0 ){
		a = b;
		b = mod;
		mod = a%b;
	}
	return b;
}

void sol( int* arr, int N ){
	for( int i=1; i<N; i++ ){
		int gd = gcd( arr[0] , arr[i] );
		cout << arr[0]/gd <<"/" << arr[i]/gd <<"\n";
	}
}

int main( void ){
	int N;
	cin >> N;
	int r[N];
	for( int i=0; i<N; i++ ){
		cin >> r[i];
	}
	sol( r, N );
	return 0;

}
