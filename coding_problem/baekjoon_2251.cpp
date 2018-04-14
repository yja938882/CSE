#include <iostream>
#include <queue>
#include <algorithm> 
using namespace std;
const int BOTTLE_A = 0;
const int BOTTLE_B = 1;
const int BOTTLE_C = 2;

struct node{
	int bottle[3];
};

queue< struct node* > _queue; 
bool visited[201][201][201];
int MAX[3];
vector< int> result;
struct node* createNode( int A, int B, int C){
	struct node* n = new node;
	n -> bottle[BOTTLE_A] = A;
	n -> bottle[BOTTLE_B] = B;
	n -> bottle[BOTTLE_C] = C;
	return n;
}

struct node* shift_bottle( struct node* n, const int from , const int to ){
	int bottle[3];
	for( int i=0;i<3; i++){
		bottle[i] = n->bottle[i];
	}
	bottle[ to ] += ( bottle[from] );
	int diff = bottle[ to ] - MAX[ to ]; // 넘친 양
	if( diff <= 0 ){// 다 부었음, 안넘쳤음
		bottle[ from ] = 0; 
	}else{ // 넘쳤음
		bottle[ to ] = MAX[to];
		bottle[ from ] = diff;
	}
	return createNode( bottle[BOTTLE_A], bottle[BOTTLE_B], bottle[BOTTLE_C] );
}

void getC_emptyA( int A, int B, int C){
	struct node* start = createNode( A, B, C );

	_queue.push( start );

	while( !_queue.empty() ){
		struct node* cur = _queue.front();
		_queue.pop();
		if( visited[ cur->bottle[BOTTLE_A] ][ cur->bottle[BOTTLE_B] ][ cur->bottle[BOTTLE_C] ] ) continue;

		if( cur->bottle[BOTTLE_A] == 0)
			result.push_back( cur-> bottle[BOTTLE_C] );

		visited[ cur->bottle[BOTTLE_A] ][ cur->bottle[BOTTLE_B] ][ cur->bottle[BOTTLE_C] ] = true;

		_queue.push( shift_bottle( cur, BOTTLE_A, BOTTLE_B ));
		_queue.push( shift_bottle( cur, BOTTLE_A, BOTTLE_C ));
		_queue.push( shift_bottle( cur, BOTTLE_B, BOTTLE_C ));
		_queue.push( shift_bottle( cur, BOTTLE_B, BOTTLE_A ));
		_queue.push( shift_bottle( cur, BOTTLE_C, BOTTLE_A ));
		_queue.push( shift_bottle( cur, BOTTLE_C, BOTTLE_B ));
		
	}


}

int main(void){

	cin >> MAX[0] >> MAX[1] >> MAX[2];
	for( int i=0; i<201; i++)
		for( int j=0; j<201; j++ )
			for( int k=0; k<201; k++)
				visited[i][j][k] = false;
	getC_emptyA( 0, 0, MAX[BOTTLE_C] );
	sort(result.begin(), result.end());
	for( int i=0; i<result.size(); i++){
		cout<<result[i]<<" ";
	}
}