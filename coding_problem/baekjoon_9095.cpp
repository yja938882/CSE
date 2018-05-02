#include <iostream>
using namespace std;
int sol( int n ){
	int arr[n+1];
	for(int i=0;i<n+1; i++)
		arr[i] = 0;
	arr[0] = 1;
	for( int i=1; i< n+1; i++ ){
		int sum = 0;
		for( int j=1; j<=3; j++ ){
			if( i-j >= 0)
				sum += arr[i-j];
		}
		arr[i] = sum;
	}
	return arr[n];
}

int main(void){
	int T;
	cin >> T;

	for( int i=0; i<T; i++ ){
		int n;
		cin >> n;
		cout << sol( n )<<"\n";
	}
}
