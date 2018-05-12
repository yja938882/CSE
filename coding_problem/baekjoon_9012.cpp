#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
char stack[51];
int top = -1;
void push( char a ){
	stack[ ++top ] = a;
}
void pop(){
	top --;
} 
bool isEmpty(){
	return top == -1;
}
int getTop(){
	return stack[top];
}
bool isVPS( char* strs ){
	int len = strlen( strs );	
	top = -1;
	for( int i=0; i< len; i++ ){
		switch( strs[i] ){
			case '(':
				push( strs[i] );
				break;
			case ')':
				if( isEmpty() ) return false;
				if( getTop() == '(' ) pop();
				else
					return false;	
				break;
		}	
	}
	return isEmpty();
}

int main( void ){
	int T;
	cin >> T;
	char buf[51];
	for( int i=0; i<T; i++ ){
		scanf("%s",buf);
		if( isVPS( buf ) ) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
