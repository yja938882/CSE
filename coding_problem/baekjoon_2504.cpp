#include <iostream>
#include <string.h>
#define OPEN_0 -1
#define CLOSE_0 -2
#define OPEN_1 -3
#define CLOSE_1 -4

using namespace std;

int stack[31];
int s_top = -1;
bool is_s_empty( ) {
	return s_top == -1;
}
void push( int i ){
	stack[ ++s_top ] = i;
}
void pop(){
	s_top --;
}
int top(){
	return stack[ s_top ];
}
/*
void print_stack(){
	for( int i=0; i<= s_top; i++ ){
		cout << stack[i] << " ";
	}
	cout <<"\n";
}
*/
int main( void ){
	int len = 0;
	char input[31];
	cin >> input;
	len = strlen( input );
		
	for ( int i=0; i<len; i++ ){
		int sum = 0;
		switch( input[i] ){
			case '(':
				push( OPEN_0 );
				break;
			case ')':
				if( is_s_empty() ){
					cout << "0";
					return 0;
				}
				if( top() == OPEN_0 ){
					pop();
					push( 2 );					
				}else{
					sum = 0;
					while( !is_s_empty() && top() !=OPEN_0 ){
						sum += top();
						pop();	
					}
					pop();
					push( sum *2);
				}
				break;
			case '[':
				push( OPEN_1 );
				break;
			case ']':
				if ( is_s_empty() ){
					cout << "0";
					return 0;
				}
				
				if( top() ==OPEN_1 ){
					pop();
					push( 3 );
				}else{
					sum = 0;
					while( !is_s_empty() && top() !=OPEN_1 ){
						sum += top();
						pop();
					}
					pop();
					push(sum*3);
				}
				break;	
		}
//		print_stack();
	}
	int ret = 0;
	while( !is_s_empty() ){
		int t = top();
		if( t < 0 ){
			cout <<"0";
			return 0;
		}
		ret += t;
		pop();
	}
	cout << ret;
	return 0;
}
