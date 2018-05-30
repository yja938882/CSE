#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "word_cluster.hpp"
using namespace std;
int main( void ){
    double **sim_matrix;
    vector< struct word_vector * > g_vectors;
    vector< struct test_cluster * > test_clusters;
    
    /* Read WordEmbedding.txt */
    read_word_data("../WordEmbedding.txt",300, g_vectors);
    
    /* Read Wordtopic.txt */
    read_test_data("../WordTopic.txt", test_clusters );
    
    /* Initialize similarity matrix */
    sim_matrix = new double* [g_vectors.size() ];
    for( int i=0; i<g_vectors.size(); i++ )
        sim_matrix[i] = new double[ g_vectors.size() ];
    
    /* Calculate normalize value */
    calc_norm( g_vectors );
    
    /* Initialize similarity matrix value - cosine similarity */
    init_sim_matrix( cosine_similarity , sim_matrix, g_vectors );
    
    /* Clustering - cosine similarity */
    struct cluster * cos_root = clustering( g_vectors , sim_matrix );
    
    vector< struct cluster_result* > cos_result[4];
    cut_by( cos_root , 0.8 , cos_result[0]); // threshold 0.8
    cut_by( cos_root , 0.6 , cos_result[1]); // threshold 0.6
    cut_by( cos_root , 0.4 , cos_result[2]); // threshold 0.4
    cut_by( cos_root , 0.2 , cos_result[3]); // threshold 0.2
   
    
    for( int i=0; i<4; i++ ){
        cout << "[" << i << "] ";
        double wetp = 0.0;
        for( int j=0; j<cos_result[i].size();j++){
            wetp += entropy( cos_result[i][j] ,g_vectors,test_clusters ) * (double)(cos_result[i][j]->wv_ids.size()) /338.0 ;
        }
        cout << wetp <<"\n";
    }
    
    /* Initialize similarity matrix value - euclidean similarity */
    init_sim_matrix( euclidean_similarity , sim_matrix, g_vectors );
    
    /* Clustering - euclidean similarity */
    struct cluster * euc_root = clustering( g_vectors , sim_matrix );
    
    vector< struct cluster_result* > euc_result[4];
    cut_by( euc_root , 0.8 , euc_result[0]); // threshold 0.8
    cut_by( euc_root , 0.6 , euc_result[1]); // threshold 0.6
    cut_by( euc_root , 0.4 , euc_result[2]); // threshold 0.4
    cut_by( euc_root , 0.2 , euc_result[3]); // threshold 0.2
    
    for( int i=0; i<4; i++ ){
        cout << "[" << i << "] ";
        double wetp = 0.0;
        for( int j=0; j<euc_result[i].size();j++){
            wetp += entropy( euc_result[i][j] ,g_vectors,test_clusters ) * (double)(euc_result[i][j]->wv_ids.size()) /338.0 ;
        }
        cout << wetp <<"\n";
    }
    
    return 0;
}

