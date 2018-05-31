#include <cstdio>
using namespace std;
int **adj;
bool *visited;

void dfs( int s , int N){
	printf("%d ",s+1 );
	visited[s] = true;
	for( int i=0; i<N; i++ ){
		if( adj[s][i] == 1 && !visited[i] ){
			dfs( i , N );
		}
	}
}

int queue[ 1001 ];
int _end = 0;
int _front = 0;
void push( int a ){
	queue[ _end ++] = a;
}
int front(){
	return queue[ _front ];
}
void pop(){
	_front++;
}
bool q_empty(){
	return _front>=_end;
}

void bfs( int s, int N ){
	push( s );
	visited[s] = true;
	while( !q_empty() ){
		int c = front();	
		pop();	
		printf("%d ",c+1);	

		for( int i=0; i<N; i++ ){
			if( adj[c][i] == 1 && !visited[i] ){
				push( i );
				visited[i] = true;
			}
		}
	}
	
}

int main( void ){
	int N, M, V;
	scanf("%d %d %d",&N,&M,&V);
	
	adj = new int*[N];
	visited = new bool [N];
	for( int i=0; i<N; i++ ){
		adj[i] = new int[N];
		for( int j=0; j<N; j++ ){
			adj[i][j] = 0;
		}
		visited[i] = false;
	}

	for( int i=0; i<M; i++ ){
		int a, b;
		scanf("%d %d",&a,&b);
		adj[a-1][b-1] = 1;
		adj[b-1][a-1] = 1;
	}
	dfs( V-1, N );

	for( int i=0; i<N; i++ ) visited[i] = false;

	printf("\n");
	bfs( V-1, N );	

	return 0;
}
