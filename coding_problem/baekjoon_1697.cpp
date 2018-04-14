#include <iostream>
#include <queue>
#include <string>
using namespace std;

queue< pair<int, int> > _queue;
/**
	@param N start position
	@param M dest position
	@return depth
*/
int DFS(int N, int M){
	_queue.push( make_pair( N, 0) );
	bool visited[200001];

	for( int i=0; i<200001; i++){
		visited[i] = false;
	}
	while(1){
		pair<int, int> n = _queue.front();
		_queue.pop();
		
		if(n.first == M)
			return n.second;
		if(visited[n.first]) // if already visited position
			continue;
		visited[n.first] = true;	// check visited
		if(n.first > 0 && !visited[n.first-1] ){
			_queue.push( make_pair((n.first)-1, n.second+1) );
		}
		if( n.first <= 100000 && !visited[n.first*2] ){
			_queue.push( make_pair(n.first*2, n.second+1) );
		}
		if( n.first <= 200000 && !visited[n.first+1] ){
			_queue.push( make_pair(n.first+1, n.second+1) );
		}
	}
	return 0;
}

int main(void){
	int N,M;
	cin>>N>>M;
	
	cout<<DFS(N,M);
}