#include <iostream>
using namespace std;
int fibo( int n ) {
    int arr[n+1];
    arr[0] = 0;
    arr[1] = 1;
    for( int i=2; i<n+1; i++ ){
        arr[i] = arr[i-1]+arr[i-2];
    }
    return arr[n];
}
int main( void ){
	int n;
	cin >> n;
	cout << fibo( n );
}
