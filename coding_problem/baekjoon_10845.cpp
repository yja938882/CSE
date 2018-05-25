#include <cstdio>
#include <string.h>
using namespace std;
int queue[10001];
int qfront = 0;
int qend = 0;
void push( int a ){
	queue[qend++] = a;
}

int empty(){
	return qend <= qfront ? 1 : 0;
}
int front(){
	return empty() == 1 ? -1 : queue[qfront];
}
int back(){
	return empty() == 1 ? -1 : queue[qend-1];
}
int size(){
	if( empty() ) return 0;
	return qend - qfront;
}
int pop(){
	if( empty() == 1 ) return -1;
	return queue[qfront++];
}
char input[100];
int main( void ){

	int N;
	scanf("%d",&N);

	for( int i=0; i<N; i++ ){
		scanf("%s",input);
		if( strcmp( input, "push" )==0 ){
			int a;
			scanf("%d",&a);
			push(a);
		}else if ( strcmp( input, "pop" )==0 ){
			printf("%d\n",pop());
		}else if( strcmp( input, "size" ) == 0 ){
			printf("%d\n",size());
		}else if ( strcmp( input, "empty" ) == 0 ){
			printf("%d\n",empty());
		}else if( strcmp( input, "front" ) == 0 ){
			printf("%d\n",front());
		}else if( strcmp( input, "back" ) == 0 ){
			printf("%d\n",back());
		}
	}
	return 0;
}
