#include "word_cluster.hpp"

/**
 @ breif : word embedding vector 를 읽어드린다.
 @ param file_name : "WordEmbedding.txt"
 @ param dimension : vector 차원
 @ param g_vector : 저장할 vector 배열
 */
void read_word_data( char* file_name , int dimension , vector< struct word_vector* > &g_vectors ){
    cout << "[*] read word vector data ... start\n";
    ifstream data_file;
    data_file.open( file_name );
    if( !data_file.is_open() ){
        cout <<"[!] open word file error ...\n";
        exit( -1 );
    }
    char temp_word[100];
    while( data_file >> temp_word ){
        struct word_vector *wv = new struct word_vector;
        (wv->word) = temp_word;
        wv->values.resize( dimension );
        for( int i=0; i< dimension -1; i++ ){
            data_file >> (wv->values[i]);
            char a;
            data_file >> a;
        }
        data_file >> (wv->values[dimension-1]);
        g_vectors.push_back( wv );
    }
    cout << "[*] read word vector data ... end \n";
    data_file.close();
    return;
}

/**
 @ breif : 제거할 문자 '\r' , '\n'
 @ param : c
 */
bool isCR( char c) {
    return ( c == '\r' || c == '\n' );
}

/**
 @ breif : cluster test 정보를 읽음
 @ param file_name : "WordTopic.txt"
 @ param test_cluster : 저장할 cluster 배열

 */
void read_test_data( char * file_name , vector< struct test_cluster * > & test_cluster){
    cout << "[*] read test cluster data ... start\n";
    ifstream test_file;
    test_file.open( file_name );
    if( !test_file.is_open() ){
        cout << "[!] open test file error ... \n";
        exit( -1 );
    }
    string input;
    struct test_cluster * test_clust = NULL;
    while( getline(test_file , input ) ){
        input.erase(std::remove_if(input .begin(), input .end(), &isCR), input .end());
        if( input[0] == '[' ){
            if( test_clust!=NULL) test_cluster.push_back(test_clust);
            test_clust = new struct test_cluster;
            test_clust -> name = string(input);
        }else{
            if( input.length() <=1 ) continue;
            for( int i=0; i< input.length() ; i++ ){
                if( input[i]>='A' &&  input[i] <= 'Z' ){
                    input[i]+=('a'-'A');
                }
            }
            (test_clust->word_set).insert( input );
        }
    }
    test_cluster.push_back(test_clust);
    test_file.close();
    cout << "[*] read test cluster data ... end \n";
}

/**
 @ breif : word a 와 word b 간의 cosine similarity
 @ param a : word1
 @ param b : word2
 */
double cosine_similarity( struct word_vector * a, struct word_vector* b ){
    double a_sum = 0.0, b_sum = 0.0 , ab_sum = 0.0;
    for( int i=0; i< (a->values).size(); i++ ){
        a_sum += ( a->values[i] * a->values[i] );
        b_sum += ( b->values[i] * b->values[i] );
        ab_sum += ( a->values[i] * b->values[i] );
    }
    return ab_sum /( sqrt(a_sum) * sqrt(b_sum) );
}

double norm = 1.0; // for nomaization

/**
 @ breif : norm 값 설정
 @ param g_v : word vector
 */
void calc_norm( vector< struct word_vector * > g_v ){
    double max_norm = -100.0;
    for( int i=0; i< g_v.size(); i++ ){
        for( int j= i+1; j<g_v.size(); j++ ){
            double dif = 0;
            for( int k=0; k< 300; k++ ){
                dif += ( g_v[i]->values[k] - g_v[j] ->values[k])*( g_v[i]->values[k] - g_v[j] ->values[k]);
            }
            dif = sqrt( dif );
            if( dif > max_norm )
                max_norm = dif;
        }
    }
    norm = max_norm;
}

/**
 @ breif : 두 word vector 간의 euclidean simlilarity 계산
 @ param a : word1
 @ param b : word2
 */
double euclidean_similarity( struct word_vector * a, struct word_vector* b ){
    double d_sum = 0.0;

    for( int i=0; i< (a->values).size(); i++ ){
        d_sum += ( a->values[i] - b->values[i] )*( a->values[i] - b->values[i] );
    }
    d_sum = sqrt( d_sum ) / norm;
    return 1.0-d_sum;
}

/**
 @ breif : similarity matrix 값 초기화
 @ param simfunc : similarity function
 @ param sim_matrix : similarity 를 저장할 배열
 @ param g_vectors : word vectors
 */
void init_sim_matrix( double (*simfunc)( struct word_vector* , struct word_vector* ) ,double ** sim_matrix , vector< struct word_vector* >& g_vectors){
    cout << "[*] initialize ... start \n";
    int m_size = (int)g_vectors.size();
   
    for( int i=0; i< m_size; i++ ){
        for( int j=i+1; j<m_size; j++ ){
            double sim = simfunc( g_vectors[i], g_vectors[j] );
            sim_matrix[i][j] = sim;
            sim_matrix[j][i] = sim;
        }
    }
    cout << "[*] initialize ... end \n";
}

void get_vector_ids( struct cluster * clust , vector<int> & ids ){
    if( clust -> is_leaf ){
        ids.push_back( clust->wv_id );
        return;
    }
    if( clust -> left != NULL ) get_vector_ids( clust -> left , ids );
    if( clust ->right != NULL ) get_vector_ids( clust -> right , ids);
}

double min_similarity(double** sim_matrix, struct cluster * clusterA, struct cluster * clusterB ){
    vector< int > a_ids;
    vector< int > b_ids;
    get_vector_ids( clusterA , a_ids );
    get_vector_ids( clusterB, b_ids );
    
    double min_sim = 100.0;
    for( int i=0; i< a_ids.size(); i++ ){
        for( int j=0; j< b_ids.size(); j++ ){
            if( sim_matrix[ a_ids[i] ][ b_ids[j] ] < min_sim ){
                min_sim = sim_matrix[ a_ids[i] ][ b_ids[j] ];
            }
        }
    }
    return min_sim;
}

struct cluster * clustering(vector< struct word_vector* >& g_v, double ** sim_matrix ){
    cout << "[*] clustering ... start \n";
    vector< struct cluster * > cur;
    int sz =g_v.size();
    for( int i=0; i< sz; i++ ){
        struct cluster * clust = new struct cluster;
        clust -> wv_id = i ;
        clust -> is_leaf = true;
        clust -> left = NULL;
        clust -> right = NULL;
        clust -> similarity = 1;
        clust -> clustered = false;
        cur.push_back( clust );
    }
    
    while( cur.size() > 1 ){
        double min_sim = -100.0;
        int min_i = -1,min_j = -1;
        for( int i=0; i< cur.size(); i++ ){
            for( int j=i+1; j< cur.size(); j++ ){
                double ms = min_similarity(sim_matrix, cur[i] , cur[j] );
                if( ms > min_sim ){
                    min_sim = ms;
                    min_i = i;
                    min_j = j;
                }
            }
        }
        if( min_i == -1 || min_j == -1 ){
            exit(-1);
            cout << "[!] error! \n";
        }
        
        struct cluster * clust = new struct cluster;
        clust -> is_leaf = false;
        clust -> left = cur[min_i];
        clust -> right = cur[min_j];
        clust -> similarity = min_sim;
        cur.erase( cur.begin() + min_j );
        cur.erase( cur.begin() + min_i );
        cur.push_back( clust );
    }
    
    
    cout << "[*] clustering ... end \n";
    return cur[0];
}

/**
 @ breif : 해당 클러스터 아래의 word vector 를 cluster 에 삽입
 @ param r : 삽입할 결과 cluster
 @ param c : 해당 클러스터
 */
void insert_result( struct cluster_result * r, struct cluster * c){
    if( c-> is_leaf ) {
        (r->wv_ids).push_back( c->wv_id );
        return;
    }
    insert_result( r, c->left );
    insert_result( r, c->right );
}

/**
 @ biref : clustering tree 를 threshold 에 따라 자름
 @ param root : root of tree
 @ param threshold : threshold
 @ param result : 결과를 저장할 배열
 */
void cut_by( struct cluster * root, double threshold,  vector< struct cluster_result* >& result){
    if( root->similarity > threshold ){
        struct cluster_result * r = new struct cluster_result;
        insert_result( r, root );
        result.push_back( r );
    }else{
        if( root->left!=NULL)
            cut_by( root->left, threshold, result);
        if( root->right!=NULL)
            cut_by( root->right, threshold, result);
    }
}

void debug_print( struct cluster * root ){
    if( root -> is_leaf ){
        return;
    }
    cout << root->similarity <<"  ";
    debug_print( root->left );
    debug_print( root->right );
}

/**
 @ breif : For Debugging
 @ param g_v : word vector
 @ param r : result cluster
 */
void print_result_cluster(vector< struct word_vector* >& g_v, struct cluster_result * r ){
    for( int i=0; i< r->wv_ids.size(); i++ ){
        cout << g_v[ r->wv_ids[i] ]->word << " ";
    }
    cout << "\n";
}

/**
 @ breif : 클러스터의 엔트로피 계산
 @ param g_w : word vector
 @ param test_cluster : 평가 기준이 되는 cluster
 */
double entropy( struct cluster_result * r , vector< struct word_vector * > g_w ,
               vector< struct test_cluster * > & test_cluster ){
   
    int cnt[ test_cluster.size() ];
    for( int i=0; i< test_cluster.size(); i++ ) cnt[i] = 0;
   
    /* Cluster 카운트  */
    for( int i=0 ; i < (r->wv_ids.size()); i++ ){
        int wid = (r->wv_ids[i]);
        for( int j=0; j<test_cluster.size(); j++ ){
            /* WordTopic [j] 클러스터에 속하면 카운트 */
            if( test_cluster[j]->word_set.find( g_w[wid]->word ) != (test_cluster[j]->word_set).end() ){
                cnt[j]++;
                break;
            }
        }
    }
    
    /* Entropy 계산 */
    double etp = 0.0;
    double total = (double)(r->wv_ids.size());
    for( int i=0; i< test_cluster.size(); i++ ){
        if( cnt[i] == 0 ) continue;
        etp -= ( (double)cnt[i]/total ) * (log2((double)cnt[i]/total )) ;
    }
    return etp;
}

