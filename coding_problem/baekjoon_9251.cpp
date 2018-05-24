#include <cstdio>
#include <string.h>
using namespace std;
char input_a[1001];
char input_b[1001];

int main( void ){

	scanf("%s",input_a);
	scanf("%s",input_b);
	int alen = strlen( input_a );
	int blen = strlen( input_b );
	int arr[alen+1][blen+1];
	
	for( int i=0; i< alen+1; i++ )
		arr[i][0] = 0;
	for( int i=0; i< blen+1; i++ )
		arr[0][i] = 0;

	for( int i=1; i< alen+1; i++ ){
		for( int j=1; j< blen+1; j++ ){
			arr[i][j] = arr[i-1][j] > arr[i][j-1] ? arr[i-1][j] : arr[i][j-1];
			if( input_a[i-1] == input_b[j-1] )
				arr[i][j] = arr[i-1][j-1]+1;
		}
	}
//	for( int i=0; i<alen+1; i++){
//		for( int j=0; j<blen+1; j++ ){
//			printf("%d ",arr[i][j]);
//		}
//		printf("\n");
//	}

	printf("%d",arr[alen][blen]);
	return 0;
}
