#include <iostream>
#include <queue>
using namespace std;

bool isCorrect( int y , int E, int S, int M ){
	int ye = ( (y % 15) == 0 ) ? 15 : (y % 15);
	int ys = ( (y % 28) == 0 ) ? 28 : (y % 28);
	int ym = ( (y % 19) == 0 ) ? 19 : (y % 19);
	return ye == E && ys == S && ym == M;
}

int main(void){
	int E, S, M;
	cin >> E >>S >> M;

	int y = 1;
	while(1){
		if( isCorrect(y , E, S, M) ){
			cout << y<< endl;
			break;
		}
		y++;
	}
	return 0;
}
