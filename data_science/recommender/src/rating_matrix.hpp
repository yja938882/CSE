#ifndef RATING_MATIX_HPP
#define RATING_MATIX_HPP

#include <vector>
#include <cmath>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct transaction{
	int user_id;	// user id
	int item_id;	// item_id
	int rating;		// rating 
	int time_stamp;	// time_stamp
	transaction( int p_uid, int p_iid, int p_rating , int p_tstp ){
		this -> user_id = p_uid;
		this -> item_id = p_iid;
		this -> rating = p_rating;
		this -> time_stamp = p_tstp;
	}
};

class Transactions{

	public :

	int max_user_id;
	int max_item_id;	
	vector< struct transaction * > trans;

	/* Constructor */
	Transactions();
	
	void push( int, int, int, int );
    
    /* For DEBUG */
    void DEBUG_print();
};

class RatingMatrix{

	public :
	int numOfUser;
	int numOfItem;
    
	int ** matrix;
    double * vec_sums;
    double ** sim_matrix;
    
	RatingMatrix();
	RatingMatrix( Transactions );
    double cosine_similarity( int , int );
    void initSimilarityMatrix();
    vector<int> getNeighbor( int );
    int recommand( int item_id , vector<int> neighbors, int k);
    int** createRecommandedMatrix( int k );
};


#endif
