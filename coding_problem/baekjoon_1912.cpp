#include <cstdio>
using namespace std;

int main( void ){
	int n;
	scanf("%d",&n);

	int arr[n];

	for( int i=0; i<n; i++ ){
		scanf("%d",&arr[i]);
	}

	int max_sum = arr[0];
	int cur_sum = arr[0];
	for( int i=1; i<n; i++ ){
		cur_sum = ( cur_sum + arr[i] > arr[i] ) ? (cur_sum + arr[i] ) : arr[i];
		max_sum = cur_sum > max_sum ? cur_sum : max_sum;
	}
	printf("%d", max_sum);
	return 0;
}
