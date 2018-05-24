#include <cstdio>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#define INF_D 400000

priority_queue< pair<int, int>, vector< pair<int, int > > , greater< pair<int, int > > > pq;
vector< vector< pair< int, int > > > adj;
int * darr;
void sol ( int s ){
		
	pq.push( make_pair( 0, s ) );

	while( !pq.empty() ){
		pair<int, int> f = pq.top();
		pq.pop();
		for( int i=0; i< adj[ f.second ].size(); i++ ){
			if( darr[ adj[ f.second ][i].first ] > f.first + adj[ f.second ][i].second ){
				darr[ adj[ f.second ][i].first ] = f.first + adj[ f.second ][i].second;
				pq.push( make_pair( darr[ adj[ f.second ][i].first  ], adj[ f.second ][i].first ) );
			}
		}
	}
}

int main( void ){
	int N,M;
	scanf("%d",&N);
	scanf("%d",&M);
	
	int S;
	scanf("%d",&S);
	adj.resize( N );
	darr = new int[N];
	for( int i=0; i<N; i++ ){
		darr[i] = INF_D;
	}
	darr[S-1] = 0;
	for( int i=0; i< M; i++ ){
		int a, b, d;
		scanf("%d %d %d",&a, &b, &d);
		adj[ a-1 ].push_back( make_pair( b-1, d ) );
	}
	sol( S-1 );
	for( int i=0; i<N; i++ ){
		if( darr[i] == INF_D ) 
			printf("INF\n");
		else
			printf("%d\n", darr[i]);
	}			
	
	return 0;
}
