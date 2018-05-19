#include <iostream>
using namespace std;

unsigned long long GCD( unsigned long long a, unsigned long long b ){
	unsigned long long mod = a%b;
	while( mod > 0 ){
		a = b;
		b = mod;
		mod = a%b;
	}
	return b;
}

int main( void ){
	unsigned long long a;
	unsigned long long b;
	cin >> a >> b;
	unsigned long long gd = GCD( a, b );
	for( unsigned long long i= 0; i< gd; i++ ){
		cout<<"1";
	}
	return 0;
}
