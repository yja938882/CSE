#include <iostream>
using namespace std;
int sol( int n ){
	int five_num = n / 5;
	while(1){
		if( five_num < 0) break;

		int remain = n - five_num*5;
		if( remain % 3 == 0 ){
			return five_num + remain/3;
		}
		five_num --;
	}
	return -1;
}

int main( void ){
	int N;
	cin >> N;
	cout << sol( N );
}
/Users/juan/Desktop/cse/coding_problem/baekjoon_2839.cpp
