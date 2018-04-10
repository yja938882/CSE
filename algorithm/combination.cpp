#include <iostream>
using namespace std;

/**
	@brief print nCr 
*/
void combination(char * arr, bool* flag, int size, int n, int r){
	if( n == r){
		cout<<"{";
		for( int i=0; i<n; i++) flag[i] = true;
		
		for( int i=0; i<size; i++)
			if( flag[i]) cout<<arr[i]<<" ";
		
		for( int i=0; i<n; i++) flag[i] = false;

		cout<<"}\n";
		return;
	}
	if( r == 1){
		for( int i=0; i<n; i++){
			cout<<"{";
			flag[i] = true;
			for( int j=0; j<size; j++){
				if( flag[j] ) cout<<arr[j]<<" ";
			}
			flag[i] = false;
			cout<<"}\n";
		}
		return;
	}
	flag[n-1] = true;
	combination( arr, flag, size, n-1, r-1 );
	flag[n-1] = false;
	combination( arr, flag, size, n-1, r );	
}

int main(){
	int N;
	int n, r;
	char* arr;
	bool* flag;

	cin >> N;
	arr = new char[N];
	flag = new bool[N];

	for( int i=0; i<N; i++){
		flag[i] = false;
		cin >> arr[i];
	}
	cin>>n;
	cin>>r;

	combination(arr, flag, N, n, r );

}