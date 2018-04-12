#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm> 
#include <queue>
using namespace std;

const int VISITED = 7;  // 임시로 방문
const int SOL_VISITED = 5;  // Path Node
const int WALL = 1; 
const int DEST = 4;
const int ROAD = 2;
const int START = 3;

struct node{
    int n;  // 행 번호
    int m;  // 열 번호
    int heuristic; // Heuristic Function 결과 값
    node* prev; // 부모 노드
};

struct CompareNode{
    bool operator()(node* a, node* b){
        return a->heuristic > b->heuristic;
    }
};

int** readInput( const char *, int *, int *, int *, int *, vector< pair<int, int> >& );
void writeResult( const char *, int **, int, int, int);
node* createNode( int, int, vector<pair<int, int> >, node* );
int ManhattaDist( int, int, int, int);
bool isReachable( int**, int, int, int, int );
bool isDest( int**, int, int );
void printArr( int **, int, int);
int GBFS( int**, int, int, vector< pair<int, int> > ) ;
int Heuristic( int, int, vector< pair< int, int> > );
int mark_sol( int** arr, node* node);

priority_queue< struct node* , vector< struct node* >, CompareNode> pqueue; // Min Heap
vector< struct node* > all_visited_node; // 모든 방문한 node
int global_count = 0; 

int main(int argc, char* argv[]){
    int N,M;
    int sn, sm;
    int ** arr ;
    int limit = 1;
    vector< pair<int, int> > dest;

    if( argc!= 3){
        cout<<" errir wrong argument!"<<endl;
        exit(-1);
    }

    arr = readInput(argv[1],&N, &M, &sn, &sm, dest);
    
    pqueue.push( createNode( sn, sm,dest,  NULL));
    int length = GBFS( arr, N, M, dest);
    
    writeResult( argv[2], arr, N, M, length);
  
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
int** readInput(const char *pFileName , int* _N, int *_M, int* _n, int *_m, vector< pair<int, int> >& pDest ){
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
            }else if (arr[n][m] == DEST){
                pDest.push_back(make_pair( n, m));
            }
        }
    }
    return arr;
}

/**
    @brief write result to file
    @param pFileName 결과를 저장할 파일 
    @param arr 미로 배열
    @param N 미로 배열 행 크기
    @param M 미로 배열 열 크기
    @param length Path 길이
*/
void writeResult(const char *pFileName, int **arr, int N, int M, int length){
    ofstream outFile;
    outFile.open( pFileName );
    if( !outFile.is_open() ){
        cout<< " error - open file :"<<pFileName<<endl;
        exit(-1);
    }

    for( int n=0; n<N; n++){
        for( int m=0; m<M; m++ ){
            outFile<<arr[n][m];
        }
        outFile<<"\n";
    }

    outFile<<"---\n";
    outFile<<"length="<<length<<endl;
    outFile<<"time="<<global_count<<endl;

    outFile.close();
}

/**
    @breif 노드 생성
    @param pN 행 번호
    @param pM 열 번호
    @param dest 목적지들
    @param pPrev 인접한 이전노드( 부모 노드)
*/
node* createNode( int pN, int pM, vector< pair<int, int> > dest, node* pPrev){
    node* n = new node();
    n->n = pN;
    n->m = pM;
    n->prev = pPrev;
    n->heuristic = Heuristic( pN, pM, dest );
    return n;
}

/**
    @brief (n1, m1) - (n2, m2) 의 맨하탄 거리 반환
*/
int ManhattaDist(int n1, int m1, int n2, int m2){
    int diffN = n1 - n2;
    int diffM = m1 - m2;
    if( diffN < 0) diffN *=(-1);
    if( diffM < 0) diffM *=(-1);
    return diffN + diffM;
}

/**
    @brief Heuristic funtion 
    @param n 노드 행 번호
    @param m 노드 열 번호
    @param dest 목적지들
*/
int Heuristic( int n, int m, vector< pair<int, int> > dest){
    int min = INT_MAX;
    for( int i=0; i<dest.size(); i++){
        int mand = ManhattaDist( n, m, dest[i].first, dest[i].second);
        if( min > mand )
            min = mand;
    }
    return min;
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
    @brief Greedy Best First Search
    @param arr 미로 배열
    @param N 미로 전체 행 크기
    @param M 미로 전체 열 크기
    @param dest 도착지
    @return length of path
*/
int GBFS( int **arr ,int N, int M, vector< pair<int, int> > dest){
    //Greedy Best First.
    node* cur = pqueue.top();
    pqueue.pop();
    global_count++;

    if( isDest( arr, cur->n, cur->m ) ){
        return mark_sol(arr, cur);
    }

    if(arr[ cur->n][ cur->m] != START){
        arr[ cur->n ][ cur->m ] = VISITED; 
        all_visited_node.push_back( cur );
    }
    int sn = cur->n;
    int sm = cur->m;
  
    if( isReachable( arr, sn -1, sm, N, M ) ){ // Left
        pqueue.push( createNode(sn-1, sm, dest , cur ) );
    }
    if( isReachable( arr, sn+1, sm, N, M ) ){ // Right
        pqueue.push( createNode(sn+1, sm, dest , cur ) );
    }
    if( isReachable( arr, sn, sm-1, N, M ) ){ // Up
        pqueue.push( createNode(sn, sm-1, dest , cur ) );
    }
    if( isReachable( arr, sn, sm+1, N, M) ){ // Down
        pqueue.push( createNode(sn, sm+1, dest , cur ) );
    }
 
    return GBFS( arr, N, M, dest);
}

/**
    @brief For DEBUG , 미로 출력
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
    @brief 도착한 Path 만을 표시( SOL_VISITED ), Path 가 아니였던 곳은 ROAD 로 다시 초기화 
    @param arr 미로 배열
    @param node 도착지점 node
    @return Path 길이 반환
*/
int mark_sol( int** arr, node* node){
    struct node* nds = node;
    int length = 0;
    while( (nds)!=NULL ){
        arr[nds->n][nds->m] = SOL_VISITED;
        length ++;
        nds = nds->prev;
    }
    for( int i=0;i< all_visited_node.size(); i++){
        if(arr[all_visited_node[i]->n][all_visited_node[i]->m] == VISITED)
            arr[all_visited_node[i]->n][all_visited_node[i]->m] = ROAD;
    }
    return length;
}



