#include <iostream>
using namespace std;
int sol( int x1, int y1, int r1, int x2, int y2, int r2 ){
	if( x1 == x2 && y1 == y2 && r1 == r2 )return -1;

	int dx = x1 - x2;
	int dy = y1 - y2;
	int dp = dx*dx + dy*dy;
	int addr = r1*r1 + ( 2*r1*r2 ) + r2*r2;
	int disr = r1*r1 - ( 2*r1*r2 ) + r2*r2;
	
	if( dp < disr ) return 0;
	
	if( dp == disr ) return 1;

	if( dp > disr && dp < addr ) return 2;

	if( dp == addr ) return 1;

	if( dp > addr ) return  0; 
	
	else return 0;
}
int main( void ){
	int T;
	cin >> T;

	for( int t = 0; t < T; t++ ){
		int x1,y1,r1,x2,y2,r2;
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 ;
		cout << sol( x1, y1, r1, x2, y2, r2 ) << "\n";
	} 

}
