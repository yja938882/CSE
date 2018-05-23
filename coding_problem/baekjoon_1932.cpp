#include <cstdio>
using namespace std;

int main ( void ){
	int n;
	scanf("%d",&n);
	int arr[n][n];
	int dp[n][n];
	for( int i=0; i<n; i++ ){
		for( int j=0; j<=i ;j++ ){
			scanf("%d",&arr[i][j]);
			dp[i][j] = arr[i][j];
		}		
	}
	
	for( int i=0; i<n-1; i++ ){
		for( int j=0; j<=i; j++ ){
			int left = j;
			int right = j+1;
			if( dp[i+1][left] < dp[i][j] + arr[i+1][left] )
				dp[i+1][left] = dp[i][j] + arr[i+1][left];	
			if( dp[i+1][right] < dp[i][j] + arr[i+1][right] )
				dp[i+1][right] = dp[i][j] + arr[i+1][right];
		}	
	}
	int maxv = 0;
	for( int i=0; i<n; i++ ){
		if( dp[n-1][i] > maxv ) 
			maxv = dp[n-1][i];
	}
	printf("%d",maxv);
	return 0;
}
