#include <cstdio>
using namespace std;
char input[1000001];
int main( void ){
	
	int cnt=0;
	while( scanf("%s",input )!=EOF ){
		cnt ++;
	}
	
	printf("%d",cnt-1);
	return 0;
}

