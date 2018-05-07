#include <iostream>
using namespace std;
int **arr;
bool **visited;
long long **count_v;

int main( void ){
	int N;
	cin >> N;

	arr = new int*[N];
	visited = new bool*[N];
	count_v = new long long*[N];
	for( int i=0; i<N; i++ ){
		arr[i] = new int[N];
		visited[i] = new bool[N];
		count_v[i] = new long long [N];
	}

	for( int i=0; i<N; i++ ){
		for( int j=0; j<N; j++ ){
			cin >> arr[i][j];
			visited[i][j] = false;
			count_v[i][j] = 0;
		}
	}
	count_v[0][0] = 1;
	for( int i=0; i<N; i++){
		for( int j=0; j<N; j++ ){
			if( count_v[i][j] == 0 ) continue;
			int d = arr[i][j];
			if( d == 0) continue;
			if( i+d < N ){
				count_v[i+d][j] += count_v[i][j];
			}
			if( j+d < N ){
				count_v[i][j+d] += count_v[i][j];
			}
		}

	}
	
	cout << count_v[N-1][N-1];
	return 0;
}
