#include "rating_matrix.hpp"

Transactions::Transactions(){
	this -> max_user_id = -1;
	this -> max_item_id = -1;
}

void Transactions::push( int uid, int iid, int rating, int t_stamp ){
	if( uid > max_user_id ) max_user_id = uid;
	if( iid > max_item_id ) max_item_id = iid;
	struct transaction * t = new transaction( uid, iid, rating, t_stamp );
	trans.push_back( t );
}

void Transactions::DEBUG_print(){
    for( int i=0; i< trans.size(); i++ ){
        cout << trans[i]->user_id << " " << trans[i] -> item_id << " " << trans[i]->rating << "\n" ;
    }
}

RatingMatrix::RatingMatrix( Transactions T ){
	this -> numOfUser = T.max_user_id + 1;
	this -> numOfItem = T.max_item_id + 1;

	matrix = new int*[ numOfUser];
 	for( int i=0; i< numOfUser ; i++ ){
		matrix[i] = new int [ numOfItem ];
		for( int j=0; j< numOfItem; j++ ){
			matrix[i][j] = 0;
		}
	}
    
    vec_sums = new double[ numOfUser ];
    for( int i=0; i< numOfUser; i++ )
        vec_sums[i] = 0.0;

	for( int i=0; i< T.trans.size() ; i++ ){
        double rate = (T.trans[i])->rating;
		matrix[ (T.trans[i])->user_id ][ (T.trans[i])-> item_id ] =( rate );
        vec_sums[ (T.trans[i])->user_id ] += ( rate * rate );
	}
    for( int i=0; i<numOfUser; i++ ){
        vec_sums[i] = sqrt( vec_sums[i] );
    }
}

double RatingMatrix::cosine_similarity( int uid_a, int uid_b ){
    double w = 0.0;
    for( int i=1; i< numOfItem; i++ ){
        if( matrix[uid_a][i] == 0 || matrix[uid_b][i] ==0  ) continue;
        w+= ( matrix[uid_a][i] / vec_sums[uid_a] ) * ( matrix[uid_b][i] / vec_sums[uid_b] );
    }
	//cout << w <<"\n";
    return w;
}

void RatingMatrix::initSimilarityMatrix(){
    cout << "[*] get similarity Matrix \n";
    sim_matrix = new double*[ numOfUser ];
    for( int i=0; i< numOfUser ; i++ )
        sim_matrix[i] = new double[ numOfUser ];
    
    for( int i=1; i< numOfUser; i++ ){
        for( int j=1; j< numOfUser; j++ ){
            sim_matrix[i][j] = cosine_similarity( i, j );
        }
    }
}

vector<int> RatingMatrix::getNeighbor( int uid ){
    vector< pair< double, int > > pv;
    for( int i=1; i< numOfUser; i++ ){
        if( i == uid ) continue;
        pv.push_back( make_pair( sim_matrix[uid][i] , i ) );
    }
    sort( pv.begin(), pv.end(),greater< pair<double,int> >() );
    
    vector<int> ret;
    for( int i=0; i<pv.size(); i++ ){
        ret.push_back( pv[i].second );
    }
    return ret;
}

int RatingMatrix::recommand( int item_id , vector<int> neighbors, int k ){
    int sum = 0;
    int cnt = 0;

    for( int i=0; i< neighbors.size() && cnt < k ; i++ ){
   		if( matrix[ neighbors[i] ][ item_id ] == 0 ) continue;
	    sum += matrix[ neighbors[i] ][item_id];
		cnt++;
    }
	if( cnt == 0 ) return 0;
    return sum/cnt;
}

int** RatingMatrix::createRecommandedMatrix( int k ){
    cout << "[*] create Recommand Matrix ...\n";
    int ** rec_matrix;
    rec_matrix = new int*[ numOfUser ];
    for( int i=0; i< numOfUser; i++ ){
        rec_matrix[i] = new int[ numOfItem ];
    }
    
    for( int i=1; i< numOfUser; i++ ){
        vector<int> neighbor = getNeighbor( i ); 
		for( int j=1; j<numOfItem; j++ ){
            if( matrix[i][j] == 0 ){
                rec_matrix[i][j] = recommand( j , neighbor, 5 );
            }else{
                rec_matrix[i][j] = matrix[i][j];
            }
        }
    }
    return rec_matrix;
}
