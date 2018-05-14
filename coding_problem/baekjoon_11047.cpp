#include <iostream>
using namespace std;

int sol(int n , int k , int * arr , int c){
	if( k == 0)
		return c;
	int ret = k/ arr[n];

	if( ret == 0 ) return sol( n-1 , k, arr ,c);
		
	return sol( n-1, k - ret*arr[n] , arr , c + ret);
}

int main( void ){
	int N, K;
	cin >> N >> K;
	int coin[N];
	for( int i=0; i<N; i++ ){
		cin >> coin[i];
	}	
	cout << sol( N-1, K , coin , 0 );	
}
