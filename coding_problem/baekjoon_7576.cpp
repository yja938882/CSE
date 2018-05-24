#include <cstdio>
#include <string>
using namespace std;
bool can_visit( int N, int M, int n, int m ){
	return ( N > n && n >=0 && M > m && m >=0 );
}
int glob_count = 0;
int glob_max = 0; 
void dfs(int ** arr, int N, int M, int n, int m, int p ){
	if( arr[n][m] != 0 ) return;
	arr[n][m] = p+1;
	
	if( can_visit( N, M, n-1, m ) )	dfs( arr, N, M, n-1, m ,p+1);
	
	if( can_visit( N, M, n, m-1 ) ) dfs( arr, N, M, n, m-1, p+1);
	
	if( can_visit( N, M, n+1, m ) ) dfs( arr, N, M, n+1, m, p+1);
	
	if( can_visit( N, M, n, m+1 ) ) dfs( arr, N, M, n , m+1, p+1);

}

int main( void ){
	int M, N;
	scanf("%d",&M);
	scanf("%d",&N);
	int arr** = new int*[N];
	for( int i=0; i<N; i++ ) arr[i] = new int[M];

	for( int i=0; i<N; i++ ){
		for( int j=0; j<M; j++ ){
			scanf("%d",&arr[i][j];
			if( arr[i][j] == 1 ) queue.push_back( make_pair( i, j ) );
		}
	}

	

}
