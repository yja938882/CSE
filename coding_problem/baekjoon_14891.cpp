#include <iostream>
using namespace std;
const int SAW_TOOTH_MAX = 8;
const int SAW_MAX = 4;
const int ROTATE_RIGHT = 1;
const int ROTATE_LEFT = -1;
/**
	백준 14891 번 문제 풀이
*/

/**
	@param arr 회전시킬 톱니바퀴
	@param way 회전시킬 방향 ( ROTATE_RIGHT or ROTATE_LEFT )
	@brief way 에 따라 톱니바퀴 회전
*/
void rotate( int *arr, int way){
	if( way == ROTATE_RIGHT ){
		int last = arr[SAW_TOOTH_MAX -1];
		for( int i= SAW_TOOTH_MAX -1; i>0; i--)
			arr[i] = arr[i-1];
		arr[0] = last;
	}else if( way == ROTATE_LEFT ){
		int first = arr[0];
		for( int i=0; i<SAW_TOOTH_MAX-1; i++)
			arr[i] = arr[i+1];
		arr[SAW_TOOTH_MAX-1] = first;
	}
}

/**
	@param arr 톱니바퀴 배열
	@brief for DEBUG. 배열 현재 상태 출력 
*/
void printSaw(int ** arr){
	for( int i=0; i<SAW_MAX;i++){
		for( int j=0;j<SAW_TOOTH_MAX;j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<"\n";
	}
}

/**
	@param arr 톱니바퀴 배열
	@param cur 현재 회전시키려고 하는 톱니바퀴 인덱스
	@return cur 톱니바퀴기준 오른쪽 톱니바퀴의 회전여부 반환
*/
bool isRightRotated( int ** arr, int cur){
	if(cur>=SAW_MAX-1)
		return false;
	return arr[cur][2] != arr[cur+1][6];
}

/**
	@param arr 톱니바퀴 배열
	@param cur 현재 회전시키려고 하는 톱니바퀴 인덱스
	@return cur 톱니바퀴기준 왼쪽 톱니바퀴의 회전여부 반환
*/
bool isLeftRotated( int ** arr, int cur){
	if( cur<=0 )
		return false;
	return arr[cur][6] != arr[cur-1][2];
}

/**
	@param arr 톱니바퀴 배열
	@param pNum 회전시킬 톱니바퀴 인덱스
	@param pWay 회전시킬 방향
	@param visited 무한 루프 방지를 위한 배열
	@brief 인덱스에 해당하는 톱니바퀴를 지정한 방향으로 회전, 이러인해 영향받는 바퀴들도 회전
*/
void rotate_saw(int** arr, int pNum , int pWay , bool* visited){
	if(visited[pNum])
		return;
	visited[pNum] = true;
	if(isRightRotated( arr, pNum)){
		if(pWay == ROTATE_RIGHT) rotate_saw( arr, pNum+1 , ROTATE_LEFT, visited);
		else if(pWay == ROTATE_LEFT ) rotate_saw(arr, pNum+1, ROTATE_RIGHT, visited);
	}
	if( isLeftRotated(arr, pNum )){
		if(pWay == ROTATE_RIGHT ) rotate_saw( arr, pNum -1, ROTATE_LEFT, visited);
		else if(pWay == ROTATE_LEFT ) rotate_saw( arr, pNum-1, ROTATE_RIGHT, visited);
	}
	rotate(arr[pNum], pWay);
}

/**
	@param arr 톱니바퀴 배열
	@return 점수
	@brief 문제에서 요구하는 점수 반환
*/
int getScore( int **arr){
	int score = 0;
	if( arr[0][0] == 1) score +=1;
	if( arr[1][0] == 1) score +=2;
	if( arr[2][0] == 1) score +=4;
	if( arr[3][0] == 1) score +=8;
	return score;
}

int main(void){
	int K;
	int ** saw = new int* [SAW_MAX];
	char line[SAW_TOOTH_MAX+1];

	for( int i=0; i<SAW_MAX; i++)
		saw[i] = new int[ SAW_TOOTH_MAX ];

	for( int i=0; i<SAW_MAX; i++){
		cin>>line;
		for( int j=0; j<SAW_TOOTH_MAX ; j++){
			saw[i][j] = (int)(line[j] - '0');
		}
	}

	cin>>K;
	for( int i=0; i<K; i++){
		int num, way;
		cin>>num>>way;
		bool rotated[SAW_MAX];
		for(int j=0;j<SAW_MAX;j++)
			rotated[j] = false;
		rotate_saw( saw, num -1 , way, rotated);
	}

	cout<<getScore(saw);
}