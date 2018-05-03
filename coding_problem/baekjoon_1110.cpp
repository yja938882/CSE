#include <iostream>
using namespace std;
int sol( int p ){
	int n = p;
	int i=0;
	while(1){
		i++;
		int front = n / 10;
		int second = n % 10;
		int sum = front + second;
		int new_n = second*10 + sum % 10;
		if( new_n == p)
			break;
		n = new_n;
	}
	return i;
}
int main( void ){
	int N;
	cin >> N;	
	cout << sol( N );
}
