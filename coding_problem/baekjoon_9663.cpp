#include <iostream>
using namespace std;
int arr[15][15];

bool is_correct(int n, int pi, int pj){
	for( int i=0; i<n; i++)
		if( arr[i][pj] == 1 )
			return false;

	for( int j=0; j<n; j++)
		if( arr[pi][j] == 1 )
			return false;

	int i = pi;
	int j = pj;
	for( ; i>=0 && j>=0; ){
		if( arr[i][j] == 1 )
			return false;
		i--;
		j--;
	}
	i = pi;
	j = pj;
	for( ; i<n && j<n; ){
		if( arr[i][j] == 1)
			return false;
		i++;
		j++;	
	}
	i = pi;
	j = pj;
	for( ; i<n && j>=0; ){
		if( arr[i][j] ==1)
			return false;
		i++;
		j--;
	}
	i = pi;
	j = pj;
	for( ; i>=0 && j<n; ){
		if( arr[i][j] == 1)
			return false;
		i--;
		j++;
	}

	return true;
}

int n_queen( int n, int step){
	if( step>=n ) return 1;

	int sum =0;
	for( int j=0;j<n; j++ ){
		if( is_correct( n, j ,step ) ){
			arr[j][step] = 1;
			sum += n_queen( n, step+1);
			arr[j][step] = 0;
		} 
	}
	return sum;
}

int main( void ){
	int N;
	cin >> N;

	for( int i=0; i< N; i++)
		for( int j=0; j< N; j++)
			arr[i][j] = 0;

	cout << n_queen( N,0 );
	return 0;
}

