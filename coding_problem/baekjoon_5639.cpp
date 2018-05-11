#include <iostream>
#include <stdio.h>
using namespace std;
int left_child[ 1000000 ];
int right_child[ 1000000 ];
void createNode( int key ){
	left_child[ key ] = -1;
	right_child[ key ] = -1;
}
void insert( int key, int root ){
	if( key < root ){
		if( left_child[root] == -1 ){
			createNode( key );
			left_child[root] = key;
		}else{
			insert( key, left_child[root] );
		}
	}else{
		if( right_child[root] == -1 ){
			createNode( key);
			right_child[root] = key;
		}else{
			insert( key, right_child[root]);
		}
	}
}

void post( int root ){
	if( left_child[root] != -1)
		post( left_child[root] );
	if( right_child[root]!= -1)
		post( right_child[root] );
	cout << root << " ";
}
int main ( void ){	

	int root;
	scanf("%d",&root );
	createNode(root);
	
	while(1){
		int in;
		if( scanf("%d",&in)==EOF )
			break;
		insert( in , root ); 
	}
	post( root );
	return 0;	
}
