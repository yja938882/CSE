#include <iostream>
#include <string>
#include <cstdio>
#include <string.h>
using namespace std;

void sol( char* cmd , char* input, int N ){
	int arr[N];
	int front = 0;
	int end = N-1;
	int way = 1;

	int i=0;
	char * tk = strtok( input,",[]");
	char* cmds = cmd;
	while( tk!=NULL){
		arr[i++] = atoi( tk );
		tk = strtok( NULL,",[]");
	}
	int temp;
	while( *cmds ){
		if( *cmds == 'R'){
			temp = front;
			front = end;
			end = temp;
			way = (( way ==1 ) ? 2: 1);
		}else{
			if( way == 1 && front > end ){
				printf("error\n");
				return;
			}
			if ( way == 2 && front < end ){
				printf("error\n");
				return;
			}
			if ( way == 1) front ++;
			else front --;
		}
		cmds++;
	}
	printf("[");
	if( way == 1){
		for( i= front ; i<= end ; i++ ){
			printf("%d",arr[i]);
			if( i!=end ) printf(",");
		}
	}
	if( way == 2){
		for( i= front ; i>= end ; i-- ){
			printf("%d",arr[i]);
			if( i!=end ) printf(",");
		}
	}
	printf("]\n");
}

int main( void ){
	int T;
	cin >> T;
	char cmd_buf[100002];
	char input_buf[300002];
	for ( int t=0; t<T; t++ ){
		scanf("%s",cmd_buf);
		
		int N;
		cin >> N;
		
		scanf("%s",input_buf);
		sol( cmd_buf, input_buf, N );		
	}
	return 0;
}
