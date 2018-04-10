#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int min_diff = INT_MAX;

void updateTeam( vector<int> teamA , vector<int> teamB, int** S){
	int sumA = 0;
	for( int i=1; i<teamA.size(); i++){
		for( int j = 0; j<i; j++){
			sumA +=( S[ teamA[i] ][ teamA[j] ] + S[ teamA[j] ][ teamA[i] ] ) ;
		}
	}

	int sumB = 0;
	for( int i=1; i<teamB.size(); i++){
		for( int j = 0; j<i; j++){
			sumB +=( S[ teamB[i] ][ teamB[j] ] + S[ teamB[j] ][ teamB[i] ] ) ;
		}
	}

	int diff = sumA - sumB;
	if( diff < 0 ) diff *= (-1);

	if(min_diff > diff) min_diff = diff;
}

void combination( int n , int r , bool* flag, int N , int ** S){
	vector<int> teamA;
	vector<int> teamB;
	if( n == r ){
		for( int i=0; i<n; i++){
			flag[i] = true;
		}
		for( int i=0; i<N; i++){
			if(flag[i])	teamA.push_back(i);
			else	teamB.push_back(i);
			
		}
		for( int i=0; i< n; i++){
			flag[i] = false;
		}
		updateTeam( teamA , teamB , S);
		return ;
	}
	if( r== 1){
		for( int i=0; i<n; i++){
			flag[i] = true;
			for( int j=0; j< N;j++){
				if(flag[j])	teamA.push_back(j);
				else	teamB.push_back(j);
			}
			flag[i] = false;

			updateTeam( teamA , teamB , S);

			teamA.resize(0);
			teamB.resize(0);
		}
		return ;
	}
	flag[n-1] = true;
	combination( n-1 , r -1 , flag , N, S);
	flag[n-1] = false;
	combination( n-1 , r , flag , N, S);
}

int main(){
	int N;
	cin>>N;
	int** S = new int* [N];
	bool flag[N];
	for( int i=0; i<N; i++){
		S[i] = new int[N]; 
		flag[i] = false;
		for( int j=0; j<N; j++){
			cin>>S[i][j];
		}
	}

	combination( N , N/2 , flag , N, S);
	cout<<min_diff;
}