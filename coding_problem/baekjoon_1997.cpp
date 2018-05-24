#include <iostream>
using namespace std;


int main( void ){
	int M, N;
	cin >> M >> N;
    
    int i=1 , j=100;
    while(1){
        if( i*i >=M )
            break;
        i++;
    }
    while(1){
        if( j*j <=N )
            break;
        j--;
    }
    
    int sum =0;
    for(int k=i;k<=j;k++) sum+=(k*k);
    
	if( sum == 0)
		cout << "-1";
	else
		cout << sum << "\n" << i*i;
	return 0;
}
