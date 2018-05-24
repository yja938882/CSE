#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

int stk[10001];
int stop = -1;

void push( int a ){
	stk[++stop] = a;
}
int get_top(){
	return stk[stop];
}
bool is_sempty(){
	return stop == -1;
}
void pop(){
	--stop;
}
int get_ssize(){
	return stop+1;
}

int main( void ){
	int N;
	char input[100];
	scanf("%d",&N);
	for( int i=0; i<N; i++ ){
		scanf("%s",input);
		if( strcmp(input, "push" ) == 0 ){

			int a;
			scanf("%d",&a);
			push( a );

		}else if( strcmp( input, "top" ) == 0 ){

			if( is_sempty() ) printf("-1\n");
			else{
			 printf("%d\n" , get_top() );
			}

		}else if( strcmp( input, "size" ) == 0 ){

			printf("%d\n",get_ssize() );

		}else if( strcmp( input, "empty" ) == 0 ){

			if( is_sempty() ) printf("1\n");
			else printf("0\n");

		}else if( strcmp( input, "pop") == 0 ){
			
			if( is_sempty() ) printf("-1\n");
			else{
				printf("%d\n",get_top());
				pop();
			}

		}
	}

	return 0;
}

