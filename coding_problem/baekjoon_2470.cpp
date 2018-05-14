#include <cstdio>
#include <algorithm>
using namespace std;

int main( void ){
	int N;
	scanf("%d",&N);
	int arr[N];
	int rarr[N];
	for( int i=0; i<N; i++ ){
		scanf("%d",&arr[i]);
	}

	sort( arr, arr+N );	

	int min_sum = 2000000000;
	int left = 0;
	int right = N-1;
	int m_left;	
	int m_right;
	while(1){
		if( left >= right) break;
	
		int sum = arr[left] + arr[right];
		int absum = sum <0 ? -sum : sum;

		if( absum < min_sum ){
			min_sum = absum;
			m_left = left;
			m_right = right;
		}
		if( sum == 0 ) break;
		if( sum > 0 ) right --;		
		if( sum < 0 ) left ++;

	}
	printf("%d %d", arr[m_left], arr[m_right]);
	return 0;	
}
