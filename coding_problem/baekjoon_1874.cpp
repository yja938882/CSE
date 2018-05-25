#include <cstdio>
#include <vector>
#include <string>
using namespace std;

int stk[100001];
int stop = -1;
void push( int a ){
	stk[++stop] = a;
}
void pop(){
	stop --;
}
int top(){
	return stk[stop];
}
bool empty(){
	return stop == -1;
}
vector< string > ans;
int main( void ){

	int n;
	scanf("%d",&n);
	int push_num = 1;
	int error = -1;
	for( int i=0; i< n; i++ ){
		int a;
		scanf("%d",&a);
		if( error == 1) continue;		

		while( top() < a || empty() ){
			ans.push_back("+");
			push( push_num ++ );
		}
		if( top() != a ) {
			error = 1;
			printf("NO");
			return 0;
		}
		pop();
		ans.push_back("-");
	}
	if( error == 1 ) return 0;

	for( int i=0; i< ans.size(); i++ ){
		printf("%s\n",ans[i].c_str() );
	}
	return 0;	
}
