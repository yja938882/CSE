#include <iostream>
using namespace std;

int dp[10][10];

void init(){
	for( int i=0; i<10; i++ )
		for( int j=0; j<10; j++ )
			dp[i][j] = 0;

	for( int i=0; i<10; i++ ) dp[0][i] = 1;

	for( int i=1; i<10; i++ ){
		for( int j = 1; j< 10; j++ ){
			for( int k= 0; k<j; k++ )
				dp[i][j] += dp[i-1][k];
		}
	}
}

void next( int d, int diff ){
	if( d < 0 ) return;

	int sum =0;
	for( int i=0; i< 10; i++ ){
		sum += dp[d][i];
		if( sum!=0 && sum >= diff ){
			printf("%d",i);
			next( d-1, dp[d][i] - sum + diff );
			return;
		}
	}
}

void sol( int n ){
	n++;
	int sum = 0;
	for( int i=0; i<10; i++ ){
		for( int j=0;j<10; j++ ){
			sum += dp[i][j];
			if( sum >= n ){
				int diff = sum-n;
				printf("%d",j);
				next( i-1 ,dp[i][j] -  diff );
				return;
			}	
		}
	}
	printf("-1");
}

int main( void ){
	int n;
	cin >> n;

	init();
/*	for( int i=0; i<10; i++ ){
		for( int j= 0; j<10; j++ ){
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}
*/
/*	for( int i=0; i< 100; i++ ){
		sol(i);
		printf("\n");
	}
*/
	sol( n);

   return 0;


}


