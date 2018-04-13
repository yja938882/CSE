#include <iostream>
using namespace std;
const int EAST = 1;
const int WEST = 2;
const int NORTH = 3;
const int SOUTH = 4;

const int TOP = 0;
const int BOTTOM = 1;
const int EAST_SIDE = 2;
const int WEST_SIDE = 3;
const int NORTH_SIDE = 4;
const int SOUTH_SIDE = 5;

struct dice{
	int n;	// 행
	int m;	// 열
	int elem[6]; // 주사위 각 육면
};

struct dice* createDice(int x, int y){
	struct dice* d = new struct dice;
	for( int i=0; i<6; i++ ){
		d->elem[i] = 0;
	}
	d->n = x;
	d->m = y;
	return d;
}

bool isCorrectPos( int dn, int dm, int N, int M){
	return (dn>=0 && dm>=0 && dn<N && dm<M);
}

void moveDice( struct dice* d, int** arr, int q, int N, int M ){
	int temp;
	switch( q ){
		case EAST:
			temp = d->elem[TOP];
			d->elem[TOP] = d->elem[WEST_SIDE];
			d->elem[WEST_SIDE] = d->elem[BOTTOM];
			d->elem[BOTTOM] = d->elem[EAST_SIDE];
			d->elem[EAST_SIDE] = temp;
			(d->m)++;
			break;
		case WEST:
			temp = d->elem[TOP];
			d->elem[TOP] = d->elem[EAST_SIDE];
			d->elem[EAST_SIDE] = d->elem[BOTTOM];
			d->elem[BOTTOM] = d->elem[WEST_SIDE];
			d->elem[WEST_SIDE] = temp;	
			(d->m)--;
			break;
		case NORTH:
			temp = d->elem[TOP];
			d->elem[TOP] = d->elem[SOUTH_SIDE];
			d->elem[SOUTH_SIDE] = d->elem[BOTTOM];
			d->elem[BOTTOM] = d->elem[NORTH_SIDE];
			d->elem[NORTH_SIDE] = temp;
			(d->n)--;
			break;
		case SOUTH:
			temp = d->elem[TOP];
			d->elem[TOP] = d->elem[NORTH_SIDE];
			d->elem[NORTH_SIDE] = d->elem[BOTTOM];
			d->elem[BOTTOM] = d->elem[SOUTH_SIDE];
			d->elem[SOUTH_SIDE] = temp;
			(d->n)++;
			break; 
	}
	if( arr[ d->n ][ d-> m] == 0){
		arr[d->n][d->m] = d->elem[BOTTOM];
	}else{
		d->elem[BOTTOM] = arr[d->n][d->m];
		arr[d->n][d->m] = 0;
	}

	cout<<d->elem[TOP]<<endl;
}

void Query( int** arr, struct dice* d, int q, int N, int M){

	switch( q ){
		case EAST:	
			if( !isCorrectPos( d->n, (d->m)+1, N, M ) ) 
				return;
			break;
		case WEST:	
			if( !isCorrectPos( d->n, (d->m)-1, N, M ) ) 
				return;
			break;
		case NORTH:	
			if( !isCorrectPos( (d->n)-1, d->m, N, M ) ) 
				return;
			break;
		case SOUTH:	
			if( !isCorrectPos( (d->n)+1, d->m, N, M ) ) 
				return;
			break;
	} 
	moveDice(d, arr, q, N, M);
}

int main(void){
	int N,M,x,y,K;
	cin>>N>>M>>x>>y>>K;
	int ** arr = new int*[N];
	int * query = new int[K];

	struct dice * d = createDice(x, y);
	
	arr = new int* [N];

	for( int i=0; i<N; i++){
		arr[i] = new int [M];
	}

	for( int i=0; i<N; i++){
		for( int j=0; j<M; j++)
			cin>>arr[i][j];
	}

	for( int i=0; i<K; i++){
		cin>>query[i];
	}

	for( int i=0;i<K; i++){
		Query( arr, d, query[i], N, M);
	}
	return 0;
}