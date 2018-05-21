#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <set>
using namespace std;
#define LABEL_UNDEF -1;
#define NOISE -2;
struct object{
	int id;
    int label;
	double x;
	double y;
    void print(){
        cout << id << ": (" << x << "," << y <<") [ "<<label <<"]\n";
    }
};

bool compareByX( const object* a, const object* b ){
    return (a->x) < (b->x);
}

bool compareByID( const object* a, const object* b){
	return (a->id) < (b->id);
}

/**
    @breif 에러 발생시 프로그램 종료
    @param msg 출력할 메시지
 */
void error( const char* msg ){
    cout << "[Error] " << msg << "\n";
	exit(-1);
}

/**
    @breif Object Input file 을 읽어 드린다.
    @parma pFileName Object file name
    @param pObjs 데이터를 저장시킬 vector
 */
void read_data( char* pFileName , vector< struct object* > &objs ){
    cout << " read data file ...start!\n";
    
    ifstream filestrm;
    filestrm.open( pFileName );
    if( !filestrm.is_open() ){
        error( "Open file .." );
        return ;
    }
    
    int id = 1;
    while( !filestrm.eof() ){
        int oid;
        double ox, oy;
        filestrm >> oid >> ox >> oy;
        struct object * object = new struct object;
        object-> id = oid;
        object-> x = ox;
        object-> y = oy;
        object-> label = -1;    //Undefined
        objs.push_back( object );
    }
    sort(objs.begin() , objs.end() , compareByX );

    filestrm.close();
    cout << " read data file ... end!\n";
    return ;
}

void DEBUG_print_objects (vector< struct object *> objs ){
    for( int i=0; i<objs.size(); i++ )
        objs[i]->print();
}


double obj_dist( struct object *a, struct object *b ){
    return sqrt( ( (a->x) - (b->x) )*( (a->x) - (b->x) ) + ( (a->y) - (b->y) )*( (a->y) - (b->y) ) );
}

int DBSCAN( int eps, int minpts , vector< struct object* > obj , int N){
    int c =0;
    for( int i=0; i<obj.size(); i++ ){
        if( c >= N ) break;
        
        if( obj[i]->label != -1 ) continue; //if label != undefined continue
        
        int left = i-1;
        int right = i+1;
        vector<int> neighbors;
        while( left >=0 && abs( (obj[left]->x)-(obj[i]->x) ) <= eps ){
            if( obj_dist(obj[left] , obj[i] ) <= eps ) neighbors.push_back( left );
            left --;
        }
        while( right <=obj.size() && abs( (obj[right]->x)-(obj[i]->x) ) <= eps ){
             if( obj_dist(obj[right] , obj[i] ) <= eps ) neighbors.push_back( right );
            right ++;
        }
        if( neighbors.size() < minpts ){
            obj[i]->label = -2; // Noise
            continue;
        }
        c++;
        obj[i]->label = c;
        for( int n=0; n< neighbors.size(); n++ ){
            if( obj[ neighbors[n] ]->label == -2 ){
                obj[ neighbors[n] ]->label = c;
            }
            if( obj[ neighbors[n] ]->label != -1 ){
                continue;
            }
            obj[ neighbors[n] ]->label = c;
            int left_n = neighbors[n]-1;
            int right_n = neighbors[n]+1;
            
            vector< int > new_neighbors;
            while( left_n >=0 && ( abs( (obj[ neighbors[n] ]->x)-(obj[ left_n ]->x) ) <=eps ) ){
                if( obj_dist( obj[ neighbors[n] ] , obj[left_n]) <= eps)
                    new_neighbors.push_back( left_n);
                left_n --;
            }
            while( right_n < obj.size() && ( abs( (obj[ neighbors[n] ]->x )-(obj[ right_n ]->x) ) <= eps )){
                if( obj_dist( obj[ neighbors[n] ] , obj[right_n]) <= eps )
                    new_neighbors.push_back( right_n);
                right_n ++;
            }
            if( new_neighbors.size() >= minpts ){
                for( int nn =0; nn< new_neighbors.size(); nn++ )
                    neighbors.push_back( new_neighbors[nn] );
            }
        }
    }
	return c;   
}

void write_result(int cluster_num, vector< struct object * > objs, string ifname ){
	cout << "write result ...";
	vector< vector< struct object * > > clusters(cluster_num);

	for( int i=0; i<objs.size(); i++ ){
		if( objs[i] -> label == -2 || objs[i] -> label == -1 ) continue;
	 	clusters[ (objs[i] -> label)-1 ].push_back( objs[i] );
	}

	for( int i=0; i< clusters.size(); i++ ){
		cout << " " << i;
		sort( clusters[i].begin(), clusters[i].end(), compareByID);

		string file_name;
		file_name = ifname+"_cluster_"+to_string(i)+".txt";
		ofstream outFile;
		outFile.open(file_name);
		for( int j=0; j<clusters[i].size(); j++ ){
			outFile << to_string(clusters[i][j]->id) << "\n";
		}	
		outFile.close();
	}
	cout << "\n";
}

int main( int argc, char* argv[] ){
    /*
     argv[1] : input file name
     argv[2] : n : number of clusters
     argv[3] : Eps : maximum radius of the neighborhood
     argv[4] : MinPts : minimum number of points in an Eps-neighborhood of a given
     */
	if( argc!=5 ){
		error( "Wrong Argument!" );
        return -1;
	}
    int n = atoi( argv[2] );
    int eps = atoi( argv[3] );
    int minpts = atoi( argv[4] );
    vector< struct object * > objs;
    read_data ( argv[1] ,objs );
 
    int cluster_num = DBSCAN(eps, minpts , objs , n);
	string ifname( argv[1] );
	size_t pos = ifname.find(".txt");
	ifname.erase( pos );
 	write_result ( cluster_num , objs ,ifname );
//    DEBUG_print_objects( objs );
    
    return 0;
}




