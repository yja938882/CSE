#include <cstdio>
using namespace std;

char arr[25][26];
int num[25][25];

void sol( ) {

}



int main( void ){
	int N;
	scanf("%d",&N);

	for( int i=0; i<25; i++ )
		for( int j=0; j<25; j++ )
			num[i][j] = 0;
	
	for( int i=0; i<N; i++ ){
		scanf("%s",arr[i] );
	}

	return 0;
}
