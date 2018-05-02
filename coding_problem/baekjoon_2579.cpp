#include <iostream>
using namespace std;

int sol( int * score, int n ){
	// 0 : 바로 뒤에 것을 밟았다 seq
	// 1 : 바로 뒤에 것은 밟지 않았다. useq
	int arr[2][n+1];

	for( int i=0; i<n+1; i++ ){
		arr[0][i] = 0;
		arr[1][i] = 0;
	}

	arr[0][1] = score[0];
	arr[1][1] = score[0];

	for( int i=2; i<n+1; i++){
		// i 번째 계단을 밟음 && i-1 은 안밟음
		arr[1][i] = arr[0][i-2] > arr[1][i-2] ? arr[0][i-2] : arr[1][i-2];

		// i 번째 계단을 밟음 && ㅑ-1 도 밟음
		arr[0][i] = arr[1][i-1] > arr[0][i-2] ? arr[1][i-1] : arr[0][i-2];

		arr[0][i] += score[i-1];
		arr[1][i] += score[i-1];
	}

	return 	arr[0][n] > arr[1][n] ? arr[0][n] : arr[1][n];
}

int main( void ){
	int N;
	cin >> N;

	int score[N];

	for( int i=0; i<N; i++ ){
		cin >> score[i];
	}
	cout << sol( score, N);

}