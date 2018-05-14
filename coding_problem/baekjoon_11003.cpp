#include <iostream>
#include <cstdio>
using namespace std;

int qarr[5000000];
int indexs[5000000];

int front =0;
int qend = 0;

void push( int a , int i){
	indexs[qend] = i;
	qarr[qend++] = a;
}
void pop_front(){
	front++;
}
void pop_back(){
	qend --;
}
int size(){
	return qend-front;
}
int get_front(){
	return qarr[ front ];
}
int get_back(){
	return qarr[ qend-1];
}
int get_front_index(){
	return indexs[ front ];
}

void print_q(){
	cout << "print_q "<< front << " "<<qend << "\n";
	for(int i=front; i<qend; i++ ){
		cout << qarr[i] <<" "; 
	}
	cout <<"\n";
}

int main( void ){
	int N, L;
	cin >> N >> L;

	int arr[N];
	for( int i=0; i<N; i++ ){
		scanf("%d",&arr[i]);
	}
	
	for( int i=0; i< N; i++ ){
		while( size() > 0 && get_back() >= arr[i]) pop_back();
		push( arr[i] , i );
		while( size() >L || get_front_index() <= i-L ) pop_front();
		printf("%d ",get_front() );
	}
	return 0;
}
