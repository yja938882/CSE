#include <iostream>
#include <vector>
using namespace std;
/**
* 길이 통과 가능한지 여부 반환 
* 조건 
* 1. 인접한 두 바닥의 높이 차이가 2 이상일 경우 경사로를 놓을수 없음.
* 2. 경사로를 놓을 곳은 평평해야함
* 3. 경사로를 놓은곳에 경사로를 놓을 수 없음
*/
bool isPassable(int pL, vector<int> road){
	int before = road[0];
	int current;
	bool setted[road.size()]; // 이미 경사로가 놓여있는지 여부
	for( int i=0; i<road.size(); i++)
		setted[i] = false;
	
	// Check left to right
	for(int i=1; i<road.size(); i++){
		current = road[i];
		if( current - before >=2 || current - before <= -2) // 높이차 2 이상
			return false;
		else if( current - before == 1){
			if( i-pL< 0)
				return false;
			for( int j=i-1; j>= i -pL; j--){ // 경사로가 평평한지 검사
				if( road[j] != before)
					return false;
				else{
					setted[j] = true;
				}
			}

		}
		before = current;
	}

	//Check right to left
	before = road[ road.size() -1 ];
	for( int i=road.size()-2; i>=0; i--){
		current = road[i];
		if( current - before == 1){
			if( i+pL > road.size() -1)
				return false;
			for( int j=i+1; j<=i+pL; j++){ // 경사로가 평평한지 검사
				if(setted[j])
					return false;
				if(road[j] != before)
					return false;
			}
		}
		before = current;
	}

	return true;
}

/**
	@param arr 길 정보 배열
	@param N 갈의 크기
	@param L 경사로 바닥 길기
	@return 통과 가능한 길의 갯수
*/
int getPassNum(int ** arr, int N, int L){
	int sum =0;

	// Check horizontal roads
	for( int i=0; i<N;i++){
		vector<int> horizontal;
		for( int j=0; j<N; j++)
			horizontal.push_back(arr[i][j]);
		if( isPassable( L , horizontal)){
			sum++;
		}
	}

	// Check vertical roads
	for( int j=0; j<N; j++){
		vector<int> vertical;
		for(int i=0; i<N; i++){
			vertical.push_back(arr[i][j]);
		}
		if(isPassable( L , vertical)){
			sum++;
		}
	}
	return sum;
}

int main(void){
	int N ,L;
	int **arr;
	cin>>N>>L;

	arr = new int* [N];
	for( int i=0; i<N; i++){
		arr[i] = new int[N];
	}

	for( int i=0; i<N; i++){
		for( int j=0; j<N; j++){
			cin>>arr[i][j];
		}
	}
	cout<<getPassNum( arr, N, L);
}