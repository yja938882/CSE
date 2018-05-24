#include <cstdio>
#include <algorithm>
using namespace std;

int main( void ){
	int N;
	scanf("%d",&N);
	int arr[N];

	for( int i=0; i<N; i++ ){
		scanf("%d",&arr[i]);
	}

	sort( arr, arr+N );			
	
	for( int i=1; i< N; i++ ){
		arr[i]+=arr[i-1];
	}
	int sum = 0;
	for( int i=0; i<N; i++ )
		sum += arr[i];
	printf("%d",sum);

	return 0;
}
