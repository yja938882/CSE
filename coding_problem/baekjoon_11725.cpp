#include <iostream>
#include <vector>
using namespace std;
int parent[100000];
bool visited[100000];
vector< vector<int> > adj;
void dfs(int r, int p){
	parent[r] = p;
	visited[r] = true;
	for( int i=0; i< adj[r].size(); i++ ){
		if( !visited[ adj[r][i] ])
			dfs(  adj[r][i] , r );
	}
}

int main ( void ){
	int N;
	cin >> N;
	adj.resize( N );
	
	for( int i=0; i<N-1; i++){
		int a, b;
		cin >> a >> b;
		adj[a-1].push_back( b-1 );
		adj[b-1].push_back( a-1 );
	}
	dfs( 0, -1 );

	for( int i=1; i< N; i++ ){
		cout << parent[i]+1 <<"\n";
	}
	return 0;
}

