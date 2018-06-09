#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "rating_matrix.hpp"
using namespace std;
void error( char * msg ){
	cout << "[Error] " << msg << "\n";
	exit( -1 );
}

bool isR( char c ){
	return c == '\r';
}

Transactions read_transaction_data ( char * file_name ){
	cout << "[*] read transaction data :" << file_name << "... \n";
	
	ifstream trainFile;
	trainFile.open( file_name );
	if( !trainFile.is_open() ){
		error(" open file ... " );
	}

	char buf[ 512 ];
	string inputLine;
	Transactions T;

	while( getline( trainFile , inputLine ) ){
		inputLine.erase( std::remove_if( inputLine.begin() , inputLine.end(), &isR ), inputLine.end() );
		strcpy( buf , inputLine.c_str() );
		char * tk = strtok( buf, "\t" );
		
		int user_id = atoi( tk );
		tk = strtok( NULL, "\t" );

		int item_id = atoi( tk );
		tk = strtok( NULL, "\t" );

		int rating = atoi( tk );
		tk = strtok( NULL, "\t" );
		int time_stamp = atoi( tk );

		tk = strtok( NULL , "\t" );

		T.push( user_id, item_id, rating, time_stamp );
	}
	trainFile.close();
    return T;
}

void wirte_prediction_data( const char * file_name , Transactions test , int** rec_matrix ){
	cout << "[*] write prediction_data : " << file_name << "...\n";

	ofstream outputFile;
	outputFile.open( file_name );
	if( !outputFile.is_open() ){
		error(" open file ... " );
	}

	for( int i=0; i< test.trans.size(); i++ ){
		outputFile << test.trans[i]->user_id << "\t" << test.trans[i]->item_id << "\t" << rec_matrix[ test.trans[i]->user_id ][ test.trans[i]->item_id ] <<"\n";
	}
	outputFile.close();
}

int main( int argc, char** argv ){
	Transactions Train = read_transaction_data( argv[1] );
   	Transactions Test = read_transaction_data( argv[2] );
  
	RatingMatrix R( Train );
    R.initSimilarityMatrix();
    int ** rec_matrix = R.createRecommandedMatrix( 5 );

    string num( argv[1]+1 );
    char buf[255];
    strcpy( buf, num.c_str() );
    char *tk = strtok( buf, "." );


    string outputFile;
    outputFile = "u" + to_string( atoi(tk) ) + ".base_prediction.txt";

 	wirte_prediction_data( outputFile.c_str() ,Test, rec_matrix );
	return 0;
}
