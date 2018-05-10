#include <iostream>
using namespace std;
long long gcd( long long a, long long b ){
	int mod = a%b;
	while( mod >0 ){
		a = b;
		b = mod;
		mod = a%b;
	}
	return b;
}
long long lcm( long long a, long long b ){
	return (a*b)/gcd( a, b );
} 

int main( void ){
	
	long long a, b;
	cin >> a >> b;
	cout << lcm( a, b) <<"\n";
	return 0;
}
