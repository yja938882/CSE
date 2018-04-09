#include <iostream>
using namespace std;

/**
	@brief 부분 집합 모두 출력
*/
void power_set(int n, int d, char* elems , bool* flags){
	if( n== d){
		cout<<"{";
		for(int i=0;i<n;i++){
			if(flags[i])
				cout<<" "<<elems[i];
		}
		cout<<" }\n";
		return;
	}
	flags[d] = true;
	power_set(n ,d+1, elems, flags);
	flags[d] = false;
	power_set(n, d+1, elems, flags);
}

int main(void){
	int N;
	cin>>N;
	char elems[N];
	bool flags[N];
	for( int i=0;i<N;i++){
		cin>>elems[i];
		flags[i] = false;
	}
	power_set(N, 0, elems,flags);
	return 0;
}