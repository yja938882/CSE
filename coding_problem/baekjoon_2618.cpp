#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> ans;
vector< pair<int, int> > pos;

int man_dist( int x, int y, int x1, int y1 ){
	int dx = (x-x1 < 0) ? x1-x : x-x1;
	int dy = (y-y1 < 0) ? y1-y : y-y1;
	return dx + dy;
}

int sol(int N, int C){
	pair<int, int> c1 = make_pair( 1, 1 );
	pair<int, int> c2 = make_pair( N, N );
	int sum=0;
	for( int i=0; i< C; i++ ){
		int c1d = man_dist( c1.first, c1.second ,pos[i].first, pos[i].second);
		int c2d = man_dist( c2.first, c2.second ,pos[i].first, pos[i].second);
		if( c1d > c2d ){
			ans.push_back( 2 );
			c2.first = pos[i].first;
			c2.second = pos[i].second;
			sum += c2d;
		}else{
			ans.push_back( 1 );
			c1.first = pos[i].first;
			c1.second = pos[i].second;
			sum +=c1d;
		}	
	} 	
	return sum;
}

int main( void ){
	int N, C;
	cin >> N >> C;

	for( int c=0; c<C; c++ ){
		int i,j;
		cin >> i >> j;
		pos.push_back( make_pair( i, j ) );		
	}
	int ret = sol( N, C );
	cout << ret <<"\n";
	for( int i=0; i<C; i++ ){
		cout << ans[i] <<"\n";
	}
	return 0;
}
