#include <iostream>
#include <vector>
#include <string>
using namespace std;
int max_pay = 0;

/**
	@brief calculate maximum pay and update max_pay
*/
void getMaxPay( vector< pair< int, int > > schedule , int n, int d, bool* visited){
	if( n == d ){
		int total_pay = 0;
		bool temp_visited[ n ];
		for( int i=0; i<n; i++)
			temp_visited [ i ] = false; 

		for( int i=0; i< n; i++){
			if( !temp_visited[i] && visited[i] && schedule[i].first + i <= schedule.size() ){
				total_pay += schedule[i].second;
				// i번째 상담을 했을때, 이후에 불가능한 스케줄 체크
				for ( int j = i; j< i+ schedule[i].first; j++ ){
					temp_visited[j] = true;
				}
			}
		}
		if( total_pay > max_pay)
			max_pay = total_pay;
		return;
	}
	visited[d] = true;
	getMaxPay( schedule, n, d+1, visited );
	visited[d] = false;
	getMaxPay( schedule, n, d+1, visited );
}

int main(void){
	int N;
	bool* visited;
	vector< pair<int, int> > schedule;
	cin>>N;
	visited = new bool[ N ];

	for( int i=0; i<N; i++ ){
		visited [i] = false;
		int time, pay;
		cin>>time>>pay;
		schedule.push_back( make_pair( time, pay ) );
	}
	
	getMaxPay( schedule, N, 0, visited );
	cout<<max_pay;
	return 0;
}