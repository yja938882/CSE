#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int bin_search( int* ns, int left, int right, int f ){
	if( left > right ){
		return -1;
	}

	int mid = (left + right)/2;
	
	if( f == ns[mid] )	return 0;
	
	if( f > ns[mid] ){
		return bin_search( ns, mid+1, right , f);
	}
	return bin_search( ns, left, mid-1, f);
}

int main( void ){
	int N , M;

	scanf("%d",&N);

	int ns[500001];
	for( int i=0; i<N; i++ ){
		scanf("%d",ns+i);
	} 
	sort( ns , ns+N );	
	scanf("%d",&M);

	for( int i=0; i<M; i++ ){
		int m;
		scanf("%d",&m);
		if( bin_search( ns, 0, N-1, m ) == 0)
			printf("1 ");
		else
			printf("0 ");
	}
	return 0;
}
