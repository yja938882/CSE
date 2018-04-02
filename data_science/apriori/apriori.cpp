/**
	@author 연주안
	@brief Apriori Algorithm
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <math.h>
using namespace std;


int trans_num=0;	//트랜젝션의 갯수
typedef struct itemset{
	set<int> intset;
	int support;
} ItemSet;

/**
	@return Set A 가 Set B를 포함하고 있는지 여부 반환 
*/
bool isContain(set<int> A, set<int> B){
	set<int>::iterator itb;
	int count =0;
	for(itb = B.begin(); itb!=B.end();++itb){
		if(A.find(*itb)!=A.end()){
			count++;
		}
	}
	return count==(int)B.size();
}

/**
	@parma pFileName을 파일명으로한 파일에서 input data를 읽어움
	@param pTrans 트렌젝션을 담을 벡터
	@return 읽어드린 트랜젝션의 갯수를 반환
	@warning 에러( File not exist ) 의 경우 -1 반환
*/
int readTrans(char* pFileName, vector< vector<int> > &pTrans){

	ifstream inputFile;
	inputFile.open(pFileName);
	if(!inputFile.is_open()){
		printf("%s is not exist!!\n",pFileName);
		return -1;	
	}
	string INPUT;
	while(getline(inputFile,INPUT)){
		vector<int> trans_line;
		char inc[1000];
		strcpy(inc,INPUT.c_str());
		
		char *tk =  strtok(inc,"\t");
		while(tk!=NULL){
			trans_line.push_back(atoi(tk));
			tk = strtok(NULL,"\t");
		}
		pTrans.push_back(trans_line);
	}
	inputFile.close();
	return (int)pTrans.size();
}

/** 
	@parma pTrans 출력할 트렌젝션 모음
	@brief 트렌젝션 출력
*/
void printTrans(vector<vector<int> > pTrans){
	cout<<"print trasnaction\n";
	for(int i=0;i<pTrans.size();i++){
		for(int j=0;j<pTrans[i].size();j++) cout<<pTrans[i][j]<<" ";
		cout<<"\n";
	}
}

/**
	@param pTrans 트렌젝션
	@param pCand Cnadidates를 담을 벡터
	@brief 1-itemset Candidate 생성
*/
void initCand(vector< vector<int> > pTrans , vector< vector<ItemSet> > &pCand){
	
	vector<ItemSet> tempCand;
	for(int i=0;i<pTrans.size();i++){
		for(int j=0;j<pTrans[i].size();j++){
			int _item = pTrans[i][j];
			int c=0;
			bool incx = false;
			for(;c<tempCand.size();c++){ // 중복되는 경우 support 를 count
				if(tempCand[c].intset.find(_item)!=tempCand[c].intset.end()){
					tempCand[c].support++;
					incx=true;
					break;
				}
			}
			if(!incx){ // 중복되지 않는다면 , 새로운 candidate 추가
				ItemSet _itemset;
				_itemset.intset.insert(_item);
				_itemset.support=1;
				tempCand.push_back(_itemset);
			}
		}
	}
	pCand.push_back(tempCand);
}

/** 
	@param pLength 출력할 Cnadidate itemset의 길이
	@param pCand Candidate 를 담고있는 벡터
	@brief Candidates 를 출력합니다.
*/
void printCand(int pLength, vector< vector<ItemSet> > pCand){
	cout<<"print candidate length :"<<pLength<<"\n";
	for(int i=0;i<pCand[pLength-1].size();i++){
		set<int>::iterator it;
		cout<<"{";
		for(it = pCand[pLength-1][i].intset.begin();
			it!=pCand[pLength-1][i].intset.end();++it){
			cout<<*it<<" ";
		}
		cout<<"} ";
	}
	cout<<"\n";
}

/**
	@parma pLength 현재 Candinates itemset의 길이
	@param pMinSup Minimum support
	@parma pCand Candidates
	@param pFreq Frequent Patterns
	@brief Candidates중에서 Minimum support 이상인 Candidate를 Frequent Pattern 으로 추가 
	
*/
void checkFreq(int pLength,int pMinSup, vector<vector<ItemSet> >pCand, vector<vector<ItemSet> > &pFreq){
	vector<ItemSet> tf;
	for(int i=0;i<pCand[pLength-1].size();i++){
		if( pCand[pLength-1][i].support>=pMinSup){
			ItemSet it;
			it.intset = pCand[pLength-1][i].intset;
			it.support = pCand[pLength-1][i].support;
			tf.push_back(it);
		}
	}
	pFreq.push_back(tf);
}

/**
	@parma pLength 출력 할 Candidates itemset 길이 
	@parma pCand 출력 할 Candidates
	@brief Frequent Pattern을 출력
*/
void printFreq(int pLength, vector< vector<ItemSet> > pCand){
	cout<<"print Freq length :"<<pLength<<"\n";
	for(int i=0;i<pCand[pLength-1].size();i++){
		set<int>::iterator it;
		cout<<"{";
		for(it = pCand[pLength-1][i].intset.begin();
			it!=pCand[pLength-1][i].intset.end();++it){
			cout<<*it<<" ";
		}
		cout<<"} ";
		cout<<"["<<((double)pCand[pLength-1][i].support/(double)trans_num)*100.0f<<"] ";
	}
	cout<<"\n";
}

/**
	@param pLength (K) Frequent Pattern 의 itemset 길이
	@param pFreq Freqent Patterns
	@param pCand Candidates
	@brief (K) Freqent pattern 에서 (K+1) Candidates 를 생성  
*/
void generateCand(int pLength, vector<vector<ItemSet> >pFreq , vector<vector<ItemSet> > &pCand){
	vector<ItemSet> resultSet;
	for(int i=0;i<pFreq[pLength-1].size();i++){
		for(int j=0;j<pFreq[pLength-1].size();j++){
			set<int> setA = pFreq[pLength-1][i].intset;
			set<int> setB = pFreq[pLength-1][j].intset;
			set<int> result;
			set_difference(setA.begin(), setA.end(),
								setB.begin(), setB.end(),
								inserter(result, result.end()));
			set<int>::iterator it;

			// Self Join
			for(it = result.begin();it!=result.end();++it){
				set<int> _itemset = setB;
				_itemset.insert(*it);

				bool b=false;
				for(int s=0;s<resultSet.size();s++){
					set<int> temp;
					set_difference(resultSet[s].intset.begin(), resultSet[s].intset.end(),
							_itemset.begin(), _itemset.end(),
							inserter(temp, temp.end()));
					if(temp.size()<=0){ //중복 확인
						b= true;
						break;
					}
				}
				if(b) break;

				// K Freqeunt Pattern 의 K-1 sub pattern 을 K-1 Frequent pattern 이 가지고 있는지 확인
				set<int>::iterator subit;
				for(subit=_itemset.begin();subit!=_itemset.end();++subit){
					set<int> subse = _itemset;
					subse.erase(*subit);
					
					bool pc = false;
					for(int q=0;q<pFreq[pLength-1].size();q++){
						if(isContain(pFreq[pLength-1][q].intset,subse)){
							pc = true;
							break;
						}
					}
					if(pc==false){ // K-1 sub pattern 을 K freq pattern 이 가지고있지 않음 
						b=true;
						break;
					}
				}
				if(b){ 
					break;
				}

				ItemSet is;
				is.intset = _itemset;
				is.support = 0;
				resultSet.push_back(is);
			}
		}
	}
	pCand.push_back(resultSet);
}

/**
	@param pLenfth Frequent Pattern 의 itemset 길이
	@param pTrans 트랜젝션
	@param pFreq 카운팅할 frequent patterns
	@brief 트랜젝션에서 frequent pattern 을 카운트
*/
void countFreq(int pLength, vector< vector<int> > pTrans, vector<vector<ItemSet> > &pFreq){
		for(int i=0;i<pFreq[pLength-1].size();i++){
			
			for(int j=0;j<pTrans.size();j++){

				set<int>::iterator it;
				int count=0;
				for(it = pFreq[pLength-1][i].intset.begin();
					it!= pFreq[pLength-1][i].intset.end(); ++it){
					//일치하는 아이템 갯수 count
					for(int k=0;k<pTrans[j].size();k++){
						if(*it == pTrans[j][k]){
							count++;
							break;
						}
					}
				}
				if(count!=0 && count == pFreq[pLength-1][i].intset.size()){ 
					//해당 freqent 패턴을 가진 transaction 이 있다면 count
					pFreq[pLength-1][i].support++;
				}

			}

		}
}

/**
	@parma pFreq 
	@brief 모든 Frequent pattern 출력
*/
void printAllFreq(vector<vector<ItemSet> > pFreq){
	for(int i=0;i<pFreq.size();i++){
		cout<<"length :"<<i+1<<"\n";
		for(int j=0;j<pFreq[i].size();j++){
			set<int>::iterator it;
			cout<<"{";
			for(it = pFreq[i][j].intset.begin(); it!=pFreq[i][j].intset.end();++it){
				cout<<*it<<" ";
			}
			cout<<"}";
			cout<<"("<<((double)pFreq[i][j].support / trans_num)*100.0<<") ";
		}
		cout<<"\n";
	}
}

/**
	@param outFile 출력할 스트림
	@param a 출력할 set
	@brief set 을 형식에 맞게 출력합니다.
*/
void printSet(ofstream &outFile, set<int> a){
	outFile<<"{";
	set<int>::iterator it;
	for(it=a.begin();it!=a.end();){
		outFile<<*it;
		it++;
		if(it!=a.end())
			outFile<<",";
	}
	outFile<<"}";
}

/**
	@param pFileName 출력할 파일명
	@param pFreq Association Rule 을 출력할 frequent pattern
	@brief frequent pattern에서 Association Rule 을 출력
*/
void writeResult(char* pFileName, vector<vector<ItemSet> > pFreq){

	ofstream outFile;
	outFile.open(pFileName);

	outFile<<fixed<<setprecision(2);
	for(int i=0;i<pFreq.size();i++){
		for(int j=0;j<pFreq[i].size();j++){
			set<int> is = pFreq[i][j].intset;
			
			for(int si=i+1;si<pFreq.size();si++){
				for(int sj=0;sj<pFreq[si].size();sj++){
					set<int> super_is = pFreq[si][sj].intset;
					if(isContain(super_is, is)){
		
					set<int> result;
					set_difference(super_is.begin(), super_is.end(),
								is.begin(), is.end(),
								inserter(result, result.end()));
			

						printSet(outFile,is);
						outFile<<"\t";
						printSet(outFile,result);
						outFile<<"\t";	
						outFile<<(pFreq[si][sj].support/(double)trans_num) * 100<<"\t";
						
						/*
						소수점 작업. 
						*/
						double confr = (pFreq[si][sj].support*100.0/(double)pFreq[i][j].support)+0.005;
						int confir = (int)(confr*1000.0);
						confir/=10;
						confr = (double)confir;
						confr/=100.0;
						outFile<<confr;
						outFile<<"\n";
					}
				}
			}

		}
	}	

	outFile.close();	
}

int main(int argc, char* argv[]){
	cout<<"apriori start .";	
	vector< vector<int> > trans; // transaction
    
    vector< vector<ItemSet> > freqItemSet;
    vector< vector<ItemSet> > candItemSet;
    
	if(argc!=4){	//argument error
		printf("[ERROR] wrong argument!! >");
		printf("%s [minimum support] [inputfile] [outputfile]\n",argv[0]);
		return -1;
	}

	
	double min_sup = (atof(argv[1]));	//Minimum support
	char* input_file = argv[2];				// 입력 파일 이름
	char* output_file = argv[3];			// 출력 파일 이름


	//트랜젝션 을 읽어드림
	trans_num = readTrans(input_file, trans);
	if(trans_num==-1)
		return -1;

	// min sup 을 numeric 하게 변환 
	int min_sup_as_num = (int)ceil(((double)trans_num/100)*min_sup);
	cout<<min_sup_as_num;

	initCand(trans,candItemSet);
	checkFreq(1,min_sup_as_num,candItemSet,freqItemSet);


	int i=1;
	while(1){
		cout<<".";
		generateCand(i++,freqItemSet,candItemSet);
		countFreq(i,trans,candItemSet);
		checkFreq(i,min_sup_as_num,candItemSet,freqItemSet);
		if(freqItemSet[freqItemSet.size()-1].size()==0){ //Frequent Pattern 이 더이상 생성되지 않으면 break
			break;
		}
	}
	writeResult(output_file,freqItemSet);


	return 0;
}
	
