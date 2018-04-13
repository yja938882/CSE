#include <iostream>
#include <vector>
#include <string>
using namespace std;
/**
	@brief (i, j)를 포함하는 테트리노가 포함한 숫자중 가장 큰 수 반환
*/
int putBlock(int **arr, int i, int j, int count, int sum, int N, int M, bool** visited){
	int total_sum = arr[i][j] + sum;
	vector< pair<int, int> > adjacent;
	if( count <= 0) return total_sum; // if Block size == 4 , then return result; 

	if ( i-1 >= 0 && !visited[i-1][j] )		// Up
		adjacent.push_back( make_pair( i-1, j ) );
	if ( i+1 < N && !visited[i+1][j] )		// Down
		adjacent.push_back( make_pair( i+1, j ) );
	if ( j-1 >=0 && !visited[ i ][j-1] )	// Left 
		adjacent.push_back( make_pair( i, j-1 ) );
	if ( j+1 < M && !visited[ i ][j+1] )	// Right
		adjacent.push_back( make_pair( i, j+1 ) );

	int max = 0;

	if( count == 3){	//Special case .. 'ㅗ' tetromino
		int min_index = 0;
		int around_sum =0;
		for( int i=0; i<adjacent.size(); i++){
			around_sum += arr[ adjacent[i].first ][ adjacent[i].second ];
			if( arr[ adjacent[min_index].first ][ adjacent[min_index].second ] > arr[ adjacent[i].first ][ adjacent[i].second ] ){
				min_index = i;
			}
		}
		max = around_sum + total_sum;
		if( adjacent.size() >=4){
			max -= arr[ adjacent[min_index].first ][ adjacent[min_index].second ];
		}
	}

	int max_index = -1;

	for ( int k =0; k< adjacent.size(); k++ ){
		visited[ adjacent[k].first ][adjacent[k].second] = true;
		int ret = putBlock( arr, adjacent[k].first, adjacent[k].second, count -1, total_sum, N, M, visited);
		visited[ adjacent[k].first ][adjacent[k].second] = false;
		if( ret > max ){
			max = ret;
		}
	}
	return max;
}

int put_tetromino( int** arr , int N, int M){
	int max=0;
	bool** visited = new bool* [N];
	for( int i=0; i<N; i++)
		visited[i] = new bool[M];
	for( int i=0; i<N; i++){
		for( int j=0; j<M; j++)
			visited[i][j] = false;
	}

	for (int i=0; i<N; i++ ){
		for( int j=0; j<M; j++ ){
			visited[i][j] = true;
			int ret = putBlock( arr, i, j, 3, 0, N, M, visited);
			visited[i][j] = false;
			if( ret >= max)
				max = ret;
		}
	}
	return max;
}

int main(void){
	int N,M;
	int** arr;
	cin>>N>>M;

	arr = new int*[ N ];
	for( int i=0; i<N; i++ ){
		arr[i] = new int [M];
	}

	for( int i=0; i<N; i++ ){
		for( int j=0; j<M; j++){
			cin>>arr[i][j];
		}
	}
	cout<<put_tetromino( arr, N, M);
}