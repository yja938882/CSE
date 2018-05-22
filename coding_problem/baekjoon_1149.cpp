#include <cstdio>
using namespace std;

int main( void ){
	int N;

	scanf("%d",&N);
	int arr[N][3];
	int dp[N][3];


	for( int i=0; i<N; i++ ){
		scanf("%d %d %d",&arr[i][0], &arr[i][1], &arr[i][2] );
	}

	dp[0][0] = arr[0][0];
	dp[0][1] = arr[0][1];
	dp[0][2] = arr[0][2];

	for( int i=1; i<N; i++ ){
		dp[i][0] = dp[i-1][1] > dp[i-1][2] ? dp[i-1][2]+arr[i][0] : dp[i-1][1] + arr[i][0];
		dp[i][1] = dp[i-1][2] > dp[i-1][0] ? dp[i-1][0]+arr[i][1] : dp[i-1][2] + arr[i][1];
		dp[i][2] = dp[i-1][1] > dp[i-1][0] ? dp[i-1][0]+arr[i][2] : dp[i-1][1] + arr[i][2];
	}

	int mind = dp[N-1][0];

	for( int i= 1; i<3; i++ ){
		if( mind > dp[N-1][i] ){
			mind = dp[N-1][i];
		}
	}
	printf("%d",mind);
	return 0;
}
