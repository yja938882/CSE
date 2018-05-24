#include <cstdio>
#include <cmath>

using namespace std;

bool is_prime( int n ){
	for( int i=2; i<=sqrt(n); i++ ){
		if( n% i == 0 ) return false;
	}
	return true;
}

void sol( int n ){
	int s = n/2;
	for( int i=n/2;i>=2; i-- ){
		if( is_prime( i ) && is_prime( n- i ) ){
			printf("%d %d\n", i , n-i );
			return;	
		}
	}
	return;
}

int main( void ){
	int n;
	scanf("%d",&n);
	for( int i=0; i<n; i++ ){
		int a;
		scanf("%d",&a);
		sol( a );
	}
	return 0;
}
