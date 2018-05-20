#include <iostream>
#include <string.h>
using namespace std;
bool isCorrect( int N ){
	if( N <= 99 ) return true;
	int  dif = (N/10)%10 - (N%10);// 2 - 1

	while( N/10 > 0 ){
		int new_dif = (N/10)%10 - (N%10);
		if( new_dif!= dif ) return false;
		N/=10;
	}
	return true;
}


int main( void ){
	int N;
	cin >> N;
	int cnt = 0;
	for( int i=1; i<=N; i++ ){
		if( isCorrect( i ) ) cnt++; 
	}
	cout << cnt;
	return 0;
}
