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
bool IDS( int**, int, int, int, int, int );
void printArr( int **, int, int );
int** readInput(const char *, int*, int *, int *, int *);
void writeResult(const char *, int **, int, int, int );

int global_count = 0;

int main(int argc, char* argv[]){
    int N,M;
    int sn, sm;
    int ** arr ;
    int limit = 1;
    if( argc != 3){
        cout<<" error wrong argument!"<<endl;
        exit(-1);
    }    

    arr = readInput(argv[1],&N, &M, &sn, &sm);

    while(1){
        if( IDS(arr, sn, sm, N, M, limit ) )
            break;
        limit++;
    }
    
    printArr( arr, N, M);
    writeResult(argv[2], arr, N, M, limit);
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
    if(!inputFile.is_open()){
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
   for( int n=0; n<N; n++){
        for( int m=0; m<M; m++){
            inputFile >> arr[n][m];
            if(arr[n][m] == START){
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
    if( n < 0 || m <0 || n>=N || m>=M )
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
    @brief Interative Deepening Search
*/
bool IDS(int** arr, int n, int m, int N, int M, int limit){

    if( !isReachable(arr, n, m, N, M))
        return false;
    
    if( limit<= 0)
        return false;
    
	global_count++;

    if( isDest( arr, n, m))
        return true;

    int before = arr[n][m];
    if(arr[n][m]!= START)
        arr[n][m] = VISITED;

    if( IDS( arr, n, m+1, N, M , limit -1)){
        return true;
    }

    if( IDS( arr, n, m-1, N, M , limit -1)){
        return true;
    }

    if( IDS( arr, n-1, m ,N, M, limit-1 )){
        return true;
    }

    if( IDS( arr, n+1, m, N, M , limit -1)){
        return true;
    }

    arr[n][m] = before;
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
	if(!outFile.is_open()){
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


