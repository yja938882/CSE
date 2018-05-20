#include <iostream>
using namespace std;

int main( void ){
	int N;
	cin >> N;
	int kg[N];
	int cm[N];
	for( int i=0; i<N; i++ ){
		cin >> kg[i] >> cm[i];
	}
	for( int i=0; i< N; i++ ){
		int cnt = 1;
		for( int j=0; j<N; j++ ){
			if( j== i ) continue;
			if( kg[i] < kg[j] && cm[i] < cm[j] ) cnt ++;
		}
		cout << cnt <<" ";
	}
	return 0;
}
