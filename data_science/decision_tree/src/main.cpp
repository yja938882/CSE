#include "DecisionTable.hpp"
#include "DecisionTree.hpp"
#include <fstream>
/**
 	@brief : 에러메시지 출력후 프로그램 종료.
 */
void error(const char* msg){
    printf("[error] %s\n",msg);
    exit(-1);
}

/**
    @brief Training 데이터를 읽어드린다.
    @param pFileName 읽어 드릴 파일 이름
    @pram 저장할 데이터 vector
*/
void readTrainData(char * pFileName, DecisionTable &pDT ){
 	cout << "> read training data ... ";
    char buf[512];
	ifstream trainFile;
    trainFile.open(pFileName);
    if(!trainFile.is_open()){
        error("open file...");
    }
    string inputLine;
	getline(trainFile, inputLine);
	replace(inputLine.begin(), inputLine.end(), '\r','\0'); // for Windows txt
	strcpy(buf,inputLine.c_str());
	char *tk = strtok(buf,"\t");

	// read attribute
    while( tk!=NULL ){
		string attr(tk);
		pDT.insert_attr(attr);
		tk = strtok(NULL,"\t");
	}
	pDT.init_label();

    // read tuples
	while(getline(trainFile,inputLine)){
		pDT.insert_tuple(inputLine);
    }
    pDT.debug_print_al();
    trainFile.close();
    cout << "end!\n";
}

void readTestData(DecisionTable pDT, char *pFileName ,vector<int> &pAttr, vector< vector <int> > &pTestData ){
    cout<<"> read test data..."<<endl;
    char buf[512];
    ifstream testFile;
    testFile.open(pFileName);
    if(!testFile.is_open()){
        error("open file...");
    }
    string inputLine;
    getline(testFile, inputLine);
    replace(inputLine.begin(), inputLine.end(), '\r','\0'); // for Windows txt
    strcpy( buf, inputLine.c_str() );
    char* tk = strtok(buf, "\t");
    
    // Read attributes
    int attrid=0;
    while( tk!= NULL){
        string attr(tk);
        pAttr.push_back(attrid);
        tk = strtok(NULL, "\t");
        attrid++;
    }

    // Read tuples
    while(getline(testFile, inputLine)){
        replace(inputLine.begin(), inputLine.end(), '\r','\0'); // for Windows txt
        strcpy( buf, inputLine.c_str() );
        tk = strtok(buf, "\t");
        vector< int > tuple;
        int ati = 0;
        while( tk!=NULL ){
            string label(tk);
            tuple.push_back( pDT.get_id_by_label(pAttr[ati],label));
            ati ++;
            tk = strtok(NULL, "\t");
        }
        pTestData.push_back( tuple );
    }
    testFile.close();
    cout << "end!\n";
}

/**
    @brief 결과를 파일에 저장
*/
void writeResult(char* pFileName , DecisionTable pDT, DecisionTree pDtree, vector< vector<int > > pTestTuple){
    cout << "write result ...\n";
    ofstream outFile;
    outFile.open(pFileName);
    if(!outFile.is_open()){
        error("open file...");
    }
    for( int i=0; i< pDT.attrs_size(); i++ ){
        outFile << pDT.get_attr_by_id(i) <<"\t";
    }
    outFile<<"\n";

    for( int i=0; i<pTestTuple.size(); i++ ){
        for( int j=0; j< pTestTuple[i].size()-1; j++ ){
            outFile << pDT.get_label_by_id( j, pTestTuple[i][j] )<<"\t";
        }
        outFile << pDT.get_label_by_id( pDT.get_class_id(), pTestTuple[i][ pTestTuple[i].size() -1 ] )<< "\n";
    }
    outFile.close();
    cout << "end!\n"; 
}


int main(int argc, char *argv[]){
    DecisionTable dt;

    // wring arguments
    if( argc != 4 ){
        cout << "wrong argument! \n";
        return -1;
    }

    // Read training data 
    readTrainData( argv[1] , dt );

    // Build decision tree
    DecisionTree decision_tree ( dt );
    decision_tree.create_tree();
    decision_tree.debug_print_t( decision_tree.root , 0, 0 ,0);
    
    // Read test data
    vector< int> attr;
    vector< vector< int > > test_data;
    readTestData(dt, argv[2],attr, test_data);
    
    // decision
    for( int i=0; i< test_data.size(); i++){
        decision_tree.classify( decision_tree.root , test_data[i] );
    }

    //write result
    writeResult(argv[3], dt ,decision_tree, test_data );
    return 0;
}


