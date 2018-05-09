#include <iostream>
#include <cmath>
using namespace std;
bool is_prime( int n ){
	double sqn = sqrt( n );
	if( n == 1 )
		return false;
	for( int i=2; i<= (int)sqn; i++ ){
		if( n%i == 0 )	return false;
	}
	return true;
}

int main( void ){
	int M,N;
	cin >> M >> N;
	int min =-1;
	int sum =0;
	for( int i = N; i>=M; i-- ){
		if( is_prime( i )){
			min = i;
			sum += i;
		}
	}
	if( min == -1){
	 	cout<< min ;	
		return 0;
	}
	cout << sum << "\n" << min;
}
