#include <iostream>
using namespace std;
#define DIV_N 1000000000

long long dp[1000001];

long long sol ( long long N ){
	dp[0] = 0;
	dp[1] = 0;
	dp[2] = 1;
	for( int i=3; i<=N; i++ ){
		dp[i] =( ((i-1)*dp[i-1]) % DIV_N + ((i-1)*dp[i-2]) % DIV_N ) % DIV_N;
	}
	return dp[N];
}

int main ( void ){
	long long N;
	cin >> N;
	cout << sol( N);
}
