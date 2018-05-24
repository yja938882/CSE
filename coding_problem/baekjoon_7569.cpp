#include <iostream>
#include <string>
#include <vector>
using namespace std;
int ** arr;
bool** visited;
vector< pair< int, int > > tms;

void bfs(){
}

int main( void ){
	int M, N;
	cin >> M >>N;
	arr = new int*[N];
	visited = new bool*[N];
	for( int i=0; i<N; i++ ){
		arr[i] = new int[M];
		vosoted[i] = new bool[M];
	}
	for( int i=0; i<N; i++ ){
		for( int j=0; j<M; j++ ){
			cin >> arr[i][j];
			visited[i][j] = false;
		}
	}	
}
