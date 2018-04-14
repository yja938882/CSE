/*
* Iterarive Deepening Search
* @author : Yeon JuAn 
*/
#include <iostream>
#include <fstream>
using namespace std;

const int VISITED = 5;
const int WALL = 1;
const int DEST = 4;
const int ROAD = 2;
const int START = 3;

bool isReachable( int**, int, int, int, int );
bool isDest( int**, int, int );
int IDS( int** arr, int, int, int, int);
bool LDS( int**, int, int, int, int, int );
void printArr( int **, int, int );
int** readInput(const char *, int*, int *, int *, int *);
void writeResult(const char *, int **, int, int, int );

int global_count = 0; // time counter

int main(int argc, char* argv[]){
    int N,M;    // row, col size
    int sn, sm; // start row, colum
    int ** arr ;    // Maze array

    if( argc != 3){ // Wrong arguments
        cout<<" error wrong argument!"<<endl;
        exit(-1);
    }    
    
    arr = readInput(argv[1],&N, &M, &sn, &sm);  // Read data
    
    int limit = IDS(arr, sn, sm, N, M); // Iterarice Deepening Search

    printArr( arr, N, M);
    
    writeResult(argv[2], arr, N, M, limit); // Write result
    return 0;
}

/**
    @brief input file read
    @param pFileName 읽을 파일 이름
    @param _N 읽은 행 크기 
    @param _N 읽은 열 크기
    @param _n 읽은 시작 행 번호
    @param _m 읽은 시작 열 번호
    @param pDest 읽은 도작지
*/
int** readInput(const char *pFileName , int* _N, int *_M, int* _n, int *_m ){
    ifstream inputFile;
    inputFile.open(pFileName);
    if(!inputFile.is_open()){   // Open error
        cout<<" error open file : "<<pFileName<<endl;
        exit(-1);
    }
   
    int N,M;
    int ** arr = NULL;
    inputFile>>N>>M;

    *(_N) = N;
    *(_M) = M;

    arr = new int*[N];
    for( int i=0; i<N; i++ ){
        arr[i] = new int[M];
    }

    // Read maze
   for( int n=0; n<N; n++){
        for( int m=0; m<M; m++){
            inputFile >> arr[n][m];
            if(arr[n][m] == START){ // Get start position
                *(_n) = n;
                *(_m) = m;
            }
   
        }
    }
    return arr;
}

/**
    @param arr 미로 배열
    @param n 검사할 행 번호
    @param m 검사할 열 변호
    @return 도달 가능한지 여부 반환
*/
bool isReachable(int** arr, int n , int m , int N, int M){
    if( n < 0 || m <0 || n>=N || m>=M ) // Out of array
        return false;
    return arr[n][m] == START || arr[n][m] == ROAD || arr[n][m] == DEST;
}

/**
    @param arr 미로 배열
    @param n 검사할 행 번호
    @param m 검사할 열 변호
    @return 목적지 인지 여부 반환
*/
bool isDest( int** arr, int n, int m){
    return arr[n][m] == DEST;
}

/**
    @brief Iterarice Deepening Search
    @param arr 미로 배열
    @param n 시작 행 위치
    @param m 시작 열 위치
*/
int IDS( int** arr, int n, int m, int N, int M ){
    int limit = 1;
    while(1){
        if( LDS(arr, n, m, N, M, limit ) )    // Limited Deepening Search
            break;
        limit++;    // Increase Limit
    }
    return limit;
}

/**
    @brief Limited Deepening Search
*/
bool LDS(int** arr, int n, int m, int N, int M, int limit){

    if( !isReachable(arr, n, m, N, M))
        return false;
    
    if( limit<= 0)  // limit depth
        return false;
    
	global_count++;    // Count time

    if( isDest( arr, n, m)) // Find goal
        return true;

    int before = arr[n][m]; // Save current maze node state
    if(arr[n][m]!= START)   // Set visited
        arr[n][m] = VISITED;

    // Search Child nodes
    if( LDS( arr, n, m+1, N, M , limit -1)){    // Right
        return true;
    }
    if( LDS( arr, n, m-1, N, M , limit -1)){    // Left
        return true;
    }
    if( LDS( arr, n-1, m ,N, M, limit-1 )){     // Up
        return true;
    }
    if( LDS( arr, n+1, m, N, M , limit -1)){    // Down
        return true;
    }
    arr[n][m] = before; // Recover maze node state
    return false;
}

/**
    @brief For DEBUG
*/
void printArr( int ** arr, int N, int M){
    for( int n=0; n<N; n++){
        for( int m=0; m<M; m++){
            cout<<arr[n][m]<< " ";
        }
        cout<<"\n";
    }
}

/**
    @brief write result to file
    @param pFileName 결과를 저장할 파일 
    @param arr 미로 배열
    @param N 미로 배열 행 크기
    @param M 미로 배열 열 크기
    @param limit 최대 depth 한계
*/
void writeResult(const char *pFileName ,int **arr, int N, int M, int limit){
	ofstream outFile;
	outFile.open(pFileName);
	if(!outFile.is_open()){    // Open error
		cout<<"error";
		return;
	}	
	for(int n=0; n<N; n++ ){
		for( int m=0; m<M; m++ ){
			outFile<<arr[n][m];
		}
		outFile<<"\n";
	}
	outFile<<"---\n";
	outFile<<"length="<<limit -2 <<endl;
	outFile<<"time="<<global_count;
	outFile.close();
}


