#include <cstdio>
using namespace std;

int queue[10000];
int _front = 0;
int _end = 0;

bool q_empty(){
    return _front >= _end ;
}
void push( int a ){
    queue[_end++] = a;
}
int front(){
    return queue[_front];
}
void pop(){
    _front ++;
}
bool is_least( int a ){
    for( int i = _front; i< _end; i++ ){
        if( queue[i] > a )
            return false;
    }
    return true;
}

int main( void ){
    int T;
    scanf( "%d",&T );
    for( int t=0; t<T; t++ ){
        int N, M;
        scanf("%d",&N);
        scanf("%d",&M);
        
        _front = 0;
        _end = 0;
        for( int i=0; i< N; i++ ){
            int d;
            scanf("%d",&d);
            push( d );
        }
        int cnt = 0;
        while( 1 ){
            int f = front();
            if( is_least( f ) &&  _front == M ){
                cnt++;
                break;
            }
            if( is_least( f ) ){
                pop();
                cnt++;
            }else{
                if( _front == M){
                    M = _end;
                }
                pop();
                push(f);
            }
        
        }
        printf( "%d\n", cnt );
    }
}




