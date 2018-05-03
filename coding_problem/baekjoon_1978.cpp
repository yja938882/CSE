#include <iostream>
using namespace std;

bool is_prime( int n ){
	if( n == 1)
		return false;
	for( int i=2; i<= n/2; i++ ){
		if( n%i == 0) return false;
	}
	return true;
}

int main( void ){
	int N;
	cin >> N;
	int arr[N];
	int cnt = 0;
	for( int i=0; i<N; i++){
		cin >> arr[i];
		if( is_prime( arr[i] ) )
			cnt ++;
	}
	cout << cnt;

}
