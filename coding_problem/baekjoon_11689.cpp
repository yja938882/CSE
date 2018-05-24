#include <iostream>
using namespace std;

long long GCD( long long a, long long b ){
	long long mod = a % b;
	while( mod > 0 ){
		a = b;
		b = mod;
		mod = a%b;
	}
	return b;
}

int main( void ){
	long long n;
	cin >> n;
	long long cnt = 0;
	for( long long i=1; i<=n; i++ ){
		if( GCD( i, n ) == 1 ) cnt ++; 
	}
	cout << cnt;

	return 0;
}
