#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <map>
#include <math.h>
using namespace std;
/* Copyright Yeon juan - All Rights Reserved
 */
bool GreaterPair( const pair<double , int> & a, const pair<double, int>& b){
	return a.first > b.first;
}
/**
	Attribute, Label , Tuple을 정수형 ID 형태로 관리하기 위한 클래스.
*/
class IdMap{
    public :
    map< string, int > attrIdMap;	// (attribute , id ) map
	map< int , string > idAttrMap;	// (id , attribute ) map
    int attrId;						// attribute에 할당할 ID 
	vector< map< string ,int > > labels_id;		// (label , id) map
	vector< map< int , string > > id_labels;	// ( id , label) map
	int *labelId;	// label 에 할당할 ID 
	int classId;	// Class 에 해당하는 attribute  ID
	vector<vector<int> > tuples;	// Tuple
	double infoD;	// info(D)
	vector< pair< double, int > > gain;
	IdMap(){
		attrId = 0;
	}

	/**
		@param p Class P 갯수
		@param n Class N 갯수
		@brief return I( p , n )
	*/
	double _I( int p , int n){
		double btm = (double)(p+n);
		double tp = (double)p;
		double tn = (double)n;
		if(n==0.0 || p==0.0)
			return 0.0;
		return -( ( tp/btm )*log2( tp/btm ) +  ( tn/btm )*log2( tn/btm ) );
	}
	
	/**
		@param pAttr attribute 이름
		@brief attribute 추가, 자동으로 id 할당
	*/
	void insertAttr( string pAttr){
		if(pAttr.find("\t")!=string::npos)
			cout<<"BIP!!!!";

		cout<<"insert attr "<<endl;
		cout<<" : "<<pAttr<<endl;
        map<string, int>::iterator it = attrIdMap.find(pAttr);
        if(it==attrIdMap.end()){
			string ats = pAttr;
            attrIdMap.insert( map<string, int>::value_type(ats, attrId) );
			idAttrMap.insert( map<int, string>::value_type(attrId, pAttr));
			classId = attrId;   	
		    attrId++;
        }
	}

	/**
		@param id attribute 의 id
		@return id에 해당하는 attribute 이름
	*/
	string getIdAttr(int id){
		map<int, string>::iterator it = idAttrMap.find(id);
		if(it == idAttrMap.end())
			return "";
		else
			return it->second;
	}

	int getAttrId( string attr ){
		cout<<"get attr : ";
		cout<< attr <<endl;
		map<string , int >::iterator it = attrIdMap.find(attr);
		if(it == attrIdMap.end()){
			cout<< " nf"<<endl;
			map<int , string>::iterator itm;
			cout<<"search "<<endl;
			for( itm = idAttrMap.begin(); itm!= idAttrMap.end() ; ++itm){
				cout<<" * "<<itm->second.c_str()<<" ";

				//if( ! attr.compare ( itm->second)){
				//	cout<<" nf return - "<<itm->first<<endl;
				//	return itm->first;
				//}
			}
			return 0;
		}else{
			cout<< "return - "<< (it->second) <<endl;
			return it->second;
		}
	}
	
	/**
		@brief label 초기화
		@warning : Attr을 모두 추가한후에 호출해야함
	*/
	void initLabel(){
		labelId = new int[attrId];
	
		for( int i = 0; i < attrId; i++) labelId[i] = 0;
		labels_id.resize( attrId );
		id_labels.resize( attrId );
	}

	/**
		@param pAttrId attribute Id
		@param pLabel label 이름
		@brief 라벨 추가, 자동으로 Id 추가
	*/
	void insertLabel( int pAttrId, string pLabel){

		if(pLabel.find("\t")!=string::npos)
			cout<<"BIP!!!!";

		map< int , string >::iterator idattr_it = idAttrMap.find(pAttrId);
		if( idattr_it == idAttrMap.end() ){
			printf("[error] \n");
			return;
		}
		map<string , int>::iterator labelid_it = labels_id[pAttrId].find(pLabel);
		if( labelid_it == labels_id[pAttrId].end() ){
			labels_id[pAttrId].insert( map<string, int>::value_type(pLabel , labelId[pAttrId]));
			id_labels[pAttrId].insert( map<int, string>::value_type(labelId[pAttrId] , pLabel));
			labelId[pAttrId]++;
		}
	}

	/**
		@pTuple 튜플
		@brief Tuple 추가
	*/
	void insertTuple(string pTuple){
		vector<int> tuple;
		char buf[512];
		strcpy( buf,pTuple.c_str() );
		char *tk = strtok(buf,"\t"); 
		int attr_id = 0;
		while( tk!=NULL ){
			string label(tk);
			this->insertLabel(attr_id , label);
			tuple.push_back( (this->getLabelId(attr_id , label )));
			tk = strtok(NULL,"\t");
			attr_id++;
		}
		(this->tuples).push_back(tuple);
	}

	/**
		@param pAttrId attribute id
		@param pLabel label 이름
		@return label id 반환
	*/
	int getLabelId(int pAttrId , string pLabel){
		if(labels_id[pAttrId].count(pLabel) ==0){
			cout<<endl;
			cout<<"get label id ERROR!!!==== "<<endl;
			cout<<pAttrId<<endl;
			cout<<pLabel<<endl;
			char buf[100];
			strcpy(buf, pLabel.c_str());
			for( int i=0;i <pLabel.length(); i++)
				cout<<buf[i]<<" ";

			cout<<"DUMP!"<<endl<<endl;
			map<string, int>::iterator it;
			for( it = labels_id[pAttrId].begin(); it!=labels_id[pAttrId].end();++it ){
					cout<<it->first <<" ";
					char buf2[100];
					strcpy(buf2, (it->first).c_str());
					for( int i=0;i <pLabel.length(); i++)
						cout<<buf2[i]<<" ";

					if(strcmp( pLabel.c_str(), (it->first).c_str()) == 0)//pLabel.compare(it->first) ==0)
						cout<<"(m)";
					else
						cout<<"(um) ";
			}

			cout<<endl;
			cout<<"==========="<<endl;
			return 0;
		}
		return (labels_id[pAttrId].find(pLabel))->second;
	}

	/**
		@param pAttrId attribute id
		@param pLabelId label id
		@return 라벨의 이름 반환
	*/
	string getIdLabel( int pAttrId, int pLabelId){
		return (id_labels[pAttrId].find(pLabelId)->second);
	}

	/**
		@breif info(D), Gain( attrs ...) 를 계산 
	*/
	void setInformation(){
		int infoDcount[2];
		infoDcount[0] = 0;
		infoDcount[1] = 0;
		for(int t = 0; t<tuples.size(); t++){
			infoDcount[tuples[t][classId]]++;
		}
		infoD = _I(infoDcount[0] , infoDcount[1]);

		for( int a=0; a<attrId; a++){
			if( a==classId ) continue;

			int infoTable[ labelId[a] ][ labelId[classId] ];
			for( int i=0; i< labelId[a] ;i++){
				for( int l =0; l< labelId[classId]; l++)
					infoTable[i][l] = 0;
			}

			for( int t=0; t<tuples.size(); t++){
				infoTable[ tuples[t][a] ][ tuples[t][classId] ]++;
			}

			double labelInfo[ labelId[a] ];
	
			for( int l=0; l<labelId[a] ; l++){
				labelInfo[l] = this->_I(infoTable[l][0] , infoTable[l][1]);
			}
			double info = 0.0;
			for( int l=0; l<labelId[a]; l++){
				info +=  labelInfo[l] * ((double)(infoTable[l][0] + infoTable[l][1]) /((double) (tuples.size())));
			}
			pair< double, int > g = make_pair( infoD - info, a);
			gain.push_back(g);
		}
		sort(gain.begin(), gain.end(),GreaterPair);
	}

	/**
		@breif : for DEBUG . map 의 모든 내용 출력
	*/
	void printMap(){
		for( int aid=0; aid<attrId; aid++){
			cout<<getIdAttr(aid)<<endl;
			for(int lid =0; lid<labelId[aid]; lid++){
				cout<<getIdLabel(aid , lid )<<endl;
				cout<<getLabelId(aid,getIdLabel(aid , lid ) );
			}
			cout<<endl;	
		}	
	}

	/**
		@breif : for DEBUG . 모든 튜플 출력
	*/
	void printTuples(){
		for(int i=0;i<tuples.size();i++){
			cout<<i<<endl;
			for( int t=0; t< tuples[i].size(); t++){
				string _label = (this)->getIdLabel( t, tuples[i][t] );
				cout<< _label<<" (";
				cout<< this->getLabelId( t,_label);
				cout<<")";
			}
			cout<<endl;
		}

	}

	/**
		@breif : for DEBUG . Gain 출력
	*/
	void printGain(){
		cout<<endl;
		for(int i=0; i<gain.size(); i++){
			cout<< gain[i].second <<" "<<gain[i].first<<endl;
		}
	}
};

/**
 	@brief : 에러메시지 출력후 프로그램 종료.
 */
void error(const char* msg){
    printf("[error] %s\n",msg);
    exit(-1);
}

typedef struct DecisionNode{
	bool isLeaf;// 맨 마지막 노드 인지 
	vector< int > tupleId; // 해당하는 튜플 ID
	vector< struct DecisionNode *> children;
	int splitId;
	int resultLabelId;

} Node;

class DecisionTree{
	public :
	Node* root;
	IdMap idMap;
	DecisionTree(IdMap pIdMap){
		idMap = pIdMap;
	} 
	Node* createNode(){
		Node* node = new Node;
		node->isLeaf = false;
		return node;
	}

	bool isInSameClass(vector<int> pTupleId){
		if(pTupleId.size()<=0)
			return true;
		int first_class = idMap.tuples[ pTupleId[0] ][idMap.classId];
		for( int i=0; pTupleId.size(); i++){
			if(idMap.tuples[ pTupleId[i] ][idMap.classId] != first_class) return false;
		}
		return true;
	}

	void insertTuple(Node* node, int pTupleId){
		node-> tupleId.push_back(pTupleId);
	}

	bool hasAllSameLabel( int pAttrId, vector<int> pTupleId){
		int label = idMap.tuples[ pTupleId[0] ][pAttrId];
		for( int i=0;i< pTupleId.size(); i++){
			int tid = pTupleId[i];
			if(idMap.tuples[ tid ][ pAttrId] != label ) return false;
		}
		return true;
	}

	void buildTree( Node* node , int pPrio){
	
		if(node == NULL)
			return;
		if( node->tupleId.size()<=0)
			return;
		if( node->isLeaf)
			return;
		if( hasAllSameLabel(idMap.classId, node->tupleId)){
			node->isLeaf = true;
			node->resultLabelId = idMap.tuples[ node->tupleId[0]][idMap.classId];
			return;
		}
		if( pPrio >= idMap.gain.size() )
			return;
		if( hasAllSameLabel( idMap.gain[pPrio].second , node->tupleId) ){
			buildTree( node , pPrio +1);
			return;
		}


		int split_id = idMap.gain[pPrio].second;
		node->splitId = split_id;
		node->children.resize( idMap.labelId[split_id] );
		
		vector< vector< int > > spliteTuples( idMap.labelId[split_id] );
		vector< vector< int > > tuples = idMap.tuples;
		for( int i=0; i<node->tupleId.size(); i++){
			spliteTuples[ tuples[ node->tupleId[i] ][ split_id] ].push_back( node-> tupleId[i] );
		}

		for( int i=0; i<spliteTuples.size(); i++){
			if( spliteTuples[i].size()<=0 ){
				node->children[i] = NULL;
				continue;
			}else{
				node->children[i] = createNode();
			}

			for( int j=0;j< spliteTuples[i].size(); j++)
				insertTuple( node-> children[i] , spliteTuples[i][j] );
			buildTree( node->children[i], pPrio +1);
		}


	}

	void createTree(){
		root = this->createNode();
		for(int i=0; i<idMap.tuples.size();i++){
			this->insertTuple(root,i);
		}
		buildTree( root , 0);
	}

	string decisionClass( vector< int> tuple){

		return "";
	}

	void printTuple(Node *node){
		for( int i=0;i<node->tupleId.size();i++){
			cout<< node->tupleId[i]<< " ";
		}
		cout<<endl;
	}

	void printNode(Node *node, int level){
		for( int i=0; i<level; i++)
			cout<<"\t";
		if( node-> isLeaf ){
			cout<<idMap.getIdLabel(idMap.classId, idMap.tuples[ node->tupleId[0] ][idMap.classId] )<<flush;

		}else{
			cout<<"["<<idMap.getIdAttr(node->splitId)<<"]";
	
			cout<<" tid : ";
			for( int i=0;i<node->tupleId.size(); i++)
				cout<<node->tupleId[i]<<" ";
		}
	
		cout<<endl;
		for( int i=0;i< node->children.size(); i++){
			if(node->children[i] != NULL){

				printNode( node->children[i] , level +1);
			}
		}
	}

	void printTree(){
		cout<<endl;
		cout<<"print Tree"<<endl;
		printNode(root , 0);
	}

	string getTestResult(vector< int > pTestTuple){
		Node* node = root;
		while( !(node->isLeaf) ){
			node = node->children[pTestTuple[ node->splitId ]];
		}
		return idMap.getIdLabel( idMap.classId , node->resultLabelId );
	}

};

/**
 	@param pFileName : 트레이닝 데이터 파일명.
 */
void readTrainData(char * pFileName, IdMap &pIdMap , vector< pair<int,int> > &pData){
    char buf[512];
	ifstream trainFile;
    trainFile.open(pFileName);
    if(!trainFile.is_open()){
        error("open file...");
    }
    string inputLine;
    
	getline(trainFile, inputLine);
	replace(inputLine.begin(), inputLine.end(), '\r','\0');

	strcpy(buf,inputLine.c_str());
	char *tk = strtok(buf,"\t");
	cout<<inputLine<<endl;
	while( tk!=NULL ){
		string attr(tk);
		pIdMap.insertAttr(attr);
		tk = strtok(NULL,"\t");
	}

	pIdMap.initLabel();

	int attr_id = 0;
	int tuple_index =0;	
	while(getline(trainFile,inputLine)){
	replace(inputLine.begin(), inputLine.end(), '\r','\0');
		pIdMap.insertTuple(inputLine);
    }
    pIdMap.setInformation();
//	pAttrIdMap.printMap(); //for DEBUG
//	pAttrIdMap.printTuples(); //for DEBUG
	pIdMap.printGain();
    trainFile.close();
}

/**

*/
void readTestData(IdMap pIdMap, char *pFileName ,vector<int> &pAttr, vector< vector <int> > &pTestData ){
	cout<<"read TestData ..."<<endl;
	char buf[512];
	ifstream testFile;
	testFile.open(pFileName);
	if(!testFile.is_open()){
		error("open file...");
	}
	string inputLine;
	getline(testFile, inputLine);
	replace(inputLine.begin(), inputLine.end(), '\r','\0');
	strcpy( buf, inputLine.c_str() );
	char* tk = strtok(buf, "\t");
	
	int attrid=0;
	while( tk!= NULL){
		string attr(tk);
		cout<<attr<<endl  ;
		pAttr.push_back(attrid);
		tk = strtok(NULL, "\t");
		attrid++;
	}

	while(getline(testFile, inputLine)){
	replace(inputLine.begin(), inputLine.end(), '\r','\0');
		strcpy( buf, inputLine.c_str() );
		tk = strtok(buf, "\t");
		vector< int > tuple;
		int ati = 0;
		while( tk!=NULL ){
			string label(tk);
		
			tuple.push_back( pIdMap.getLabelId( pAttr[ati] , label));
			//cout<<pIdMap.getLabelId( pAttr[ati] , label);
			ati ++;
			tk = strtok(NULL, "\t");
		}

		pTestData.push_back( tuple );
	}
	testFile.close();
}

void printTestData(IdMap pIdMap, vector<int> pAttr, vector< vector<int> > pTestTuple){
	cout<<"print Test Data"<<endl;
	cout<<"size : "<<pTestTuple.size()<<endl;
	for( int i=0; i<pAttr.size() ; i++){
		cout<<pIdMap.getIdAttr( pAttr[i] )<<" ";
	}
	cout<<endl;
	for( int i=0; i<pTestTuple.size(); i++){
		for( int j=0; j<pTestTuple[i].size(); j++){
			cout<<pIdMap.getIdLabel( pAttr[j] , pTestTuple[i][j] )<<" ";
		}
		cout<<endl;
		for( int j=0; j<pTestTuple[i].size(); j++){
			cout<< pTestTuple[i][j]<<" ";
		}
		cout<<endl;
	}


	cout<<endl;
	cout<<"-end";
	cout<<endl;
}

/**
	
*/
void wirteResult(char* pFileName , DecisionTree pDTree, vector< int> pAttr, vector< vector<int > > pTestTuple){
	ofstream outFile;
	outFile.open(pFileName);
	if(!outFile.is_open()){
		error("open file...");
	}
	for( int i=0; i<pAttr.size(); i++){
		outFile << pDTree.idMap.getIdAttr(pAttr[i]) <<"\t";
	}
	outFile << pDTree.idMap.getIdAttr( pDTree.idMap.classId )<<"\t";
	outFile<<"\n";

	for( int i=0;i<pTestTuple.size();i++){
		for( int j=0;j<pTestTuple[i].size(); j++){
			outFile<<pDTree.idMap.getIdLabel(pAttr[j], pTestTuple[i][j] )<<"\t";
		}
		outFile<<pDTree.getTestResult(pTestTuple[i]);
		outFile<<"\n";
	}
	outFile.close();

}

int main(int argc, char *argv[]){
	IdMap idMap;
	
    if(argc!=4) error("wrong arguments...");
    
	vector< pair<int ,int> > data;
	readTrainData(argv[1] , idMap , data);
	DecisionTree dTree = DecisionTree(idMap);
	dTree.createTree();
	dTree.printTree();

	vector<int> test_attrs;
	vector< vector<int> > test_tuples;
    readTestData(idMap , argv[2] , test_attrs, test_tuples);
    wirteResult(argv[3] , dTree , test_attrs , test_tuples );
    
  	
    return 0;
}
