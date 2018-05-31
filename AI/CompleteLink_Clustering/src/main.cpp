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
    
    /* Read "WordEmbedding.txt" */
    read_word_data("./WordEmbedding.txt",300, g_vectors);
    
    /* Read "Wordtopic.txt" */
    read_test_data("./WordTopic.txt", test_clusters );
    
    /* Initialize similarity matrix */
    sim_matrix = new double* [g_vectors.size() ];
    for( int i=0; i<g_vectors.size(); i++ )
        sim_matrix[i] = new double[ g_vectors.size() ];

    /* Initialize similarity matrix value - cosine similarity */
    init_sim_matrix( cosine_similarity , sim_matrix, g_vectors );
    
    /* Nomalization - cosine similarity */
    cosine_normalization( sim_matrix , g_vectors );
    
    /* Clustering - cosine similarity */
    struct cluster * cos_root = clustering( g_vectors , sim_matrix );
    
    vector< struct cluster_result* > cos_result[4];
    cut_by( cos_root , 0.8 , cos_result[0]); // threshold 0.8
    cut_by( cos_root , 0.6 , cos_result[1]); // threshold 0.6
    cut_by( cos_root , 0.4 , cos_result[2]); // threshold 0.4
    cut_by( cos_root , 0.2 , cos_result[3]); // threshold 0.2
    

    /* Initialize similarity matrix value - euclidean similarity */
    init_sim_matrix( euclidean_similarity , sim_matrix, g_vectors );
    
    /* Nomalization - euclidean similarity */
    euclidean_normalization( sim_matrix , g_vectors );
    
    /* Clustering - euclidean similarity */
    struct cluster * euc_root = clustering( g_vectors , sim_matrix );
    
    vector< struct cluster_result* > euc_result[4];
    cut_by( euc_root , 0.8 , euc_result[0]); // threshold 0.8
    cut_by( euc_root , 0.6 , euc_result[1]); // threshold 0.6
    cut_by( euc_root , 0.4 , euc_result[2]); // threshold 0.4
    cut_by( euc_root , 0.2 , euc_result[3]); // threshold 0.2
    
    
    /* Print result */
    cout << "|========[ Cosine Similarity ]========\n";
    cout << "| Threshold |   Weighted entropy sum  \n";
    cout << "|-------------------------------------\n";
    cout << "|    0.8    | " << weighted_entropy_sum( cos_result[0], g_vectors, test_clusters ) <<"\n";
    cout << "|    0.6    | " << weighted_entropy_sum( cos_result[1], g_vectors, test_clusters ) <<"\n";
    cout << "|    0.4    | " << weighted_entropy_sum( cos_result[2], g_vectors, test_clusters ) <<"\n";
    cout << "|    0.2    | " << weighted_entropy_sum( cos_result[3], g_vectors, test_clusters ) << "\n";
    cout << "|=====================================\n";
    
    cout << "|======[ Euclidean Similarity ]=======\n";
    cout << "| Threshold |   Weighted entropy sum  \n";
    cout << "|-------------------------------------\n";
    cout << "|    0.8    | " << weighted_entropy_sum( euc_result[0], g_vectors, test_clusters ) <<"\n";
    cout << "|    0.6    | " << weighted_entropy_sum( euc_result[1], g_vectors, test_clusters ) <<"\n";
    cout << "|    0.4    | " << weighted_entropy_sum( euc_result[2], g_vectors, test_clusters ) <<"\n";
    cout << "|    0.2    | " << weighted_entropy_sum( euc_result[3], g_vectors, test_clusters ) << "\n";
    cout << "|=====================================\n";
   
    /* Write result */
    write_result_data("WordClustering.txt", g_vectors, cos_result[1] );
    
    return 0;
}

