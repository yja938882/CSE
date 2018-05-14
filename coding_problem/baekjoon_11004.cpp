#include <iostream>
#include <climits>
#include <cstdio>
using namespace std;

int partition(int *arr, int left, int right){
    int p = arr[right], i = left;
    for( int j=left; j<= right-1; j++ ){
        if( arr[j] <= p ){
            swap(arr[i],arr[j]);
            i++;
        }
    }
    swap(arr[i],arr[right]);
    return i;
}

int quickSelect(int *arr , int left, int right, int k)
{
    if( k>0 && k <= right - left +1 ){
        int part = partition( arr, left, right );
        
        if( part - left == k-1 )    return arr[part];
        if( part - left > k-1 )        return quickSelect( arr, left, part-1, k );
        return quickSelect( arr, part + 1, right, k -part +left -1 );
    }
    return INT_MAX;
}

int main(){
    int N;
    cin>>N;
    
    int K;
    cin>>K;
    int arr[N];
    for( int i=0; i<N; i++ ){
        scanf("%d",&arr[i]);
    }
    cout<< quickSelect( arr, 0, N-1, K );
    
    return 0;
}



