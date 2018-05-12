#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main( void ){
	int N;
	vector< pair< int, int > > times;
	cin >> N;
	for( int i=0; i<N; i++ ){
		int start , end ;
		cin >> start >> end;
		times.push_back( make_pair( end , start ) );
	}
	sort( times.begin() , times.end() );

	int count = 0;
	int current = times[0].first;
	count ++;
	for( int i=1; i< times.size(); i++ ){
		if( times[i].second >= current ){
			current = times[i].first;
			count ++;
		}
	}
	cout << count;
	return 0;
}
