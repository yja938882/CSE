#include <cstdio>
#include <queue>
#include <string>
using namespace std;
char **arr;
bool **visited;
int N, M;
queue< pair<int, int > > q;
queue< int > qv;
bool can_visit( int n , int m ){
    return n>=0 && n < N && m >=0 && m<M && arr[n][m]=='1' && !visited[n][m];
}

int bfs( int n, int m, int dn, int dm ){
    q.push( make_pair( n, m ) );
    qv.push( 1 );
    while( !q.empty()){
        pair<int, int> f = q.front();
        int d = qv.front();
        q.pop();
        qv.pop();
    
        if( f.first == dn && f.second == dm )
            return d;
        n = f.first;
        m = f.second;
        if( can_visit( n-1, m ) ){
            q.push( make_pair( n-1, m ) );
            qv.push( d+1 );
            visited[ n-1 ][ m ] = true;
        }
        if( can_visit( n+1, m ) ){
            q.push( make_pair( n+1, m ) );
            qv.push( d+1 );
            visited[ n+1 ][ m ] = true;
        }
        if( can_visit( n, m+1 ) ){
            q.push( make_pair( n, m+1 ) );
            qv.push( d+1 );
            visited[ n ][ m+1 ] = true;
        }
        if( can_visit( n, m-1) ){
            q.push( make_pair( n, m-1) );
            qv.push( d+1 );
            visited[ n ][ m-1 ] = true;
        }
    }
    return -1;
}

int main( void ){
    scanf("%d %d",&N, &M);
    
    arr = new char*[N];
    visited = new bool*[N];
    for( int i=0; i<N; i++ ){
        arr[i] = new char[M+1];
        visited[i] = new bool[M];
        for( int j=0; j<M; j++ )
            visited[i][j] = false;
    }
    
    
    for( int i=0; i<N; i++ ){
        scanf("%s",arr[i] );
    }
    printf("%d", bfs( 0,0, N-1, M-1 ) );
    return 0;
}

