#include <iostream>
using namespace std;
int main( void ){
	long long A, B, C;
	cin >> A >> B >> C;
	long long ans = 1;
	while(B){
		if( B%2 ){
			ans*=A;
			ans%=C;
		}
		A*=(A) ;
		A%=C;
		B/=2;
	}
	cout << ans%C;
}
