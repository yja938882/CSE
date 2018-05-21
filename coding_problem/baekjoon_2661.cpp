#include <cstdio>
#include <iostream>
using namespace std;

bool is_bad( char *strs, int start, int end ){
	int len = end - start +1;
	int right = start+len/2;
	int left = start;
	int left_end = right -1;

	if( len %2 == 1 ) return false;

	while( left <= left_end && right <=end ){
		if( strs[left++] != strs[right++] ) return false;
	}

	return true;
}

bool dfs( char* strs, int in , char a, int N){
	strs[in] = a;	
	for( int i=0; i<=in; i++ ){
		if( is_bad( strs, i , in) ) return false;
	}
	if( in >= N-1 ){
		strs[in+1] = '\0';
		return true;
	}

	if( strs[in] == '1' ){
		if( dfs( strs, in + 1 , '2' , N ) ) return true;
		if( dfs( strs, in + 1 , '3' , N ) ) return true; 
	}else if( strs[in] == '2' ){
		if( dfs( strs, in + 1 , '1' , N ) ) return true;
		if( dfs( strs, in + 1 , '3' , N ) ) return true; 
	}else{
		if( dfs( strs, in + 1 , '1' , N ) ) return true;
		if( dfs( strs, in + 1 , '2' , N ) ) return true;
	}
	return false;
}

int main( void ){
	char strs[81];
	int N;
	cin >> N;
	dfs( strs, 0, '1' , N );
	printf("%s",strs);
	return 0;	
}
