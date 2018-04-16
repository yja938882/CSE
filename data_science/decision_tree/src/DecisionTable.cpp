//
//  DecisionTable.cpp
//  Created by 주안 on 2018. 4. 16..
//  Copyright © 2018년 주안. All rights reserved.
//

#include "DecisionTable.hpp"

DecisionTable::DecisionTable(){
    attr_count = 0;
   
}

void DecisionTable::insert_attr( string pAttr ){
    if( attr_id_Map.count(pAttr) ) return;
    
    attr_id_Map.insert( map< string, int >::value_type( pAttr , attr_count ) );
    id_attr_Map.insert( map< int, string >::value_type( attr_count, pAttr ) );
    class_id = attr_count;
    attr_count ++;
}

string DecisionTable::get_attr_by_id( int pId ){
    map< int, string >::iterator it = id_attr_Map.find( pId );
    if( it == id_attr_Map.end() ){
        cout<<"error!\n";
        return NULL;
    }
    return it->second;
}

int DecisionTable::get_id_by_attr( string pAttr ){
    map< string, int >::iterator it = attr_id_Map.find( pAttr );
    if( it == attr_id_Map.end() ) {
        cout<<"error!\n";
        return -1;
    }
    
    return it->second;
}

void DecisionTable::init_label(){
    label_id_Maps.resize( attr_count );
    id_label_Maps.resize( attr_count );
    label_count.resize( attr_count );
    for( int i=0; i<label_count.size(); i++ ) label_count[i] = 0;
}

void DecisionTable::insert_label( int pAttrId, string pLabel ){
    if( label_id_Maps[ pAttrId ].count( pLabel ) ) return;
    
    label_id_Maps[ pAttrId ].insert( map< string, int >::value_type( pLabel, label_count[ pAttrId ] ));
    id_label_Maps[ pAttrId ].insert( map< int, string >::value_type( label_count[ pAttrId ], pLabel ));
    label_count[ pAttrId ] ++;
}

string DecisionTable::get_label_by_id( int pAttrId, int pId ){
    map< int, string >::iterator it = (id_label_Maps[ pAttrId ]).find( pId );
    if( it == id_label_Maps[ pAttrId ].end() ){
        cout<<"error!\n";
        return NULL;
    }
    
    return it->second;
}

int DecisionTable::get_id_by_label( int pAttrId, string pLabel ){
    map< string, int >::iterator it = (label_id_Maps[ pAttrId ]).find( pLabel );
    if( it == (label_id_Maps[ pAttrId ]).end() ){
        cout<<"error!\n";
        return -1;
    } 
    
    return it->second;
}

int DecisionTable::attrs_size(){
    return attr_count;
}

int DecisionTable::labels_size( int pAttr ){
    return label_count[ pAttr ];
}

void DecisionTable::insert_tuple( string pTuple ){
    vector< int > tuple;
    char buf[512];
    replace( pTuple.begin(), pTuple.end(), '\r', '\0' );
    strcpy( buf, pTuple.c_str() );
    char *tk = strtok( buf, "\t" );
    int attr_id = 0;
    while( tk!=NULL ){
        string label( tk );
        this->insert_label( attr_id, label );
        tuple.push_back( this->get_id_by_label( attr_id++, label ) );
        tk = strtok( NULL, "\t" );
    }
    this->tuples.push_back( tuple );
}

double DecisionTable::_I(int * pClassCount ,  int N){
    double sum = 0.0, ret = 0.0;
     for(int i=0; i<N;i++){
        if( pClassCount[i] == 0 )
            return 0.0;
        sum += (double)pClassCount[i];
    }
    for( int i=0; i< N; i++){
        ret-=( ((double)pClassCount[i])/sum )* log2( (double)pClassCount[i] / sum);
    }
    return ret;
}

void DecisionTable::init_info_gain(){
    int label_cnt = labels_size( class_id );
    int info_D_cnt[ label_cnt ];

    for ( int i=0; i< label_cnt; i++ ) info_D_cnt[i] = 0;

    for ( int i=0; i< this->tuples.size(); i++ ) info_D_cnt[ this-> tuples[i][ class_id ] ] ++;

    infoD = _I( info_D_cnt , label_cnt );
    cout<<"in d :'"<<infoD;
    for( int i=0; i< attr_count; i++ ){
        if( i == class_id ) continue ;

        int LABEL_SIZE = label_count[i];
        int CLASS_SIZE = label_count[ class_id ];

        int info_table[ LABEL_SIZE ][ CLASS_SIZE ];
       
        for ( int j=0; j< LABEL_SIZE; j++ ){
            for ( int k=0; k< CLASS_SIZE; k++ )
                info_table[j][k] = 0;
        }

        for ( int j=0; j< tuples.size(); j++ ){
            info_table[ tuples[j][i] ][ tuples[j][class_id] ] ++;
        }

        double label_info[ LABEL_SIZE ];

        for( int j=0; j< label_count[i]; j++) label_info[j] = this->_I( info_table[j], label_count[class_id] );

        double info = 0.0;
        for( int j=0; j< LABEL_SIZE; j++){
            double sum = 0.0;
            for( int k=0; k< CLASS_SIZE; k++){
                sum += info_table[j][k];
            }
            info += (label_info[j] * (sum / (double) tuples.size() ));
        }

        pair< double, int > g = make_pair( infoD - info, i );
        gain.push_back( g ); 
    }
    sort( gain.begin(), gain.end(), GreaterPair );

    
}

int DecisionTable::get_class_id(){
    return class_id;
}

int DecisionTable::get_tuple_class( int pTupleId){
    return tuples[pTupleId][class_id];
}

int DecisionTable::get_tuple_label( int pTupleId, int pAttr ){
    return tuples[pTupleId][pAttr];
}

bool DecisionTable::GreaterPair( const pair<double , int> & a, const pair<double, int>& b){
    return a.first > b.first;
}

int DecisionTable::get_gain_size(){
    return gain.size();
}

int DecisionTable::get_prio_gain( int priority ){
    return gain[priority].second;
}

int DecisionTable::get_tuple_size(){
    return tuples.size();
}

/** For Debug **/
void DecisionTable::debug_print_al(){
    cout<<"===== print attributes & labels =====\n";
    for( int i=0; i< attr_count; i++ ){
        cout<< get_attr_by_id( i )<<" : ";
        for( int j=0; j< label_count[ i ] ; j++ )
            cout<< get_label_by_id( i, j)<<"("<<get_id_by_label(i,get_label_by_id( i, j))<<") ";
        cout<<"\n";
    }
    cout<<"======================================\n";
}

void DecisionTable::debug_print_tp(){
    cout<<"===== print tuples =====\n";
    for( int i=0; i< this->tuples.size(); i++ ){
        for( int j=0; j< attr_count; j++ ){
            cout<< get_label_by_id( j , this->tuples[i][j] );
            //cout<<"("<<get_id_by_label( j,get_label_by_id( j , this->tuples[i][j]) )<<") ";
        }
        cout<<"\n";
    }
    cout<<"========================\n";
}
void DecisionTable::debug_print_ig(){
    cout<<"===== print info gain =====\n";
    for( int i=0; i< gain.size(); i++ ){
        cout<<" "<< get_attr_by_id( gain[i].second )<<"("<<gain[i].first<< ") ";
    }
    cout<<"\n";
    cout<<"===========================\n";
}

