#include <iostream>
#include <cmath>
using namespace std;

long long sol( long long min, long long max ){
	bool ch[1000003 ];
	long long cnt = 0;
	for( int i=0; i< 1000003; i++ ) ch[i] = false;

	for( long long i=2; i<= sqrtl( max )+1 ; i++ ){
		long long j = i*i;
		long long k = min/j;
		for( ; j*k <=max; k++ ){
			if( j*k-min >=0 && !ch[j*k - min]){
				ch[ j*k -min ] = true;
				cnt++;
			}	
		}
	}

	return max-min+1 - cnt;
}

int main( void ){
	long long min, max;
	cin >> min >> max;
	cout << sol( min, max );
	return 0;
}
