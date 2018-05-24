#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int left_child[ 300001 ];
int right_child[ 300001 ];
int left_most[ 300001 ];
int right_most[ 300001 ];
int levels[ 300001 ];
void createNode( int key ){
	left_child[key] = -1;
	right_child[key] = -1;
	left_most[key] = key;
	right_most[key] = key;
}

void insert( int key, int root ){
	if( left_most[ root ] > key ){
		if( left_most[ root ] == root ){
			left_child[ root ] = key;
			createNode( key );		
			levels[ key ] = levels[ root ] +1;	
		}else{
			insert( key , left_most[ root ] );
		}
		left_most[ root ] = key;
	}else if( right_most[root] < key ){
		if( right_most[ root ] == root ){
			right_child[ root ] = key;
			createNode( key );
			levels[ key ] = levels[ root ] +1;
		}else{
			insert( key, right_most[ root ] );
		}
		right_most[ root ] = key;
	}else{
		if( root > key ){
			insert( key , left_child[root] );	
		}else{
			insert( key, right_child[root] );
		}	
	}

}
int main( void ){
	int root;
	int N;
	vector< int > seq;
	scanf("%d",&N);
	scanf("%d",&root);
	seq.push_back( root );
	createNode( root );
	levels[ root ] = 0;
	for( int i=1; i<N; i++ ){
		int in;
		scanf("%d",&in );
		insert( in , root);
		seq.push_back( in );
	}
	int sum = 0;
	for( int i=0; i< seq.size(); i++ ){
		sum += levels[seq[i]];
		printf("%d\n",sum);
	}
	return 0;
}
