#include <iostream>
using namespace std;

int get_digit_sum( int n ){
	int cur = n;
	int sum = 0;
	while( cur > 0 ){
		sum += cur%10;
		cur/=10;
	}
	return sum;
}

int get_ctr( int n ){
	int m = 2;
	for( int i=n/2; i<= n ;i++ ){
		m = i+get_digit_sum(i);
		if( m == n )
			return i;
	}
	return 0;
}

int main( void ){
	int N;
	cin >> N;

	cout << get_ctr( N );
	return 0;
}
