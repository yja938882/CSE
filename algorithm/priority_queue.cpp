#include <iostream>
using namespace std;
int size = 0;
int *queue_arr;
void init( int s ){
	queue_arr = new int[s];
}

void insert( int key ){
	int i = size++;
	while( i>0 && key > queue_arr[i/2] ){
		queue_arr[i] = queue_arr[i/2];
		i/=2;
	}
	queue_arr[i] = key;
}

void heapify( int root ){
	int left = ( root+1 )*2 -1;
	int right = ( root+1)*2;
	int largest = root;
	if( left < size && queue_arr[left] > queue_arr[largest] ){
		largest = left;
	}
	if( right < size && queue_arr[right] > queue_arr[largest] ){
		largest = right;
	}
	if( largest != root ){
		swap( queue_arr[root], queue_arr[largest] );
		heapify( largest );
	}
}

bool isempty(){
	return size <= 0;
}

void pop(){
	if( isempty() ) return;
	queue_arr[0] = queue_arr[--size];
	heapify( 0 );
}

int top(){
	return queue_arr[0];
}

int main( void ){
	int N;
	scanf("%d",&N);
	init(N);
	printf("*** P(push) , D( pop ) , T (top ) ***\n");
	while(1){
		char input;
		int num;
		scanf("%c",&input);
		switch( input ){
			case 'P':
				scanf("%d",&num );
				insert( num );
				break;
			case 'D':
				pop();
				break;
			case 'T':
				printf("%d\n",top());
				break;
		}
		for( int i=0; i<size; i++){
			printf("%d ",queue_arr[i]);
		}
		printf("\n");
	}
	
	
}
