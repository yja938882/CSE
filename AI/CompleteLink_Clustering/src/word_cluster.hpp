#ifndef WORD_CLUSTER_HPP
#define WORD_CLUSTER_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <string.h>
#include <math.h>
using namespace std;
struct word_vector{
    string word;    // word 의 내용
    vector< double > values;    // word 의 벡터값
};

struct test_cluster{
    string name;    // cluster 의 이름
    set< string > word_set; // word 값
};

struct cluster{
    int wv_id;
    struct cluster * left;
    struct cluster * right;
    bool is_leaf;
    double similarity;
    bool clustered;
};

struct cluster_result{
    vector< int > wv_ids;
};

void read_word_data( char* file_name , int , vector< struct word_vector * >& );
void read_test_data( char * , vector< struct test_cluster * > &);

double cosine_similarity( struct word_vector * , struct word_vector* );
void cosine_normalization ( double ** sim_matrix , vector< struct word_vector* > &  );

double euclidean_similarity( struct word_vector *, struct word_vector* );
void euclidean_normalization( double ** sim_matrix, vector< struct word_vector* > & );

void init_sim_matrix( double (*simfunc)( struct word_vector* , struct word_vector* ), double **, vector< struct word_vector* > &);
void get_vector_ids( struct cluster * , vector<int> & );
double min_similarity( double **, struct cluster * , struct cluster * );
struct cluster* clustering( vector< struct word_vector * >& ,double **);
void insert_result( struct cluster_result * , struct cluster * );
void cut_by( struct cluster* , double , vector< struct cluster_result* >& );
void debug_print( struct cluster *);
void print_result_cluster(vector< struct word_vector* >& g_v, struct cluster_result * r );
double entropy( struct cluster_result * r , vector< struct word_vector * > g_w ,
               vector< struct test_cluster * > & test_cluster );
double weighted_entropy_sum( vector< struct cluster_result * > &result ,
                            vector< struct word_vector * > g_v ,
                            vector< struct test_cluster* >& test_c );
void write_result_data( char* file_name, vector< struct word_vector * > g_v , vector< struct cluster_result*> result );
#endif
