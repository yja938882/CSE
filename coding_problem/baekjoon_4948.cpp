#include <iostream>
#include <cmath>
using namespace std;

bool is_prime( int n ) {
	for( int i=2; i<= sqrt(n); i++ ){
		if( n%i == 0 ) return false;
	}
	return true;
}

int main ( void){

	while(1){
		int n;
		scanf("%d",&n );
		if( n == 0 ) break;
		int cnt = 0;
		for( int i=n+1; i<=2*n; i++ ){
			if( is_prime( i ) ) cnt ++;
		}
		printf("%d\n",cnt);
	}
	return 0;
}
