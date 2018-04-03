// Created by 주안
// Copyright 2018년 주안. All rights reserved.

#include <iostream>
#define SWAP(a,b) a^=b; b^=a; a^=b;
using namespace std;

/**
	@brief 퀵 정렬
*/
void quickSort(int *arr, int left, int right){
	int i=left, j = right;
	int pivot = arr[ (left + right) / 2];
	do{
		while(arr[i]<pivot)	i++;
		while(arr[j]>pivot) j--;
		if(i<=j)
			swap(arr[i++],arr[j--]);
	}while(i<=j);

	if(left<j)	quickSort(arr,left,j);

	if(i<right)	quickSort(arr,i,right);
}

int main(void){
	int N;
	cin>>N;
	int arr[N];
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}

	quickSort(arr,0,N-1);

	for(int i=0;i<N;i++){
		cout<<arr[i]<<" ";
	}
}
