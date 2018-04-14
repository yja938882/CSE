#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void combination(int * arr, int n, int r, int size, bool* flag){
	vector< int > result;
	if( n == r ){
		for( int i=0; i<n; i++ ) flag[i] = true;
		int sum = 0;
		for( int i=0; i<size; i++ ){
			if( flag[i] ){
				sum+=arr[i];
			}
		}
		if( sum == 100 ){
			for( int i=0; i<size; i++ ){
				if( flag[i] )
					result.push_back( arr[i] );
			}
		}
		sort( result.begin(), result.end() );
		for( int j=0; j< result.size(); j++ ){
			cout << result[j] << endl;
		}
		for( int i=0; i<n; i++ ) flag[i] = false;
		result.resize(0);
		return;
	}
	if( r == 1 ){
		for( int i=0; i<n; i++ ){
			flag[i] = true;
			int sum =0;
			for( int j=0;j<size; j++ ){
				if( flag[j] ){
					sum+=arr[j];
				}
			}
			if( sum == 100){
				for( int j=0; j<size; j++ ){
					if( flag[j] )
						result.push_back( arr[j] );
				}
			}
			sort( result.begin(), result.end() );
			for( int j=0; j< result.size(); j++ ){
				cout << result[j] << endl;
			}
			flag[i] = false;
			result.resize(0);
		}
		return;
	}
	flag[n-1] = true;
	combination( arr, n-1, r-1, size, flag );
	flag[n-1] = false;
	combination( arr, n-1, r ,size, flag );
}

int main(void){
	int* arr = new int[9];
	bool* visited = new bool[9];
	for( int i=0; i<9; i++ ){
		visited[i] = false;
		cin >> arr[i];
	}
	combination( arr, 9, 7, 9, visited );
	return 0;
}
