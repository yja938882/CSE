#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

long long gcd( long long a, long long b ){
	int mod = a % b;
	while ( mod > 0 ){
		a = b;
		b = mod;
		mod = a % b;
	}
	return b;
}


int main( void ){
	int N;
	scanf("%d",&N);
	long long M[ N ];
	vector< long long > diff; 
	scanf("%lld",&M[0]);
	int d;
	for( int i=1; i<N; i++ ){
		scanf("%lld",&M[i]);
		d = M[i] - M[i-1];
		if( d <0 ) d *= -1; 
		diff.push_back(d);
	}
	for( int i=N-1; i>0; i-- ){
		diff.push_back( M[i] - M[i-1] );
	}
	long long gd = diff[0];
	
	for( int i=1; i< diff.size(); i++ ){
		gd = gcd( diff[i], gd );
	}
	long long max = gd;	
	vector< long long > ret;
	for( long long i=1; i<= max; i++ ){
		if( gd%i == 0 ){				
			if( i!=1)
				printf("%lld ",i);
			if( i != gd/i )
				ret.push_back(gd/i);
		}
		max = gd/i;
	}
//	printf("\n");
	for( int i=ret.size() -1; i >= 0; i--){
		printf("%lld ",ret[i]);
	}
	return 0;
}
