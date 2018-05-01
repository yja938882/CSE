#include <iostream>
using namespace std;

int main( void ){
	int N;
	cin >> N;

	int count[N+1];

	count[1] = 0;

	for( int i=2; i< N+1; i++ ){
		count[i] = count[i-1];

		if( i%3 == 0 ){
			if( count[i] > count[i/3] ){
				count[i] = count[i/3];
			}
		}
		if( i%2 == 0 ){
			if( count[i] > count[i/2] ){
				count[i] = count[i/2];
			}
		}
		count[i] ++;
	}
	cout << count[N];
}
