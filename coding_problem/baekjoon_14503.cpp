#include <iostream>
#include <string>
using namespace std;
const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;

const int DIRTY = 0;
const int WALL = 1;
const int CLEAN = 2;

/**
	@brief get left position
	@param r row index
	@param c colum index
	@param d current direction
	@return left position
*/
pair<int, int> getLeft( int r, int c, int d){
	switch(d){
		case NORTH :	return make_pair( r, c-1 );
		case EAST :		return make_pair( r-1, c );
		case SOUTH : 	return make_pair( r, c+1 );
		case WEST :		return make_pair( r+1, c );
	}
	return make_pair(0,0);
}

/**
	@brief get back position
	@param r row index
	@param c colum index
	@param d current direction
	@return back position
*/
pair<int, int> getBack( int r, int c, int d){
	switch(d){
		case NORTH :	return make_pair( r+1, c );
		case EAST :		return make_pair( r, c-1 );
		case SOUTH : 	return make_pair( r-1, c );
		case WEST :		return make_pair( r, c+1 );
	}
	return make_pair( 0, 0 );
}

/**
	@brief rotate
	@param d current direction
	@return rotated direction
*/
int rotate( int d ){
	int retd = d;
	retd --;
	if( retd<0 )
		retd = WEST;
	return retd;
}

/*
    1.현재 위치를 청소한다.
    2.현재 위치에서 현재 방향을 기준으로 왼쪽방향부터 차례대로 탐색을 진행한다.
        (1)왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면, 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행한다.
        (2)왼쪽 방향에 청소할 공간이 없다면, 그 방향으로 회전하고 2번으로 돌아간다.
        (3)네 방향 모두 청소가 이미 되어있거나 벽인 경우에는, 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아간다.
        (4)네 방향 모두 청소가 이미 되어있거나 벽이면서, 뒤쪽 방향이 벽이라 후진도 할 수 없는 경우에는 작동을 멈춘다.
*/
int robot_clean( int** arr, int pR, int pC, int pD , int pClean){

	int r = pR, c = pC, d = pD;
	int clean = pClean;
	if( arr[r][c] == DIRTY ){
		arr[r][c] = CLEAN; // 청소
		clean++;
	}

	//네 방향 모두 청소 or 벽 
	if ( ( arr[r-1][c] == CLEAN || arr[r-1][c] == WALL )	// NORTH 
	&&	 ( arr[r][c+1] == CLEAN || arr[r][c+1] == WALL )	// EAST
	&& 	 ( arr[r+1][c] == CLEAN || arr[r+1][c] == WALL ) 	// SOUTH
	&& 	 ( arr[r][c-1] == CLEAN || arr[r][c-1] == WALL ) ){	// WEST
		pair<int , int> backPos = getBack( r, c, d );
		if( arr[ backPos.first ][ backPos.second ] == WALL){	// (4) 조건
			return clean;
		}else{		// (3) 조건
			r = backPos.first;
			c = backPos.second;
			return robot_clean( arr, r, c, d, clean) ;
		}
	}

	pair<int, int> leftPos = getLeft( r, c, d );
	if( arr[ leftPos.first ][ leftPos.second ] == DIRTY ){ // (1) 조건
		r = leftPos.first;
		c = leftPos.second;
		d = rotate(d);
		return robot_clean( arr, r, c, d ,clean );
	}else{ // (2) 조건
		d = rotate(d);
		return robot_clean( arr, r, c, d, clean );
	}
}

int main(void){
	int N, M;
	int r, c, d;
	int **arr;
	cin>>N>>M;
	cin>>r>>c>>d;

	arr = new int*[ N ];
	for( int i=0; i<N; i++ ){
		arr[i] = new int[ M ];
	}
	for( int i=0; i<N; i++){
		for( int j=0; j<M; j++){
			cin>>arr[i][j];
		}
	}
	cout<<robot_clean( arr, r, c, d ,0);

}
