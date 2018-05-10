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

int main( void ){
	
	int a, b;
	int g;
	cin >> a >> b;
	g = gcd( a, b );
	cout << g << "\n";
	cout << a*b/g <<"\n";
	return 0;
}
