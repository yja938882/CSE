//  Created by 주안
//  Copyright © 2018년 주안. All rights reserved.

#include <iostream>
using namespace std;

/**
    @brief arr[left ... mid] , arr[mid+1 ... right ] 두 배열을 정렬하며 병합한다.
*/
void merge(int *arr, int left,int mid, int right){
    int i = left , j = mid+1, k = 0;
    int temp[right-left+1];
    while(i<=mid && j<=right){
        if(arr[i]< arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }
    while(i<=mid)
        temp[k++] = arr[i++];
    while(j<=right)
        temp[k++] = arr[j++];
    
    for(int t=0;t<right-left+1;t++){
        arr[left+t] = temp[t];
    }
}

/**
    @breif 배열을 나눈뒤 다시 병합한다.
 */
void mergeSort(int *arr, int left, int right){
    int mid = (right+left)/2;
    if(left<right){
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}

int main() {
    int N;
    cin>>N;
    int arr[N];
   
    //입력
    for(int i=0;i<N;i++)    cin>>arr[i];
    
    //정렬
    mergeSort(arr,0,N-1);
    
    //출력
    for(int i=0;i<N;i++)    cout<<arr[i]<<" ";
  
    return 0;
}
