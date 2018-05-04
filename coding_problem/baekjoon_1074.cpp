#include <iostream>
#include <cmath>
using namespace std;
int sol( int N, int r, int c, int cnt ){
	if ( N<=1) return cnt;
	int cur_cnt = cnt;
	int before = 0;
	if( r >=N/2 ){
		before += 2;
	}
	if( c >=N/2 ){
		before += 1;
	}
	cur_cnt += (before)*(N/2)*(N/2);
	
	return sol( N/2 , r % (N/2), c % (N/2), cur_cnt );	
}


int main( void ){
	int N , r, c;

	cin >> N >> r >> c;
//	N *=2;
	N = (int)pow(2.0 , N);
	
	cout << sol( N, r, c, 0);
}
