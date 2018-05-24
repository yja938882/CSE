#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long longabs( long long a ){
    return a<0 ? -a : a;
}

void sol( long long* arr, int N ){
	int left = 0;
	int right = N-1;
	int middle;

	int min_left = 0;
	int min_right = N-1;
	int min_middle = min_left+1;
	long long sum = arr[ min_left ] + arr[ min_right ] + arr[min_middle] ;
	while( left < right - 1 ){
		for( middle = left+1; middle < right; middle++ ){
			if( longabs( sum ) > longabs(arr[ left ] + arr[ right ] + arr[ middle ]) ){
				sum = arr[ left ] + arr[ right ] + arr[ middle ] ;
				min_left = left;
				min_right = right;
				min_middle = middle;	
			}
		}
		if( sum < 0 ){
			left++;
		}else if( sum > 0 ){
			right--;
		}else{
			break;
		}
	}
	cout << arr[min_left] <<" " << arr[min_middle] << " " << arr[min_right];
	return ;
}

int main( void ){
	int N;
	cin >> N;
	long long arr[N];
	for( int i=0; i<N; i++ ){
		cin >> arr[i];
	}
	sort( arr, arr+N );
	sol( arr, N );
	return 0;
}
