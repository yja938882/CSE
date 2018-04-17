//
//  DecisionTable.cpp
//  Created by 주안 on 2018. 4. 16..
//  Copyright © 2018년 주안. All rights reserved.
//
#include "DecisionTable.hpp"

/**
    @brief Constructor
*/
DecisionTable::DecisionTable(){
    attr_count = 0;
   
}

/**
    @brief Attribute 추가
    @param pAttr 추가할 Attribute
*/
void DecisionTable::insert_attr( string pAttr ){
    if( attr_id_Map.count(pAttr) ) return;
    
    attr_id_Map.insert( map< string, int >::value_type( pAttr , attr_count ) );
    id_attr_Map.insert( map< int, string >::value_type( attr_count, pAttr ) );
    class_id = attr_count;
    attr_count ++;
}

/**
    @Brief  ID에 해당하는 Attribute 이름 반환
*/
string DecisionTable::get_attr_by_id( int pId ){
    map< int, string >::iterator it = id_attr_Map.find( pId );
    if( it == id_attr_Map.end() ){
        cout<<"error!\n";
        return NULL;
    }
    return it->second;
}

/**
    @brief Attribute 의 ID 반환
*/
int DecisionTable::get_id_by_attr( string pAttr ){
    map< string, int >::iterator it = attr_id_Map.find( pAttr );
    if( it == attr_id_Map.end() ) {
        cout<<"error!\n";
        return -1;
    }
    
    return it->second;
}

/**
    @brief label 초기화
*/
void DecisionTable::init_label(){
    label_id_Maps.resize( attr_count );
    id_label_Maps.resize( attr_count );
    label_count.resize( attr_count );
    for( int i=0; i<label_count.size(); i++ ) label_count[i] = 0;
}

/**
    @brief label 추가
*/
void DecisionTable::insert_label( int pAttrId, string pLabel ){
    if( label_id_Maps[ pAttrId ].count( pLabel ) ) return;
    
    label_id_Maps[ pAttrId ].insert( map< string, int >::value_type( pLabel, label_count[ pAttrId ] ));
    id_label_Maps[ pAttrId ].insert( map< int, string >::value_type( label_count[ pAttrId ], pLabel ));
    label_count[ pAttrId ] ++;
}

/**
    @brief attribute id 와 label id 에 해당하는 label 이름 반환
*/
string DecisionTable::get_label_by_id( int pAttrId, int pId ){
    map< int, string >::iterator it = (id_label_Maps[ pAttrId ]).find( pId );
    if( it == id_label_Maps[ pAttrId ].end() ){
        cout<<"error!\n";
        return NULL;
    }
    
    return it->second;
}

/**
    @brief attribute id 와 label이름 에 해당하는 label id 반환
*/
int DecisionTable::get_id_by_label( int pAttrId, string pLabel ){
    map< string, int >::iterator it = (label_id_Maps[ pAttrId ]).find( pLabel );
    if( it == (label_id_Maps[ pAttrId ]).end() ){
        cout<<"error!\n";
        return -1;
    } 
    
    return it->second;
}

/**
    @brief attribute 의 수 반환
*/
int DecisionTable::attrs_size(){
    return attr_count;
}

/**
    @brief 해당 attribute id 가 가지는 label 수 반환
*/
int DecisionTable::labels_size( int pAttr ){
    return label_count[ pAttr ];
}

/*
    @brief 튜플 삽입
*/
void DecisionTable::insert_tuple( string pTuple ){
    vector< int > tuple;
    char buf[512];
    replace( pTuple.begin(), pTuple.end(), '\r', '\0' );    // for Windows txt
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

/**
    @brief class attribute 의 id 반환
*/
int DecisionTable::get_class_id(){
    return class_id;
}

/**
    @brief 튜플의 클래스 반환 
*/
int DecisionTable::get_tuple_class( int pTupleId){
    return tuples[pTupleId][class_id];
}

/**
    @brief 튜플의 라벨 반환
*/
int DecisionTable::get_tuple_label( int pTupleId, int pAttr ){
    return tuples[pTupleId][pAttr];
}

/**
    @brief 튜플의 크기 반환
*/
int DecisionTable::get_tuple_size(){
    return tuples.size();
}

/** For Debug **/

/** For DEBUG.
    @brief Print Attribute & Labes
*/
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

/** For DEBUG.
    @brief Print Training Tuples
*/
void DecisionTable::debug_print_tp(){
    cout<<"===== print tuples ===================\n";
    for( int i=0; i< this->tuples.size(); i++ ){
        for( int j=0; j< attr_count; j++ ){
            cout<< get_label_by_id( j , this->tuples[i][j] );
        }
        cout<<"\n";
    }
    cout<<"======================================\n";
}