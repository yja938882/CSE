#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

const int VIRUS = 2;
const int WALL = 1;

int max_safe_area = -1;

/**
	@brief Simple virus position stack
*/
pair<int, int> VSStack[64];
int top = -1;

bool isVSEmpty(){
	return top == -1;
}
pair<int, int> VStop(){
	return VSStack[top];
}
void VSpush(int i, int j){
	VSStack[++top] = make_pair( i, j);
}
void VSpop(){
	top --;
}

/**
	@return (n,m)위치로 바이러스가 퍼질수 있는지 여부 반환
*/
bool can_spread( int ** arr, int n, int m, int N, int M){
	if( n<0 || m<0 || n>=N || m>=M )
		return false;
	return arr[n][m] == 0;
}

/**
	@brief 바이러스가 퍼지는 프로세스
*/
void spred_process(int ** arr,int  N, int M){
	if( isVSEmpty() )
		return;
	pair<int, int> pos = VStop();
	VSpop();
	arr[pos.first][pos.second] = VIRUS;
	if( can_spread( arr, pos.first -1, pos.second ,N,M)){
		VSpush( pos.first -1, pos.second );
	}
	if( can_spread( arr, pos.first +1, pos.second ,N,M)){
		VSpush( pos.first +1, pos.second );
	}
	if( can_spread(arr, pos.first, pos.second+1 ,N,M)){
		VSpush( pos.first, pos.second+1 );
	}
	if( can_spread(arr, pos.first , pos.second-1,N,M )){
		VSpush( pos.first, pos.second-1 );
	}
	spred_process(arr, N, M);
}

/**
	@return 바이러스가 퍼졌을때 안전지대 갯수 반환
*/
int spread( int **arr, int N, int M ){
	int ret = 0;
	int **temp = new int *[N];

	// Copy arr -> temp
	for( int i=0; i<N; i++){
		temp[i] = new int [M];
	}
	for( int i=0;i< N;i++){
		for(int j=0; j<M;j++){
			temp[i][j] = arr[i][j];
			
			if(arr[i][j] == VIRUS)
				VSpush(i,j);
		}
	}

	spred_process(arr,N,M);

	// 안전지대 카운트
	for( int i=0; i<N; i++ ){
		for( int j=0; j<M; j++){
			if(arr[i][j] == 0)
				ret++;
		}
	}

	// Recover arr <- temp
	for( int i=0;i< N;i++){
		for(int j=0; j<M;j++){
			arr[i][j] = temp[i][j];
		}
	}

	return ret;
}

void combination( int ** arr, vector< pair<int, int > > safe_area , bool* flag, int n, int r, int N, int M){
	if( n == r ){
		for( int i=0; i<n; i++) flag[i] = true;

		for( int i=0; i<safe_area.size(); i++){
			if( flag[i] ){
				arr[ safe_area[i].first ][ safe_area[i].second ] = WALL;
			}
		}
		int ret = spread(arr, N, M);
		if( ret > max_safe_area){
			max_safe_area = ret;
	
		}

		for( int i=0; i<safe_area.size(); i++){
			if( flag[i] ){
				arr[ safe_area[i].first ][ safe_area[i].second ] = 0;
			}
		}

		for( int i=0; i<n; i++) flag[i] = false;

		return;
	}
	if( r == 1 ){
		for( int i=0; i<n; i++){
			flag[i] = true;
		
			for( int j=0; j<safe_area.size(); j++){
				if( flag[j] ){
					arr[ safe_area[j].first ][ safe_area[j].second ] = WALL;
				}
			}
			int ret = spread(arr, N, M);
			if( ret > max_safe_area){
				max_safe_area = ret;
	
			}

			for( int j=0; j<safe_area.size(); j++){
				if( flag[j] ){
					arr[ safe_area[j].first ][ safe_area[j].second ] = 0;
				}
			}

			flag[i] = false;
		}
		return;
	}
	flag[n-1] = true;
	combination( arr, safe_area , flag , n-1, r-1, N, M );
	flag[n-1] = false;
	combination( arr, safe_area , flag, n-1, r, N, M);
}

int main(void){
	int N,M;
	int ** arr;
	cin>>N>>M;
	vector< pair<int, int> > safe_area;
	arr = new int* [N];
	for( int i=0; i< N; i++ ){
		arr[i] = new int [M];
	}

	for( int i=0; i<N; i++ ){
		for( int j=0; j<M; j++){
			cin>>arr[i][j];
			if( arr[i][j] == 0)
				safe_area.push_back( make_pair(i, j) );
		}
	}

	bool * flag = new bool[ safe_area.size() ];
	for( int i=0; i<safe_area.size(); i++)
		flag[i] = false;
	combination( arr, safe_area, flag, safe_area.size(), 3, N, M);
	cout<< (max_safe_area);

	return 0;
}