#include <cstdio>
#include <cmath>
using namespace std;
bool arr[1000001];

int main( void ){
	int M, N;
	scanf("%d",&M);
	scanf("%d",&N);
	for( int i=1; i<=N; i++ ) arr[i] = true;
    arr[1] = false;
	for( int i=2; i<= sqrt(N)+1; i++ ){
		if(!arr[i]) continue;

		for( int k = i+1; k<=N; k++ ){
			if( k%i == 0 )
				arr[k] = false;
		}
	}
	for( int i=M; i<=N; i++ )
		if( arr[i] )
			printf("%d ",i );	 	
	return 0;
}
