#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long long_abs( long long a ){
	return a<0? a*(-1) : a;
}
int main( void ){
	int N;
	scanf("%d",&N);
	long long arr[N];
	for( int i=0; i<N; i++ ){
		scanf("%lld",&arr[i]);
	}
	sort( arr, arr+N );
	int mini=0,minj=1,mink=2;	
	long long minsum = 3000000000;
	for( int i=0; i< N-2; i++ ){
		int j = i+1;
		int k = N-1;	
		while( j<k ){
			long long sum = arr[i] + arr[j] + arr[k];
			if( long_abs(sum) < long_abs(minsum) ){
				minsum = sum;		
				mini = i;
				minj = j;
				mink = k;
			}
			if( sum == 0 ) break;
			else if( sum > 0 ) k--;
			else j++;
		}
	}
	printf("%lld %lld %lld",arr[mini], arr[minj], arr[mink] );

	return 0;
}
