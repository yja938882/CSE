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
int lcm( int a, int b ){
	return (a*b)/gcd( a, b );
} 

int main( void ){
	int T;
	cin >> T;
	for( int i=0; i<T; i++ ){
		int a, b;
		cin >> a >> b;
		cout << lcm( a, b) <<"\n";
	}
	return 0;
}
